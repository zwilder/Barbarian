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

void Engine::handleEvents()
{
    // Poll the window for user input events (SDL)
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
        handleEvents_player_(input);
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
    else if (gameState_ == GameState::INVENTORY || gameState_ == GameState::DROP || gameState_ == GameState::EQUIP)
    {
        handleEvents_inventory_(input);
    }
    else if(gameState_ == GameState::GAME_OVER && keyPressed)
    {
        newGame();
    }
}
