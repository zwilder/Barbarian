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

// Bit flags are overkill and possibly not the best way to do this... 
enum Cmd : int
{
    NONE = 0,
    MOVE = 0x02,
    QUIT = 0x04,
    FULLSCREEN = 0x04,
    NEXT_LEVEL = 0x08
};
        

class Action
{
    public:
        Action(int cmd = Cmd::NONE);
        Action(int cmd, wsl::Vector2i delta);

        bool move() { return((cmdMask_ & Cmd::MOVE) == Cmd::MOVE); }
        bool quit() { return((cmdMask_ & Cmd::QUIT) == Cmd::QUIT); }
        bool fullscreen() { return((cmdMask_ & Cmd::FULLSCREEN) == Cmd::FULLSCREEN); }
        bool nextLevel() { return((cmdMask_ & Cmd::NEXT_LEVEL) == Cmd::NEXT_LEVEL); }

        wsl::Vector2i dir() { return dir_; }
    private:
        int cmdMask_;
        wsl::Vector2i dir_; 
 };

Action handleKeys(int key);

#endif //INPUT_HANDLERS_HPP
