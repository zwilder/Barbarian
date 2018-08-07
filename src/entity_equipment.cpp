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

Equipment::Equipment(int s, int p, int d, int h) : powerBonus(p), damageBonus(d), healthBonus(h)
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
        game_->addMessage(name_ + " can't seem to figure out how to equip the " + item->name() "!");
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
            game_->addMessage(name_ + " tried to equip a " + item->name() + ", but had to stop wielding a " + mainHandItem->name() + " first.");
        }
        else
        {
            // Actor has nothing equipped in the main hand, equip item
            actor_->engage(Actor::Flags::EQUIP_MAIN_HAND);
            item->equipment_->engage(Equipment::Flags::EQUIPPED);
            game_->addMessage(name_ + " wields the " + item->name() + "!");
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
            game_->addMessage(name_ + " tried to equip a " + item->name() + ", but had to stop wielding a " + offHandItem->name() + " first.");
        }
        else
        {
            // Actor has nothing equipped in the off hand, equip item
            actor_->engage(Actor::Flags::EQUIP_OFF_HAND);
            item->equipment_->engage(Equipment::Flags::EQUIPPED);
            game_->addMessage(name_ + " readies the " + item->name() + "!");
        }
    }
}

Entity * Entity::getMainHand()
{
    Entity * result = NULL;

    return result;
}

Entity * Entity::getOffHand()
{
    Entity * result = NULL;

    return result;
}
