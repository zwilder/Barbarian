/*
* Barbarian!
* Copyright (C) Zach Wilder 2018
* 
* This file is a part of Barbarian!
*
* Barbarian! is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Barbarian! is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Barbarian!.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <iostream>
#include <iterator>
#include <sstream>
#include "../include/engine.hpp"

Engine::Engine()
{
    windowWidth_ = 800; // Window is set to 800x600 so the console can be 'centered' in it
    windowHeight_ = 600;
    windowTitle_ = "Barbarian!";
    window_ = NULL;

    spriteSize_ = wsl::Vector2i(9,14);
    consoleWidth_ = windowWidth_ / spriteSize_.x; // 88; // consoleWidth_ and consoleHeight_ refer to the 'root' console
    consoleHeight_ = windowHeight_ / spriteSize_.y; // 42; 
    fullscreen_ = false;

    maxRoomSize_ = 10;
    minRoomSize_ = 6;
    maxRooms_ = 15; 

    visible_ = std::make_unique< std::vector<wsl::Vector2i> >();

    ACTION_COST = 100;
    gameState_ = GameState::PLAYERS_TURN;
    prevGameState_ = gameState_;
    running_ = init();

    currentMsg_ = "";
}

bool Engine::init()
{
    bool success = true;

    // Set up the virtual console
    console_ = std::make_unique<wsl::Console>(consoleWidth_, consoleHeight_);

    // Set up the physical window and renderer (SDL)
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL failed to initialize: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{

		window_ = SDL_CreateWindow(windowTitle_.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth_, windowHeight_, SDL_WINDOW_SHOWN);
		if (window_ == NULL)
		{
			std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
			success = false;
		}
	}
    
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_ == NULL)
    {
        std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
        int imgFlags = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags) & imgFlags))
        {
            std::cout << "Failed to initialize SDL_image: " << SDL_GetError() << std::endl;
            success = false;
        }
    }

    if(success)
    {
        // Load the cp437 texture image
        spriteSheet_ = new wsl::Texture;
        success = spriteSheet_->loadFromFile("assets/IBM_9x14.png", renderer_);

        // Create sprite rectangles for all sprites on the spritesheet 
        int x = 0;
        int y = 0;
        for(size_t i = 0; i < spriteRects_.size(); ++i)
        {
            spriteRects_[i] = wsl::Rect(x,y,spriteSize_.x, spriteSize_.y);

            x += spriteSize_.x;
            if(i == 0)
            {
                continue;
            }
            if(x == 16 * spriteSize_.x)
            {
                y += spriteSize_.y;
                x = 0;
            }
        }
        
        // Setup the game map width/height - should be a different function, with the next three arguments passed in.
        gameMap_ = std::make_unique<GameMap>(this, consoleWidth_, consoleHeight_, maxRoomSize_, minRoomSize_, maxRooms_);

        // Add the player entity - Should be a separate function,
        // which would facilitate a character creation option in the future. 
        player_ = new Entity(this, wsl::Vector2i(0,0), wsl::Glyph('@', wsl::Color::Black, wsl::Color::Green), "Griff");
        player_->makeActor(Actor(50,4)); // speed, vision
        player_->makeInventory();
        player_->setPos(gameMap_->rooms[0].center());
        fov::visible(visible_.get(), gameMap_.get(), player_);

        // Tell gamemap to place some enemies
        entityList_.clear();
        gameMap_->placeActors(2);
        gameMap_->placeItems(5);
    }
    return success;
}

void Engine::cleanup()
{
    delete spriteSheet_;
    delete player_;
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Engine::handleEvents()
{
    // Poll the window for user input events (SFML)
    SDL_Event event;
    Input input;
    bool keyPressed = false;
    while(SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT)
        {
            running_ = false;
        }
        else if(event.type == SDL_KEYDOWN)
        {
            input = handleKeys(event.key.keysym.sym);
            keyPressed = true;
        }
    }

    // Evaluate the input to see if the engine needs to do anything.
    if(input.quit())
    {
        if(gameState_ == GameState::INVENTORY || gameState_ == GameState::DROP)
        {
            changeState(prevGameState_);
        }
        else
        {
            running_ = false;
        }
    }
    if(input.fullscreen())
    {
        // This is very broken, and I don't know why
        // Uint32 flags = (SDL_GetWindowFlags(window_) ^ SDL_WINDOW_FULLSCREEN_DESKTOP);
        // if(SDL_SetWindowFullscreen(window_, flags) < 0)
        // {
        //    std::cout << "Failed to set fullscreen: " << SDL_GetError() << std::endl;
        // }
        if(fullscreen_)
        {
            windowWidth_ = 800;
            windowHeight_ = 600;
            SDL_SetWindowSize(window_, windowWidth_, windowHeight_);
            SDL_SetWindowPosition(window_, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
            fullscreen_ = false;
        }
        else
        {
            SDL_DisplayMode dm;
            SDL_GetDesktopDisplayMode(0, &dm);
            windowWidth_ = dm.w;
            windowHeight_ = dm.h;
            SDL_SetWindowSize(window_, windowWidth_ + 10, windowHeight_ + 10);
            SDL_SetWindowPosition(window_, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
            fullscreen_ = true;
        }
    }
    if(gameState_ == GameState::PLAYERS_TURN)
    {
        if(input.move())
        {
            wsl::Vector2i dPos = player_->pos() + input.dir();
            if(!gameMap_->tileAt(dPos).blocksMovement())
            {
                Entity * actor = gameMap_->actorAt(dPos);
                Entity * item = gameMap_->itemAt(dPos);
                bool move = false;
                if(actor)
                {
                    addMessage("You attack the " + actor->name() + " for " + std::to_string(player_->power() - actor->defense()) + " damage!");
                    actor->takeDamage(player_->power() - actor->defense());
                }
                else if(item)
                {
                    move = true;
                    if(item->quantity() > 1)
                    {
                        addMessage("You see " + std::to_string(item->quantity()) + " " + item->name() + "s here.");
                    }
                    else
                    {
                        addMessage("You see a " + item->name() + " here.");
                    }
                }
                else
                {
                    move = true;
                }

                if(move)
                {
                    player_->move(input.dir()); // Need to move this to the player's "update" routine, so the player takes their turn in proper order.
                    fov::visible(visible_.get(), gameMap_.get(), player_);
                }
            }
            changeState(GameState::ENEMY_TURN);
        }
        if(input.get())
        {
            Entity * itemEntity = gameMap_->itemAt(player_->pos());
            if(itemEntity == NULL)
            {
                addMessage("You see no item here.");
            }
            else
            {
                player_->pickup(itemEntity);
                if(itemEntity->quantity() > 1)
                {
                    addMessage("You pickup the " + itemEntity->name() + "s.");
                }
                else
                {
                    addMessage("You pickup the " + itemEntity->name() + ".");
                }
            }
            changeState(GameState::ENEMY_TURN);
        }
        if(input.openInv())
        {
            changeState(GameState::INVENTORY);
        }
        if(input.openDrop())
        {
            changeState(GameState::DROP);
        }
        if(input.nextLevel())
        {
            *gameMap_ = GameMap(this, consoleWidth_, consoleHeight_, maxRoomSize_, minRoomSize_, maxRooms_);
            player_->setPos(gameMap_->rooms[0].center());
            fov::visible(visible_.get(), gameMap_.get(), player_);
            // Tell gamemap to place some enemies
            entityList_.clear();
            gameMap_->placeActors(2);
            gameMap_->placeItems(5);
        }
    }
    // else if(gameState_ == GameState::MSG_WAIT && input.enter())
    // {
    //     if(!msgList_.isEmpty())
    //     {
    //         currentMsg_ = msgList_.popFront();
    //         if(msgList_.isEmpty())
    //         {
    //             gameState_ = GameState::PLAYERS_TURN;
    //         }
    //     }
    //     else
    //     {
    //         currentMsg_ = "";
    //         gameState_ = GameState::PLAYERS_TURN;
    //     }
    // }
    else if (gameState_ == GameState::INVENTORY)
    {
        if(input.alpha() >= 'a' && input.alpha() <= 'z')
        {
            int index = int(input.alpha() - 97);
            wsl::DLNode<Entity> * itemNode = player_->inventory()->at(index);
            if(itemNode)
            {
                player_->use(index);
                addMessage("You use the " + itemNode->data.name() + "!");
                changeState(GameState::ENEMY_TURN);
            }
        }
    }
    else if (gameState_ == GameState::DROP)
    {
        if(input.alpha() >= 'a' && input.alpha() <= 'z')
        {
            int index = int(input.alpha() - 97);
            wsl::DLNode<Entity> * itemNode = player_->inventory()->at(index);
            if(itemNode)
            {
                player_->drop(index);
                if(itemNode->data.quantity() > 1 )
                {
                    addMessage("You drop the " + itemNode->data.name() + "s.");
                }
                else
                {
                    addMessage("You drop the " + itemNode->data.name() + ".");
                }
                changeState(GameState::ENEMY_TURN);
            }
        }
    }
    else if (gameState_ == GameState::EQUIP)
    {
        //
    }
    else if(gameState_ == GameState::GAME_OVER && keyPressed)
    {
        newGame();
    }
}

void Engine::update()
{
    /*
    if(!schedule_->isEmpty())
    // while(schedule_->head() != NULL)
    {
        // std::cout << "Schedule is not empty\n";
        // if(curActor_ == NULL)
        // {
        //     curActor_ = schedule_->popFront();
        // }
        // if(gameState_ == GameState::PLAYERS_TURN)
        // {
        //     return;
        // }
        // else
        // {
        //     //curActor_->update();
        // }
        // std::cout << curActor_->name() << " took turn!\n";
        if(!curActor_->update())
        {
            return; // Current actor failed to take turn
        }
        curActor_->energy() -= ACTION_COST;
        curActor_ = schedule_->popFront();
        return;
    }
    else
    {
        // for(int i = 0; i < entityList_->size(); ++i)
        for(wsl::DLNode<Entity> * temp = entityList_.head(); temp != NULL; temp = temp->next)
        {
            // if(entityList_->at(i).actor() == NULL)
            Entity & entity = temp->data;
            Actor * actor = entity.actor();
            if(actor == NULL)
            {
                continue;
            }
            // Actor * actor = entityList_->at(i).actor();
            actor->grantEnergy();
            if(actor->energy() >= ACTION_COST)
            {
                schedule_->push(actor);
            }
        }
        player_->actor()->grantEnergy();
        if(player_->actor()->energy() >= ACTION_COST)
        {
            schedule_->push(player_->actor());
        }
        gameState_ = GameState::PLAYERS_TURN;
    }
    */
    if(gameState_ == GameState::ENEMY_TURN)
    {
        for(wsl::DLNode<Entity> * temp = entityList_.head(); temp != NULL; temp = temp->next)
        {
            Entity & entity = temp->data;
            entity.update();
        }
        if((gameState_ != GameState::GAME_OVER))// && (gameState_ != GameState::MSG_WAIT))
        {
            changeState(GameState::PLAYERS_TURN);
        }

        if(!msgList_.isEmpty())
        {
            currentMsg_ = msgList_.popFront();
        }
        else
        {
            currentMsg_ = "";
        }
    }
    //Remove dead entities (and leave corpses!)
    wsl::DLNode<Entity> * current = entityList_.head();
    while(current != NULL)
    {
        if(current->data.check(Entity::Flags::DEAD))
        {
            wsl::DLNode<Entity> * dead = current;
            current = current->next;
            gameMap_->tileAt(dead->data.pos()).glyph() = wsl::Glyph(dead->data.glyph().symbol(), dead->data.glyph().color(), dead->data.glyph().bgColor());
            entityList_.remove(dead);
        }
        else
        {
            current = current->next;
        }
    }
}

void Engine::draw()
{
    // Render order, GameMap (Tiles) >> Stairs >> Items >> Entities.
    // Translate GameMap to virtual console (right now this is the 'root' console)
    console_->flush();

    // Render tiles first, this loops through the entirety of the console_ width/height, since Tiles remain visible after being explored.
    if(gameState_ == GameState::ENEMY_TURN || gameState_ == GameState::PLAYERS_TURN || gameState_ == GameState::GAME_OVER)
    {
        for(int x = 0; x < console_->width(); ++x)
        {
            for(int y = 0; y < console_->height(); ++y)
            {
                int index = console_->index(x,y);
                wsl::Glyph glyph = gameMap_->tiles[index].glyph();
                if(fov::contains(visible_.get(), wsl::Vector2i(x,y)))
                { 
                    console_->put(x,y,glyph);
                    gameMap_->tiles[index].engage(Tile::Flags::EXPLORED);
                }
                else if(gameMap_->tiles[index].explored())
                {
                    if(glyph.symbol() != '#')
                    {
                        glyph.setColor(wsl::Color::Black);
                    }
                    else
                    {
                        glyph.setColor(wsl::Color::DkGrey);
                    }
                    glyph.setBgColor(wsl::Color::Black);
                    console_->put(x,y,glyph);
                }
            }
        }

        // Loop through entities here, rendering items if they've been seen (explored)

        // Loop through entities again, rendering entities IF they are in the visible_ coordinates.
        for(wsl::DLNode<Entity> * temp = entityList_.head(); temp != NULL; temp = temp->next)
        {
            Entity & entity = temp->data;
            wsl::Vector2i entityPos = entity.pos();
            wsl::Glyph entityGlyph = entity.glyph();
            if(fov::contains(visible_.get(), entityPos))
            {
                console_->put(entityPos.x,entityPos.y,entityGlyph);
            }
        }

        console_->put(player_->pos().x, player_->pos().y, player_->glyph());

        // UI
        console_->print(0,0, currentMsg_);
        console_->print(0,console_->height() - 2, player_->name());
        console_->print(0,console_->height() - 1, "HP: " + std::to_string(player_->hp()) + "(" + std::to_string(player_->maxHP()) + ")");
    }
    else if(gameState_ == GameState::INVENTORY)
    {
        console_->print(0,1, "Inventory");
        console_->print(0,2, "---------");
        // if(player_->inventory()->size() == 0)
        if(player_->inventory()->isEmpty())
        {
            console_->print(0,3, "Your inventory is empty.");
        }
        else
        {
            int i = 0;
            for(wsl::DLNode<Entity> * temp = player_->inventory()->head(); temp != NULL; temp = temp->next)
            {
                Entity & item = temp->data;
                std::string name = item.name();
                name[0] = toupper(name[0]);
                int nameSize = int(name.size());
                
                console_->print(0, int(i) + 3, std::string(1, char(i+97)));
                console_->print(1, int(i) + 3, ": " + name); 
                if(item.stackable())
                {
                    console_->print(nameSize + 4, int(i) + 3, "x " + std::to_string(item.quantity()));
                }
                ++i;
            }
        }

        console_->print(0, console_->height() - 1, "Press [a-z] to select, [Esc] to exit");
    }
    else if(gameState_ == GameState::DROP)
    {
        console_->print(0,1, "Select the item you wish to drop:");
        console_->print(0,2, "---------");
        // if(player_->inventory()->size() == 0)
        if(player_->inventory()->isEmpty())
        {
            console_->print(0,3, "Your inventory is empty.");
        }
        else
        {
            int i = 0;
            for(wsl::DLNode<Entity> * temp = player_->inventory()->head(); temp != NULL; temp = temp->next)
            {
                Entity & item = temp->data;
                std::string name = item.name();
                name[0] = toupper(name[0]);
                int nameSize = int(name.size());
                
                console_->print(0, int(i) + 3, std::string(1, char(i+97)));
                console_->print(1, int(i) + 3, ": " + name); 
                if(item.stackable())
                {
                    console_->print(nameSize + 4, int(i) + 3, "x " + std::to_string(item.quantity()));
                }
                ++i;
            }
        }

        console_->print(0, console_->height() - 1, "Press [a-z] to select, [Esc] to exit");

    }

    // Clear the SDL window
    SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer_);

    // Create sprites from the template sprites in spriteChars_ to represent the characters on the virtual console, and draw them to the screen
    wsl::Sprite cursorSprite = wsl::Sprite(wsl::Rect(0,0,spriteSize_.x,spriteSize_.y),spriteSheet_); 
    wsl::Sprite bgCursorSprite = wsl::Sprite(wsl::Rect(0,0,spriteSize_.x,spriteSize_.y),spriteSheet_);
    int xOfs = (windowWidth_ - (console_->width() * spriteSize_.x)) / 2; // Centers the console on the window
    int yOfs = (windowHeight_ - (console_->height() * spriteSize_.y)) / 2;
    for(int x = 0; x < console_->width(); ++x)
    {
        for(int y = 0; y < console_->height(); ++y)
        {
            wsl::Color bgColor = console_->get(x,y).bgColor();
            if(bgColor != wsl::Color::Black)
            {
                bgCursorSprite.setTexPos(spriteRects_[219]); // 219 is the white square in the CP437 font
                bgCursorSprite.setPos((x * spriteSize_.x) + xOfs, (y * spriteSize_.y) + yOfs);
            
                bgCursorSprite.render(renderer_, bgColor);
            }
            wsl::Rect & textureRect = spriteRects_[console_->get(x,y).symbol()];
            cursorSprite.setPos((x * spriteSize_.x) + xOfs, (y * spriteSize_.y) + yOfs);
            cursorSprite.setTexPos(wsl::Rect(textureRect.x1, textureRect.y1, textureRect.w, textureRect.h));
            wsl::Color color = console_->get(x,y).color();

            cursorSprite.render(renderer_, color);
        }
    }
    
    // Display the SDL window
    SDL_RenderPresent(renderer_);
}

void Engine::addMessage(std::string msg)
{
    // Check message head, if message head is less than maxLength, pop and combine with msg.
    if(!msgList_.isEmpty())
    {
        std::string & msgHead = msgList_.head()->data;
        msg = msgHead + " " + msg;
        msgList_.popFront();
    }
    msgList_.push(msg);

    // int maxLength = console_->width() * 3; // # lines
    // maxLength -= 7; // [MORE]
    // maxLength -= 26; // [Press enter to continue]
    // if(int(msg.size()) > maxLength)
    // {
    //     // Split message?
    //     // Break into words, adding words to msg until maxLength. Then add [Press any key to continue]. Push msg to list and continue until all words are added.
    //     std::istringstream iss(msg);
    //     std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
    //     std::string first = "";
    //     std::string remainder = "";
    //     for(size_t i = 0; i < results.size(); ++i)
    //     {
    //         std::string & word = results[i];
    //         word += " ";
    //         if((int(word.size()) + int(first.size())) > maxLength)
    //         {
    //             //Exceeded max length, add the word to remainder
    //             remainder += word;
    //         }
    //         else
    //         {
    //             first += word;
    //         }
    //     }
    //     first += " [Press enter to continue]";
    //     msgList_.push(remainder);
    //     msgList_.push(first);
    //     gameState_ = GameState::MSG_WAIT;
    //     // addMessage(remainder);
    //     // addMessage(first);
    // }
    // else
    // {
        // msgList_.push(msg);
    // }
}

void Engine::changeState(GameState newState)
{
    prevGameState_ = gameState_;
    gameState_ = newState;
}

void Engine::revertState()
{
    gameState_ = prevGameState_;
}

void Engine::newGame()
{
    // This code is a mess and should be replaced eventually with something cleaner, less specific, and reusable.
    *gameMap_ = GameMap(this, consoleWidth_, consoleHeight_, maxRoomSize_, minRoomSize_, maxRooms_);

    // Add the player entity - Should be a separate function,
    // which would facilitate a character creation option in the future. 
    *player_ = Entity(this, wsl::Vector2i(0,0), wsl::Glyph('@', wsl::Color::Black, wsl::Color::Green), "Griff");
    player_->makeActor(Actor(50,4)); // speed, vision
    player_->makeInventory();
    player_->setPos(gameMap_->rooms[0].center());
    fov::visible(visible_.get(), gameMap_.get(), player_);

    // Tell gamemap to place some enemies
    entityList_.clear();
    gameMap_->placeActors(2);
    gameMap_->placeItems(5);
    gameState_ = GameState::PLAYERS_TURN;
    prevGameState_ = gameState_;
    msgList_.clear();
    currentMsg_ = "";
}
