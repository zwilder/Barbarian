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

void Engine::draw_inventory_()
{
    if(gameState_ == GameState::INVENTORY)
    {
        console_->print(0,0, "Inventory");
    }
    else if(gameState_ == GameState::DROP)
    {
        console_->print(0,0, "Select the item you wish to drop:");
    }
    else if(gameState_ == GameState::EQUIP)
    {
        console_->print(0,0, "Equipment");
    }

    console_->print(0,2, "---------");
    if(player_->inventory()->isEmpty())
    {
        console_->print(0,3, "Your inventory is empty.");
    }
    else
    {
        int i = 0;
        for(wsl::PQNode<Entity, int> * temp = player_->inventory()->head(); temp != NULL; temp = temp->next)
        {
            Entity & item = temp->data;
            std::string name = item.name();
            name[0] = toupper(name[0]);
            int nameSize = int(name.size());
            
            console_->print(0, int(i) + 3, std::string(1, char(i+97)));
            console_->print(1, int(i) + 3, ": " + name); 
            if(item.stackable())
            {
                console_->print(nameSize + 4, int(i) + 3, "x " + std::to_string(item.quantity()));
            }
            else if(item.quantity() >= 1)
            {
                console_->print(nameSize + 4, int(i) + 3, "x " + std::to_string(item.quantity()) + " charges");
            }

            if(item.isEquipment())
            {
                if(item.equipped())
                {
                    std::string slot = "";
                    if(item.equipment().check(Equipment::Flags::MAIN_HAND)) slot = "Main Hand";
                    if(item.equipment().check(Equipment::Flags::OFF_HAND)) slot = "Off Hand";
                    if(item.equipment().check(Equipment::Flags::BODY)) slot = "Body";
                    if(item.equipment().check(Equipment::Flags::BACK)) slot = "Back";
                    if(item.equipment().check(Equipment::Flags::LRING)) slot = "Left Ring";
                    if(item.equipment().check(Equipment::Flags::RRING)) slot = "Right Ring";
                    if(item.equipment().check(Equipment::Flags::BOOTS)) slot = "Boots";
                    if(item.equipment().check(Equipment::Flags::RANGED)) slot = "Ranged";
                    if(item.equipment().check(Equipment::Flags::AMMO)) slot = "Ammo";
                    // std::string slot = (item.isMainHand() ? "Main Hand" : "Off Hand"); // This will obviously need to change when more slots added
                    console_->printf(nameSize + 4, int(i) + 3, " [Equipped - " + slot + "]", wsl::Color::Orange);
                }
            }
            ++i;
        }
    }
    console_->print(0, console_->height() - 1, "Press [a-z] to select, [Esc] to exit");
}
