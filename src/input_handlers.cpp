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
   dir_ = wsl::Vector2i();
   alpha_ = char(0);
   mod_ = KMOD_NONE;
}

Input::Input(int cmd, wsl::Vector2i delta, char alpha, int mod) : cmdMask_(cmd), dir_(delta), alpha_(alpha), mod_(mod)
{
    //
}

Input handleKeys(int key, int mod)
{
    switch(key)
    {

        case SDLK_a: return Input(Cmd::NONE, wsl::Vector2i(), 'a', mod);

        case SDLK_b:
        case SDLK_KP_1:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(-1,1), 'b', mod);
        }
        
        case SDLK_c: return Input(Cmd::NONE, wsl::Vector2i(), 'c', mod);

        case SDLK_d:
        {
            return Input(Cmd::OPEN_DROP, wsl::Vector2i(), 'd', mod);
        }

        case SDLK_e: return Input(Cmd::NONE, wsl::Vector2i(), 'e', mod);
        case SDLK_f: return Input(Cmd::NONE, wsl::Vector2i(), 'f', mod);

        case SDLK_g:
        {
            return Input(Cmd::GET, wsl::Vector2i(), 'g', mod);
        }

        case SDLK_h:
        case SDLK_LEFT:
        case SDLK_KP_4:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(-1,0), 'h', mod);
        }
        
        case SDLK_i:
        {
            return Input(Cmd::OPEN_INV, wsl::Vector2i(), 'i', mod);
        }

        case SDLK_j:
        case SDLK_DOWN:
        case SDLK_KP_2:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(0,1), 'j', mod); 
        }

        case SDLK_k:
        case SDLK_UP:
        case SDLK_KP_8:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(0,-1), 'k', mod);
        }

        case SDLK_l:
        {
            if(mod & KMOD_SHIFT)
            {
                return Input(Cmd::LOOK, wsl::Vector2i(0,0), 'L', mod);
            }
        }
        case SDLK_RIGHT:
        case SDLK_KP_6:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(1,0), 'l', mod);
        }
        
        case SDLK_m: return Input(Cmd::NONE, wsl::Vector2i(), 'm', mod);

        case SDLK_n:
        case SDLK_KP_3:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(1,1), 'n', mod);
        }

        case SDLK_o: return Input(Cmd::NONE, wsl::Vector2i(), 'o', mod);
        case SDLK_p: return Input(Cmd::NONE, wsl::Vector2i(), 'p', mod);
        case SDLK_q:
        {
            if(mod & KMOD_SHIFT)
            {
                return Input(Cmd::QUIT, wsl::Vector2i(0,0), 'Q', mod);
            }
            else
            {
                return Input(Cmd::NONE, wsl::Vector2i(), 'q', mod);
            }
        }
        case SDLK_r: return Input(Cmd::NONE, wsl::Vector2i(), 'r', mod);

        case SDLK_s: return Input(Cmd::NONE, wsl::Vector2i(), 's', mod);
        case SDLK_t: return Input(Cmd::NONE, wsl::Vector2i(), 't', mod);

        case SDLK_u:
        case SDLK_KP_9:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(1,-1), 'u', mod);
        }

        case SDLK_v: return Input(Cmd::NONE, wsl::Vector2i(), 'v', mod);
        case SDLK_w: return Input(Cmd::NONE, wsl::Vector2i(), 'w', mod);
        case SDLK_x: return Input(Cmd::NONE, wsl::Vector2i(), 'x', mod);

        case SDLK_y:
        case SDLK_KP_7:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(-1,-1), 'y', mod);
        }

        case SDLK_z: return Input(Cmd::NONE, wsl::Vector2i(), 'z', mod);

        case SDLK_KP_5:
        case SDLK_KP_PERIOD:
        case SDLK_PERIOD:
        {
            return Input(Cmd::MOVE, wsl::Vector2i(0,0), 0, mod);
        };

        case SDLK_ESCAPE:
        {
            return Input(Cmd::ESCAPE, wsl::Vector2i(0,0), 0, mod);
        }

        case SDLK_RETURN:
        case SDLK_KP_ENTER:
        {
            return Input(Cmd::ENTER, wsl::Vector2i(0,0), 0, mod);
        }
        case SDLK_F1:
        {
            return Input(Cmd::FULLSCREEN);
        }
        default: { break; }
    }

    return Input(Cmd::NONE);
}
