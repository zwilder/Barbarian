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


#pragma once
#ifndef INPUT_HANDLERS_HPP
#define INPUT_HANDLERS_HPP

#include "vector.hpp"

// Bit flags are possibly not the best way to do this...
enum Cmd : int
{
    NONE = 0,
    MOVE = 0x002,
    QUIT = 0x004,
    FULLSCREEN = 0x008,
    NEXT_LEVEL = 0x010,
    ENTER = 0x020,
    GET = 0x040,
    OPEN_INV = 0x080
};
        

class Input
{
    public:
        Input(int cmd = Cmd::NONE);
        Input(int cmd, wsl::Vector2i delta, char alpha = 0);

        bool move() { return((cmdMask_ & Cmd::MOVE) == Cmd::MOVE); }
        bool quit() { return((cmdMask_ & Cmd::QUIT) == Cmd::QUIT); }
        bool fullscreen() { return((cmdMask_ & Cmd::FULLSCREEN) == Cmd::FULLSCREEN); }
        bool nextLevel() { return((cmdMask_ & Cmd::NEXT_LEVEL) == Cmd::NEXT_LEVEL); }
        bool enter() { return((cmdMask_ & Cmd::ENTER) == Cmd::ENTER); }
        bool get() { return((cmdMask_ & Cmd::GET) == Cmd::GET); }
        bool openInv() { return((cmdMask_ & Cmd::OPEN_INV) == Cmd::OPEN_INV); }

        wsl::Vector2i dir() { return dir_; }
        char alpha() { return alpha_; }
    private:
        int cmdMask_;
        wsl::Vector2i dir_; 
        char alpha_;
 };

Input handleKeys(int key);

#endif //INPUT_HANDLERS_HPP
