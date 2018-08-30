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
#include "../include/engine.hpp"

Equipment::Equipment(int s, int p, int d, int h) : powerBonus(p), defenseBonus(d), healthBonus(h)
{
    set(s);
}

void Entity::makeEquipment(Equipment equipment)
{
    if(!isItem())
    {
        makeItem(Item(Item::Flags::EQUIP, 1, false));
    }
    engage(Flags::EQUIPMENT);
    equipment_ = std::make_shared<Equipment>();
    *equipment_ = equipment;
}

/*
 * This function is kinda a disaster to read - I'm sure theres a better (cleaner) way of doing this, but when all else fails
 * those good ol' if/then/if else statements never do.
 */
void Entity::toggleEquip(Entity * item)
{
    if(!item)
    {
        return;
    }
    // This function is called by an actorEntity trying to equip an itemEntity
    // Entity & item = itemNode->data;
    if(!item->check(Flags::EQUIPMENT))
    {
        game_->addMessage(name() + " can't seem to figure out how to equip the " + item->name() + "!");
    }

    // Check if the actor has an item already occupying the slot in the item occupies
    if(item->isMainHand())
    {
        if(actor_->check(Actor::Flags::EQUIP_MAIN_HAND))
        {
            // Actor has an item equipped in the main hand, unequip it
            Entity * mainHandItem = getMainHand();
            actor_->remove(Actor::Flags::EQUIP_MAIN_HAND);
            mainHandItem->equipment_->remove(Equipment::Flags::EQUIPPED);
            if(item != mainHandItem)
            {
                game_->addMessage(name() + " tried to equip a " + item->name() + ", but had to stop wielding a " + mainHandItem->name() + " first.");
            }
            else
            {
                game_->addMessage(name() + " unequips the " + item->name() + ".");
            }
        }
        else
        {
            // Actor has nothing equipped in the main hand, equip item
            actor_->engage(Actor::Flags::EQUIP_MAIN_HAND);
            item->equipment_->engage(Equipment::Flags::EQUIPPED);
            game_->addMessage(name() + " wields the " + item->name() + "!");
        }
    }
    else if(item->isOffHand())
    {
        if(actor_->check(Actor::Flags::EQUIP_OFF_HAND))
        {
            // Actor has an item equipped in the off hand, unequip it
            Entity * offHandItem = getOffHand();
            actor_->remove(Actor::Flags::EQUIP_OFF_HAND);
            offHandItem->equipment_->remove(Equipment::Flags::EQUIPPED);
            if(item != offHandItem)
            {
                game_->addMessage(name() + " tried to equip a " + item->name() + ", but had to stop wielding a " + offHandItem->name() + " first.");
            }
            else
            {
                game_->addMessage(name() + " unequips the " + item->name() + ".");
            }
        }
        else
        {
            // Actor has nothing equipped in the off hand, equip item
            actor_->engage(Actor::Flags::EQUIP_OFF_HAND);
            item->equipment_->engage(Equipment::Flags::EQUIPPED);
            game_->addMessage(name() + " readies the " + item->name() + "!");
        }
    }
}

Entity * Entity::getMainHand()
{
    Entity * result = NULL;
    if(hasInventory())
    {
        //Iterate through inventory, checking each item looking for Equipment::Flags::MAIN_HAND.
        //when found, if equipped set result to item and break.
        for(wsl::PQNode<Entity, int> * node = inventory_->head(); node != NULL; node = node->next)
        {
            Entity * item = &node->data;
            if(item->isEquipment())
            {
                if(item->isMainHand() && item->equipped())
                {
                    result = item;
                    break;
                }
            }
        }
    }

    return result;
}

Entity * Entity::getOffHand()
{
    Entity * result = NULL;

    if(hasInventory())
    {
        //Iterate through inventory, checking each item looking for Equipment::Flags::MAIN_HAND.
        //when found, if equipped set result to item and break.
        for(wsl::PQNode<Entity, int> * node = inventory_->head(); node != NULL; node = node->next)
        {
            Entity * item = &node->data;
            if(item->isEquipment())
            {
                if(item->isOffHand() && item->equipped())
                {
                    result = item;
                    break;
                }
            }
        }
    }
    return result;
}
