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


// #include <SFML/Window.hpp>
#include <SDL2/SDL.h>
#include "../include/input_handlers.hpp"

Input::Input(int cmd) : cmdMask_(cmd)
{
   //
}

Input::Input(int cmd, wsl::Vector2i delta) : cmdMask_(cmd), dir_(delta)
{
    //
}

Input handleKeys(int key)
{
    switch(key)
    {
        case SDLK_j:
        case SDLK_DOWN:
        case SDLK_KP_2:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(0,1)); 
        }
        case SDLK_h:
        case SDLK_LEFT:
        case SDLK_KP_4:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(-1,0));
        }
        case SDLK_k:
        case SDLK_UP:
        case SDLK_KP_8:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(0,-1));
        }
        case SDLK_l:
        case SDLK_RIGHT:
        case SDLK_KP_6:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(1,0));
        }
        case SDLK_y:
        case SDLK_KP_7:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(-1,-1));
        }
        case SDLK_u:
        case SDLK_KP_9:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(1,-1));
        }
        case SDLK_n:
        case SDLK_KP_3:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(1,1));
        }
        case SDLK_b:
        case SDLK_KP_1:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(-1,1));
        }
        case SDLK_KP_5:
        case SDLK_KP_PERIOD:
        case SDLK_PERIOD:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(0,0));
        };
        case SDLK_g:
        {
            return Input(Cmd::GET);
        }
        case SDLK_q:
        case SDLK_ESCAPE:
        {
            return Input(Cmd::QUIT);
        }
        case SDLK_RETURN:
        case SDLK_KP_ENTER:
        {
            return Input(Cmd::ENTER);
        }
        case SDLK_F1:
        {
            return Input(Cmd::FULLSCREEN);
        }
        default: { break; }
    }

    return Input(Cmd::NONE);
}
