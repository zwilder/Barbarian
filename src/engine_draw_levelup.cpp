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

void Engine::draw_levelup_()
{
    console_->print(0,0,"Your skill in battle increases! Welcome to level " + std::to_string(player_->currentLevel()));
    console_->print(0,2, "---------");
    console_->print(0,4,"Select a skill to increase");
    console_->print(0,5, "a: Constitution (+20 HP, from " + std::to_string(player_->maxHP()) + ")");
    console_->print(0,6, "b: Strength (+1 attack, from " + std::to_string(player_->power()) + ")");
    console_->print(0,7, "c: Dexterity (+1 defense, from " + std::to_string(player_->defense()) + ")");
}
