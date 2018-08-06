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
#include <chrono>
#include <thread>
#include "../include/engine.hpp"
#include "../include/random.hpp"
#include "../include/monsters.hpp"

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
    // gameState_ = GameState::PLAYERS_TURN;
    gameState_ = GameState::TITLE;
    prevGameState_ = gameState_;

    currentMsg_ = "";

    running_ = init();

    uint32_t seed = uint32_t(std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count());
    engineRNG_ = std::make_shared<wsl::RNGState>(123987445, seed); // Random numbers
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
        
        gameMap_ = std::make_unique<GameMap>();
        player_ = new Entity();
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

void Engine::advanceMsg_()
{
    if(!msgList_.isEmpty())
    {
        currentMsg_ = msgList_.popFront();
    }
    else
    {
        currentMsg_ = "";
    }
}

void Engine::changeState(GameState newState)
{
    prevGameState_ = gameState_;
    gameState_ = newState;
    if(newState == GameState::GAME_OVER)
    {
        prevGameState_ = newState;
    }
}

void Engine::revertState()
{
    gameState_ = prevGameState_;
}

void Engine::newGame()
{
    // This code is a mess and should be replaced eventually with something cleaner, less specific, and reusable.
    *gameMap_ = GameMap(this, consoleWidth_, consoleHeight_, maxRoomSize_, minRoomSize_, maxRooms_);

    // Create the player entity - this should eventually be from a character creation screen
    *player_ = monster::player(this, gameMap_->rooms[0].center());
    fov::visible(visible_.get(), gameMap_.get(), player_);

    // Tell gamemap to place some enemies
    entityList_.clear();
    gameMap_->placeActors(2);
    gameMap_->placeItems(5);
    gameState_ = GameState::PLAYERS_TURN;
    prevGameState_ = gameState_;
    msgList_.clear();
    currentMsg_ = "Your torch flickers briefly as you descend into the dungeon...";
}

wsl::Vector2i Engine::cursor()
{
    return cursorPos_;
}

void Engine::target(bool look)
{
    // This function is called by other functions to have the player move the cursor to a desired location,
    // select that location with [enter], and then the other function has access to the cursorPos via Engine::cursor();
    targetSelected_ = false;
    targeting_ = true;
    std::string prevMsg = currentMsg_;
    GameState prevState = gameState_;
    advanceMsg_();
    if(look)
    {
        changeState(GameState::LOOK);
        Entity * closestEntity = gameMap_->closestEntityTo(player_->pos());
        if(closestEntity)
        {
            if(fov::contains(visible(), closestEntity->pos()))
            {
                cursorPos_ = closestEntity->pos(); // This is temporary, Look selects the closest Entity, Target selects the closest Actor
                handleEvents_look_(Input(Input::Cmd::MOVE, wsl::Vector2i(0,0)));
            }
            else
            {
                cursorPos_ = player_->pos();
                handleEvents_look_(Input(Input::Cmd::MOVE, wsl::Vector2i(0,0)));
            }
        }
    }
    else
    {
        changeState(GameState::TARGET);
        Entity * target = gameMap_->closestActorTo(player_->pos());
        if(target)
        {
            if(fov::contains(visible(), target->pos()))
            {
                cursorPos_ = target->pos();   
                handleEvents_target_(Input(Input::Cmd::MOVE, wsl::Vector2i(0,0)));
            }
            else
            {
                cursorPos_ = player_->pos();
            }
        }
    }

    // Target is a mini-main loop - so this limits it's speed a bit
    using namespace std::chrono;
    const milliseconds MS_PER_FRAME = std::chrono::milliseconds(16); // 16ms = ~60fps, 33ms = ~30fps

    while(targeting_)
    {
        milliseconds start = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        handleEvents(); // moving the cursor, waiting for [enter] to set targetSelected_ to true
        draw(); // Drawing the path from the player to the cursor
        std::this_thread::sleep_for(milliseconds(start + MS_PER_FRAME - duration_cast<milliseconds>(system_clock::now().time_since_epoch())));
    } 
    changeState(prevState);
    addMessage(prevMsg);
    advanceMsg_();
}
