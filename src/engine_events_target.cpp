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
        wsl::Vector2i newPos = cursorPos_ + input.dir();
        if(fov::contains(visible_.get(), newPos))
        {
            cursorPos_ = newPos;
            Entity * actor = gameMap_->actorAt(cursorPos_);
            Entity * item = gameMap_->itemAt(cursorPos_);
            
            if(actor)
            {
                addMessage("A " + actor->name() + ".");
            }
            else if(item)
            {
                if(item->quantity() > 1)
                {
                    addMessage("Some " + item->name() + "s.");
                }
                else
                {
                    addMessage("A " + item->name() + ".");
                }
            }
            advanceMsg_();
        }
    }
    if(input.enter())
    {
        // Target DOES NOT change game state - at the end of the targeting loop, the game returns to the function that called target
        targetSelected_ = true;
        targeting_ = false;
    }
    if(input.escape())
    {
        targeting_ = false;
    }
    //Other target commands will go here, IE +/- for next/prev auto target (entity)
}

void Engine::handleEvents_look_(Input input)
{
    if(input.move())
    {
        wsl::Vector2i newPos = cursorPos_ + input.dir();
        if(newPos.x > console_->width())
        {
            newPos.x = console_->width();
        }
        if(newPos.x < 0)
        {
            newPos.x = 0;
        }
        if(newPos.y > console_->height())
        {
            newPos.y = console_->height();
        }
        if(newPos.y < 0)
        {
            newPos.y = 0;
        }
        cursorPos_ = newPos;
        Entity * actor = gameMap_->actorAt(cursorPos_);
        Entity * item = gameMap_->itemAt(cursorPos_);
        Tile & tile = gameMap_->tileAt(cursorPos_);
        
        if(tile.visible() || tile.explored())
        {
            if(actor)
            {
                addMessage("You see a " + actor->name() + ".");
            }
            else if(item)
            {
                if(item->quantity() > 1)
                {
                    addMessage("You see some " + item->name() + "s.");
                }
                else
                {
                    addMessage("You see a " + item->name() + ".");
                }
            }
            else
            {
                if(tile.isWall())
                {
                    addMessage("You see an old, crumbling brick wall.");
                }
                else if(tile.isFloor())
                {
                    addMessage("You see the dirty, bloodstained ground.");
                }
            }
            advanceMsg_();
        }
        else
        {
            addMessage("You see nothing, except the oppressive darkness.");
            advanceMsg_();
        }
    }
    if(input.enter() || input.escape())
    {
        // Target DOES NOT change game state - at the end of the targeting loop, the game returns to the function that called target
        // targetSelected_ = false;
        targeting_ = false;
    }
    //Other target commands will go here, IE +/- for next/prev auto target (entity)
}
