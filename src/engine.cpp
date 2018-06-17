#include <iostream>
#include "../include/engine.hpp"

Engine::Engine()
{
    running_ = init();
}

bool Engine::init()
{
    bool success = true;

    // Set up the console and the physical window
    consoleWidth_ = 80; // consoleWidth_ and consoleHeight_ refer to the 'root' console
    consoleHeight_ = 50;
    spriteSize_ = 12;
    windowWidth_ = consoleWidth_ * spriteSize_;
    windowHeight_ = consoleHeight_ * spriteSize_;
    console_ = new wsl::Console(consoleWidth_, consoleHeight_); // if we add further consoles we can reduce the area this takes up on 'root'
    window_ = new sf::RenderWindow(sf::VideoMode(windowWidth_,windowHeight_), "Barbarian!", sf::Style::None);

    // Setup the cp437 font
    spritesheet_ = new sf::Texture;
    if(!spritesheet_->loadFromFile("assets/cp437_12x12.png"))
    {
        success = false;
    }
    
    // Pre-create all sprites, not sure if this is advantageous but it seemed like a good idea at the time
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

    // Setup the game map width/height
    maxRoomSize_ = 10;
    minRoomSize_ = 6;
    maxRooms_ = 30; 
    gameMap_ = new GameMap(consoleWidth_, consoleHeight_, maxRoomSize_, minRoomSize_, maxRooms_);

    // Temporary 
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
                action = handleKeys(event.key.code);
                break;
            }
            default: { break; }
        }
    }

    if(action.quit())
    {
        running_ = false;
    }
    if(action.move())
    {
        console_->flush();
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
    //
}

void Engine::draw()
{
    //Update GameMap on console
    for(int x = 0; x < console_->width(); ++x)
    {
        for(int y = 0; y < console_->height(); ++y)
        {
            int index = console_->index(x,y);
            console_->put(x,y, gameMap_->tiles[index].glyph());
        }
    }

    //Update entity positions on console_
    console_->put(player_.pos().x, player_.pos().y, player_.glyph());

    // Since all the sprites are precreated in spriteChars_, the draw function creates new sprites from the template to represent the current glyph on
    // the console.
    window_->clear();
    
    sf::Sprite sprites[console_->width() * console_->height()];
    
    for(int x = 0; x < console_->width(); ++x)
    {
        for(int y = 0; y < console_->height(); ++y)
        {
            int index = console_->index(x,y);
            // std::cout << index << std::endl;
            sprites[index] = spriteChars_[console_->get(x,y).symbol()];
            sprites[index].setPosition(sf::Vector2f(spriteSize_ * x, spriteSize_ * y));
            wsl::Color color = console_->get(x,y).color();
            sprites[index].setColor(sf::Color(color.r(),color.g(),color.b()));
            window_->draw(sprites[index]);            
        }
    }
    
    window_->display();
}
