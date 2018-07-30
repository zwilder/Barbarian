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

void Engine::handleEvents_title_(Input input)
{
//a - new game
//b - load game
//c - quit
//[esc]-[ctrl+q]-[shift+q]-[q]-[Q] - quit

    if(input.alpha() == 'a')
    {
        newGame();
    }
    if(input.alpha() == 'b')
    {
        if(!loadGame())
        {
            newGame();
        }
    }
    if(input.alpha() == 'c' || input.alpha() == 'q' || input.escape())
    {
        running_ = false;
    }
}
