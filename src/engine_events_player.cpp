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

void Engine::handleEvents_player_(Input input)
{
    if(input.move())
    {
        wsl::Vector2i dPos = player_->pos() + input.dir();
        if(!gameMap_->tileAt(dPos).blocksMovement())
        {
            Entity * actor = gameMap_->actorAt(dPos);
            Entity * item = gameMap_->itemAt(dPos);
            bool move = false;
            if(actor)
            {
                addMessage("You attack the " + actor->name() + " for " + std::to_string(player_->power() - actor->defense()) + " damage!");
                // actor->takeDamage(player_->power() - actor->defense());
                player_->dealDamage(actor, player_->power() - actor->defense());
                if(gameState_ != GameState::LEVEL_UP)
                {
                    changeState(GameState::ENEMY_TURN);
                }
            }
            else if(item)
            {
                move = true;
                if(item->quantity() > 1)
                {
                    addMessage("You see " + std::to_string(item->quantity()) + " " + item->name() + "s here.");
                }
                else
                {
                    addMessage("You see a " + item->name() + " here.");
                }
            }
            else if(gameMap_->tileAt(dPos).isStairs())
            {
                addMessage("You see a dark staircase winding downwards into the unknown.");
                move = true;
            }
            else
            {
                move = true;
            }

            if(move)
            {
                player_->move(input.dir()); // Need to move this to the player's "update" routine, so the player takes their turn in proper order.
                fov::visible(visible_.get(), gameMap_.get(), player_);
                changeState(GameState::ENEMY_TURN);
            }
        }
    }

    if(input.get())
    {
        Entity * itemEntity = gameMap_->itemAt(player_->pos());
        if(itemEntity == NULL)
        {
            addMessage("You see no item here.");
        }
        else
        {
            std::string itemName = itemEntity->name();
            player_->pickup(itemEntity);
            if(itemEntity->quantity() > 1)
            {
                addMessage("You pickup the " + itemName + "s.");
            }
            else
            {
                addMessage("You pickup the " + itemName + ".");
            }
        }
        changeState(GameState::ENEMY_TURN);
    }

    if(input.openInv())
    {
        changeState(GameState::INVENTORY);
    }

    if(input.openDrop())
    {
        changeState(GameState::DROP);
    }

    if(input.nextLevel())
    {
        if(gameMap_->tileAt(player_->pos()).isStairs())
        {
            addMessage("You descend deeper into the dungeon...");
            gameMap_->nextLevel();
            fov::visible(visible_.get(), gameMap_.get(), player_);
            advanceMsg_();
        }
        else
        {
            addMessage("You search for a way to move downwards, but find nothing."); 
            changeState(GameState::ENEMY_TURN);
        }
    }

    if(input.look())
    {
        look();
    }
}
