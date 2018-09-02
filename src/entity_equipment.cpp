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
    int slotFlag = getSlot(item);
    if(hasEquippedInSlot(slotFlag))
    {
        // Try unequipping your ITEMINSLOT first!
        Entity * oldItem = itemInSlot(slotFlag);
        actor_->remove(actorSlot(slotFlag)); // actorSlot turns Equipment::Flag into Actor::Flag
        oldItem->equipment_->remove(Equipment::Flags::EQUIPPED);
        if(item != oldItem)
        {
            game_->addMessage(name() + " tried to equip a " + item->name() + ", but had to stop wielding a " + oldItem->name() + " first.");
        }
        else
        {
            game_->addMessage(name() + " unequips the " + item->name() + ".");
        }
    }
    else
    {
        // Equip the ITEM
        actor_->engage(actorSlot(slotFlag));
        item->equipment_->engage(Equipment::Flags::EQUIPPED);
        game_->addMessage(name() + " wields the " + item->name() + "!");
    }
    /*
    if(item->isMainHand())
    {
        if(actor_->check(Actor::Flags::EQUIP_MAIN_HAND))
        {
            // Actor has an item equipped in the main hand, unequip it
            // Entity * mainHandItem = getMainHand();
            Entity * mainHandItem = itemInSlot(Equipment::Flags::MAIN_HAND);
            actor_->remove(Actor::Flags::EQUIP_MAIN_HAND); // Remove slot equipped flag from actor
            mainHandItem->equipment_->remove(Equipment::Flags::EQUIPPED); // Remove equipped status from item
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
            // Entity * offHandItem = getOffHand();
            Entity * offHandItem = itemInSlot(Equipment::Flags::OFF_HAND);
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
    */
}

Entity * Entity::itemInSlot(int slotFlag)
{
    Entity * result = NULL;
    if(hasInventory())
    {
        for(wsl::PQNode<Entity, int> * node = inventory_->head(); node != NULL; node = node->next)
        {
            Entity * item = &node->data;
            if(item->isEquipment())
            {
                if(item->equipment().check(slotFlag) && item->equipped())
                {
                    result = item;
                    break;
                }
            }
        }
    }
    return result;
}

int Entity::getSlot(Entity * item)
{
    // Returns the item's equipment flags stripped of the excess flags
    //  like EQUIPPED - the result is the slot the item equips to.
    int result = Equipment::Flags::NONE;
    if(item->isEquipment())
    {
        result = item->equipment_->mask();
        result &= ~(Equipment::Flags::EQUIPPED);
    }
    return result;
}

int Entity::actorSlot(int equipmentSlot)
{
    int result = Actor::Flags::NONE;
    if((equipmentSlot & Equipment::Flags::MAIN_HAND) == Equipment::Flags::MAIN_HAND)
    {
        result |= Actor::Flags::EQUIP_MAIN_HAND;
    }
    else if((equipmentSlot & Equipment::Flags::OFF_HAND) == Equipment::Flags::OFF_HAND)
    {
        result |= Actor::Flags::EQUIP_OFF_HAND;
    }
    else if((equipmentSlot & Equipment::Flags::BODY) == Equipment::Flags::BODY)
    {
        result |= Actor::Flags::EQUIP_BODY;
    }
    else if((equipmentSlot & Equipment::Flags::BACK) == Equipment::Flags::BACK)
    {
        result |= Actor::Flags::EQUIP_BACK;
    }
    else if((equipmentSlot & Equipment::Flags::LRING) == Equipment::Flags::LRING)
    {
        result |= Actor::Flags::EQUIP_LRING;
    }
    else if((equipmentSlot & Equipment::Flags::RRING) == Equipment::Flags::RRING)
    {
        result |= Actor::Flags::EQUIP_RRING;
    }
    else if((equipmentSlot & Equipment::Flags::BOOTS) == Equipment::Flags::BOOTS)
    {
        result |= Actor::Flags::EQUIP_BOOTS;
    }
    else if((equipmentSlot & Equipment::Flags::RANGED) == Equipment::Flags::RANGED)
    {
        result |= Actor::Flags::EQUIP_RANGED;
    }
    else if((equipmentSlot & Equipment::Flags::AMMO) == Equipment::Flags::AMMO)
    {
        result |= Actor::Flags::EQUIP_AMMO;
    }
    return result;
}

bool Entity::hasEquippedInSlot(int equipmentSlot)
{
    if(!isActor())
    {
        return false;
    }
    bool result = false;
    if((equipmentSlot & Equipment::Flags::MAIN_HAND) == Equipment::Flags::MAIN_HAND)
    {
        result = actor_->check(Actor::Flags::EQUIP_MAIN_HAND);
    }
    else if((equipmentSlot & Equipment::Flags::OFF_HAND) == Equipment::Flags::OFF_HAND)
    {
        result = actor_->check(Actor::Flags::EQUIP_OFF_HAND);
    }
    else if((equipmentSlot & Equipment::Flags::BODY) == Equipment::Flags::BODY)
    {
        result = actor_->check(Actor::Flags::EQUIP_BODY);
    }
    else if((equipmentSlot & Equipment::Flags::BACK) == Equipment::Flags::BACK)
    {
        result = actor_->check(Actor::Flags::EQUIP_BACK);
    }
    else if((equipmentSlot & Equipment::Flags::LRING) == Equipment::Flags::LRING)
    {
        result = actor_->check(Actor::Flags::EQUIP_LRING);
    }
    else if((equipmentSlot & Equipment::Flags::RRING) == Equipment::Flags::RRING)
    {
        result = actor_->check(Actor::Flags::EQUIP_RRING);
    }
    else if((equipmentSlot & Equipment::Flags::BOOTS) == Equipment::Flags::BOOTS)
    {
        result = actor_->check(Actor::Flags::EQUIP_BOOTS);
    }
    else if((equipmentSlot & Equipment::Flags::RANGED) == Equipment::Flags::RANGED)
    {
        result = actor_->check(Actor::Flags::EQUIP_RANGED);
    }
    else if((equipmentSlot & Equipment::Flags::AMMO) == Equipment::Flags::AMMO)
    {
        result = actor_->check(Actor::Flags::EQUIP_AMMO);
    }
    return result;
}
