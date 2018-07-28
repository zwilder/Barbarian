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

void Engine::handleEvents_inventory_(Input input)
{
    if(input.alpha() >= 'a' && input.alpha() <= 'z')
    {
        int index = int(input.alpha() - 97);
        wsl::DLNode<Entity> * itemNode = player_->inventory()->at(index);
        if(!itemNode)
        {
            return;
        }
        if(gameState_ == GameState::INVENTORY)
        {
            // if(itemNode)
            // {
                player_->use(index);
                // addMessage("You use the " + itemNode->data.name() + "!");
                changeState(GameState::ENEMY_TURN);
            // }
        }
        else if (gameState_ == GameState::DROP)
        {
            // if(itemNode)
            // {
                player_->drop(index);
                if(itemNode->data.quantity() > 1 )
                {
                    addMessage("You drop the " + itemNode->data.name() + "s.");
                }
                else
                {
                    addMessage("You drop the " + itemNode->data.name() + ".");
                }
                changeState(GameState::ENEMY_TURN);
            // }
        }
        else if (gameState_ == GameState::EQUIP)
        {
            //
        }
    }
}
