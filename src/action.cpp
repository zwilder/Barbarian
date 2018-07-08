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
#include "../include/tile.hpp"
#include "../include/action.hpp"

Action::Action()
{
    mask_ = Flags::NONE;
    alternateMask_ = Flags::NONE;
    actor_ = NULL;
    other_ = NULL;
    tile_ = NULL;
    pos_ = wsl::Vector2i();
}

Action::Action(int mask, Entity * actor, Entity * other, Tile * tile, wsl::Vector2i pos) : mask_(mask), actor_(actor), other_(other), tile_(tile), pos_(pos)
{
    alternateMask_ = Flags::NONE;
}

void Action::perform()
{
    if(check(Flags::ATTACK))
    {
        attack_();
    }
    else if(check(Flags::WALK))
    {
        move_();
    }
    else if(check(Flags::REST))
    {
        rest_();
    }
    else
    {
        remove(Flags::SUCCESS);
    }
}

void Action::attack_()
{
    if(pos_ == wsl::Vector2i(0,0))
    {
        remove(Flags::SUCCESS);
        alternateMask_ = Flags::REST;
    }
    else if(other_ == NULL)
    {
        remove(Flags::SUCCESS);
        alternateMask_ = Flags::WALK;
    }
    else
    {
        //Attack!
        engage(Flags::SUCCESS);
    }
}

void Action::move_()
{
    if(tile_->blocksMovement())
    {
        remove(Flags::SUCCESS);
    }
    else if(pos_ == wsl::Vector2i(0,0))
    {
        remove(Flags::SUCCESS);
        alternateMask_ = Flags::REST;
    }
    else
    {
        actor_->move(pos_);
        engage(Flags::SUCCESS);
    }
}

void Action::rest_()
{
    // Other stuff can happen here, like healing or whatever.
    engage(Flags::SUCCESS);
}

