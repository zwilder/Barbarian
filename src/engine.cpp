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
#include "../include/engine.hpp"

Engine::Engine()
{
    consoleWidth_ = 80; // consoleWidth_ and consoleHeight_ refer to the 'root' console
    consoleHeight_ = 50;
    spriteSize_ = 12;

    windowWidth_ = consoleWidth_ * spriteSize_;
    windowHeight_ = consoleHeight_ * spriteSize_;
    windowTitle_ = "Barbarian!";
    window_ = NULL;

    maxRoomSize_ = 10;
    minRoomSize_ = 6;
    maxRooms_ = 15; 

    visible_ = std::make_unique< std::vector<wsl::Vector2i> >();
    entityList_ = std::make_unique< std::vector<Entity> >();

    running_ = init();
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
        success = spriteSheet_->loadFromFile("assets/cp437_12x12.png", renderer_);

        // Create sprite rectangles for all sprites on the spritesheet 
        int x = 0;
        int y = 0;
        for(int i = 0; i < spriteRects_.size(); ++i)
        {
            spriteRects_[i] = wsl::Rect(x,y,spriteSize_, spriteSize_);

            x += spriteSize_;
            if(i == 0)
            {
                continue;
            }
            if(x == 16 * spriteSize_)
            {
                y += spriteSize_;
                x = 0;
            }
        }
        
        // Setup the game map width/height - should be a different function, with the next three arguments passed in.
        gameMap_ = std::make_unique<GameMap>(consoleWidth_, consoleHeight_, maxRoomSize_, minRoomSize_, maxRooms_);

        // Create empty vector to hold entities, and add the player entity - Should also be a separate function,
        // which would facilitate a character creation option in the future. 
        player_ = Entity(wsl::Vector2i(0,0), wsl::Glyph('@', wsl::Color::Black, wsl::Color::Green), 4); // # is the FOV, this should be changed
        player_.setPos(gameMap_->rooms[0].center());
        fov::visible(visible_.get(), gameMap_.get(), &player_);

        // Tell gamemap to place some enemies
    }
    return success;
}

void Engine::cleanup()
{
    delete spriteSheet_;
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Engine::handleEvents()
{
    // Poll the window for user input events (SFML)
    SDL_Event event;
    Action action;
    while(SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT)
        {
            running_ = false;
        }
        else if(event.type == SDL_KEYDOWN)
        {
            action = handleKeys(event.key.keysym.sym);
        }
    }

    // Evaluate the action to see if the engine needs to do anything.
    if(action.quit())
    {
        running_ = false;
    }
    if(action.move())
    {
        wsl::Vector2i dPos = player_.pos() + action.dir();
        if(!gameMap_->isBlocked(dPos.x,dPos.y))
        {
            player_.move(action.dir());
            fov::visible(visible_.get(), gameMap_.get(), &player_);
        }
    }
    if(action.nextLevel())
    {
        *gameMap_ = GameMap(consoleWidth_, consoleHeight_, maxRoomSize_, minRoomSize_, maxRooms_);
        player_.setPos(gameMap_->rooms[0].center());
        fov::visible(visible_.get(), gameMap_.get(), &player_);
        // Tell gamemap to place some enemies
    }
}

void Engine::update()
{
    //
}

void Engine::draw()
{
    // Render order, GameMap (Tiles) >> Stairs >> Items >> Entities.
    // Translate GameMap to virtual console (right now this is the 'root' console)
    console_->flush();

    // Render tiles first, this loops through the entirety of the console_ width/height, since Tiles remain visible after being explored.
    for(int x = 0; x < console_->width(); ++x)
    {
        for(int y = 0; y < console_->height(); ++y)
        {
            int index = console_->index(x,y);
            wsl::Glyph glyph = gameMap_->tiles[index].glyph();
            if(fov::contains(visible_.get(), wsl::Vector2i(x,y)))
            { 
                if(glyph.symbol() != '#')
                {
                    glyph.setColor(glyph.bgColor());
                    glyph.setBgColor(wsl::Color::LtYellow);
                }
                console_->put(x,y,glyph);
                gameMap_->tiles[index].engage(Tile::Flags::EXPLORED);
            }
            if(gameMap_->tiles[index].explored())
            {
                // glyph.setBgColor(wsl::Color::DkGrey);
                console_->put(x,y,glyph);
            }
        }
    }

    // Loop through entities here, rendering items if they've been seen (explored)

    // Loop through entities again, rendering entities IF they are in the visible_ coordinates.
    // Temporarily just rendering the player.
    console_->put(player_.pos().x, player_.pos().y, player_.glyph());

    // Clear the SDL window
    SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer_);

    // Create sprites from the template sprites in spriteChars_ to represent the characters on the virtual console, and draw them to the screen
    wsl::Sprite cursorSprite = wsl::Sprite(wsl::Rect(0,0,spriteSize_,spriteSize_),spriteSheet_); 
    wsl::Sprite bgCursorSprite = wsl::Sprite(wsl::Rect(0,0,spriteSize_,spriteSize_),spriteSheet_);
    for(int x = 0; x < console_->width(); ++x)
    {
        for(int y = 0; y < console_->height(); ++y)
        {
            wsl::Color bgColor = console_->get(x,y).bgColor();
            if(bgColor != wsl::Color::Black)
            {
                bgCursorSprite.setTexPos(spriteRects_[219]); // 219 is the white square in the CP437 font
                bgCursorSprite.setPos(x * spriteSize_, y * spriteSize_);
            
                bgCursorSprite.render(renderer_, bgColor);
            }
            wsl::Rect & textureRect = spriteRects_[console_->get(x,y).symbol()];
            cursorSprite.setPos(x * spriteSize_, y * spriteSize_);
            cursorSprite.setTexPos(wsl::Rect(textureRect.x1, textureRect.y1, textureRect.w, textureRect.h));
            wsl::Color color = console_->get(x,y).color();

            cursorSprite.render(renderer_, color);
        }
    }
    
    // Display the SDL window
    SDL_RenderPresent(renderer_);
}
