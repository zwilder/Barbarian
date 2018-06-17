#include <iostream>
#include "../include/engine.hpp"

Engine::Engine()
{
    running_ = init();
}

bool Engine::init()
{
    bool success = true;

    // Set up the virtual console
    consoleWidth_ = 80; // consoleWidth_ and consoleHeight_ refer to the 'root' console
    consoleHeight_ = 50;
    spriteSize_ = 12;
    console_ = new wsl::Console(consoleWidth_, consoleHeight_); // if we add further consoles we can reduce the area this takes up on 'root'

    // Set up the physical window (SFML)
    windowWidth_ = consoleWidth_ * spriteSize_;
    windowHeight_ = consoleHeight_ * spriteSize_;
    window_ = new sf::RenderWindow(sf::VideoMode(windowWidth_,windowHeight_), "Barbarian!", sf::Style::None);

    // Load the cp437 texture image (SFML)
    spritesheet_ = new sf::Texture;
    if(!spritesheet_->loadFromFile("assets/cp437_12x12.png"))
    {
        success = false;
    }
    
    // Create sprite 'templates' for all sprites on the spritesheet (SFML)
    int x = 0;
    int y = 0;
    for(int i = 0; i < 256; ++i)
    {
        spriteChars_[i].setTexture(*spritesheet_);
        spriteChars_[i].setTextureRect(sf::IntRect(x,y, spriteSize_,spriteSize_));
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
    maxRoomSize_ = 10;
    minRoomSize_ = 6;
    maxRooms_ = 30; 
    gameMap_ = new GameMap(consoleWidth_, consoleHeight_, maxRoomSize_, minRoomSize_, maxRooms_);

    // Create empty vector to hold entities, and add the player entity - Should also be a separate function,
    // which would facilitate a character creation option in the future. 
    player_ = Entity(wsl::Vector2i(gameMap_->width() / 2,gameMap_->height() / 2), wsl::Glyph('@'));
    player_.setPos(gameMap_->rooms[0].center());

    return success;
}

void Engine::cleanup()
{
    delete spritesheet_;
    delete gameMap_;
    window_->close();
    delete window_;
    delete console_;
}

void Engine::handleEvents()
{
    // Poll the window for user input events (SFML)
    sf::Event event;
    Action action;
    while(window_->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                running_ = false;
                break;
            }
            case sf::Event::KeyPressed:
            {
                action = handleKeys(event.key.code); // Pass the keycode of a keyboard press to a separate function for handling.
                break;
            }
            default: { break; }
        }
    }

    // Evaluate the action to see if the engine needs to do anything.
    if(action.quit())
    {
        running_ = false;
    }
    if(action.move())
    {
        // console_->flush();
        wsl::Vector2i dPos = player_.pos() + action.dir();
        if(!gameMap_->isBlocked(dPos.x,dPos.y))
        {
            player_.move(action.dir());
        }
    }
    if(action.nextLevel())
    {
        *gameMap_ = GameMap(consoleWidth_, consoleHeight_, maxRoomSize_, minRoomSize_, maxRooms_);
        player_.setPos(gameMap_->rooms[0].center());
    }
}

void Engine::update()
{
    // Entity update routines will go here, eventually.
}

void Engine::draw()
{
    // Render order, GameMap (Tiles) >> Items >> Stairs >> Entities.
    //Translate GameMap to virtual console (right now this is the 'root' console)
    for(int x = 0; x < console_->width(); ++x)
    {
        for(int y = 0; y < console_->height(); ++y)
        {
            int index = console_->index(x,y);
            console_->put(x,y, gameMap_->tiles[index].glyph());
        }
    }

    //Place entity positions on console_
    console_->put(player_.pos().x, player_.pos().y, player_.glyph());

    // Clear the SFML window
    window_->clear();
    
    // Create SFML sprites from the template sprites in spriteChars_ to represent the characters on the virtual console, and draw them to the screen
    sf::Sprite sprites[console_->width() * console_->height()];
    
    for(int x = 0; x < console_->width(); ++x)
    {
        for(int y = 0; y < console_->height(); ++y)
        {
            int index = console_->index(x,y);
            sprites[index] = spriteChars_[console_->get(x,y).symbol()];
            sprites[index].setPosition(sf::Vector2f(spriteSize_ * x, spriteSize_ * y));
            wsl::Color color = console_->get(x,y).color();
            sprites[index].setColor(sf::Color(color.r,color.g,color.b));
            window_->draw(sprites[index]);            
        }
    }
    
    // Display the SFML window
    window_->display();
}
