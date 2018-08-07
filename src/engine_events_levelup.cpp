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

#include "../include/engine.hpp"

void Engine::handleEvents_levelup_(Input input)
{
    if(input.alpha() == 'a')
    {
        //Constitution
        player_->baseMaxHP() += 20;
        player_->hp() += 20;
        changeState(GameState::PLAYERS_TURN);
    }
    else if(input.alpha() == 'b')
    {
        //Strength
        player_->basePower() += 1;
        changeState(GameState::PLAYERS_TURN);
    }
    else if(input.alpha() == 'c')
    {
        //Dexterity
        player_->baseDefense() += 1;
        changeState(GameState::PLAYERS_TURN);
    }
}
