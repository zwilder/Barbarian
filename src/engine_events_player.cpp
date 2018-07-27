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
                actor->takeDamage(player_->power() - actor->defense());
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
            else
            {
                move = true;
            }

            if(move)
            {
                player_->move(input.dir()); // Need to move this to the player's "update" routine, so the player takes their turn in proper order.
                fov::visible(visible_.get(), gameMap_.get(), player_);
            }
        }
        changeState(GameState::ENEMY_TURN);
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
            player_->pickup(itemEntity);
            if(itemEntity->quantity() > 1)
            {
                addMessage("You pickup the " + itemEntity->name() + "s.");
            }
            else
            {
                addMessage("You pickup the " + itemEntity->name() + ".");
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
        *gameMap_ = GameMap(this, consoleWidth_, consoleHeight_, maxRoomSize_, minRoomSize_, maxRooms_);
        player_->setPos(gameMap_->rooms[0].center());
        fov::visible(visible_.get(), gameMap_.get(), player_);
        // Tell gamemap to place some enemies
        entityList_.clear();
        gameMap_->placeActors(2);
        gameMap_->placeItems(5);
    }

    if(input.look())
    {
        look();
    }
}
