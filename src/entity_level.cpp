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

#include "../include/entity.hpp"

Level::Level(int cLvl, int cXP, int lvlUB, int lvlUF) : currentLevel(cLvl), currentXP(cXP), levelUpBase(lvlUB), levelUpFactor(lvlUF)
{
    //
}

void Entity::makeLevel(Level level)
{
    engage(Flags::LEVEL);
    level_ = std::make_shared<Level>();
    *level_ = level;
}

bool Entity::addXP(int xp)
{
    level_->currentXP += xp;
    if(level_->currentXP > xpToNextLevel())
    {
        level_->currentXP -= xpToNextLevel();
        level_->currentLevel += 1;

        return true;
    }
    
    return false;
}

int Entity::xpToNextLevel()
{
    return (level_->levelUpBase + (level_->currentLevel * level_->levelUpFactor));
}
