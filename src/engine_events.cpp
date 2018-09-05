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
#include <ctime>

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
            input = handleKeys(event.key.keysym.sym, event.key.keysym.mod);
            keyPressed = true;
        }
    }

    // Evaluate the input to see if the engine needs to do anything.
    if(gameState_ == GameState::TITLE)
    {
        handleEvents_title_(input);
    }
    else if(gameState_ == GameState::PLAYERS_TURN)
    {
        if(input.sshot())
        {
            screenshot_();
        }
        else
        {
            handleEvents_player_(input);
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
    else if (gameState_ == GameState::INVENTORY || gameState_ == GameState::DROP || gameState_ == GameState::EQUIP)
    {
        if(input.sshot())
        {
            screenshot_();
        }
        else
        {
            handleEvents_inventory_(input);
        }
    }
    else if(gameState_ == GameState::GAME_OVER && keyPressed)
    {
        if(input.sshot())
        {
            screenshot_();
        }
        else
        {
            saveGame();
            changeState(GameState::RIP);
        }
    }
    else if(gameState_ == GameState::RIP)
    {
        if(input.sshot())
        {
            screenshot_();
        }
        else if(keyPressed)
        {
            changeState(GameState::TITLE);
        }
    }
    else if(gameState_ == GameState::TARGET)
    {
        handleEvents_target_(input);
    }
    else if(gameState_ == GameState::LOOK)
    {
        handleEvents_look_(input);
    }
    else if(gameState_ == GameState::LEVEL_UP)
    {
        handleEvents_levelup_(input);
    }

    if(input.escape())
    {
        if(gameState_ == GameState::INVENTORY || gameState_ == GameState::DROP)
        {
            changeState(prevGameState_);
        }
    }
    if(input.quit())
    {
        running_ = false;
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
}

void Engine::screenshot_()
{
    // Take screenshot
    std::time_t t = std::time(0);
    std::tm * now = std::localtime(&t);
    std::string mon = now->tm_mon + 1 < 10 ? "0" + std::to_string(now->tm_mon + 1) : std::to_string(now->tm_mon + 1);
    std::string day = now->tm_mday < 10 ? "0" + std::to_string(now->tm_mday) : std::to_string(now->tm_mday);
    std::string date = mon  + "_" + day  + "_" + std::to_string(1900 + now->tm_year);
    std::string time = std::to_string(now->tm_hour) + std::to_string(now->tm_min) + std::to_string(now->tm_sec);
    std::string filename = "ss-" + date + "-" + time + ".png";
    SDL_Surface *sshot = SDL_CreateRGBSurface(0, windowWidth_, windowHeight_, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    // int w = 800;
    // int h = 600;
    // SDL_Surface *sshot = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer_, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    // SDL_SaveBMP(sshot, filename.c_str());
    IMG_SavePNG(sshot, filename.c_str());
    SDL_FreeSurface(sshot);
}
