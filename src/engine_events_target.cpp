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

void Engine::handleEvents_target_(Input input)
{
    if(input.move())
    {
        // Need to add logic here to make sure the cursor stays within certain distance of the player.
        cursorPos_ += input.dir();
    }
    if(input.enter() || input.quit())
    {
        // Target DOES NOT change game state - at the end of the targeting loop, the game returns to the function that called target
        targetSelected_ = true;
        std::cout << "Target selected.\n";
    }
    //Other target commands will go here, IE +/- for next/prev auto target (entity)
}
