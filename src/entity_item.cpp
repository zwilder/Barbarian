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
#include "../include/game_map.hpp"
#include "../include/engine.hpp"
#include "../include/pathfinding.hpp"

Item::Item(int u, int q, bool s)
{
    useFunction = UseFunction(u);
    quantity = q;
    carried = false;
    stackable = s;
}

void Entity::makeItem(Item item)
{
    engage(Flags::ITEM);
    item_ = std::make_shared<Item>();
    *item_ = item;
}

void Entity::makeInventory()
{
    engage(Flags::INVENTORY);
    inventory_ = std::make_shared< wsl::DLList<Entity> >();
}

void Entity::pickup(Entity * itemEntity)
{
    if(!itemEntity->isItem())
    {
        return;
    }
    // Add Item to inventory
    if(!hasInventory())
    {
        return;
    }
    itemEntity->item_->carried = true;
    if(itemEntity->item_->stackable)
    {
        // Check if inventory has an item of the same name (?) 
        Entity * invItem = NULL;
        for(wsl::DLNode<Entity> * temp = inventory_->head(); temp != NULL; temp = temp->next)
        {
            Entity * listEntity = &temp->data;
            if(listEntity->name() == itemEntity->name())
            {
                invItem = listEntity;
                break;
            }
        }
        if(invItem != NULL)
        {
            invItem->item_->quantity += 1;
        }
        else // invItem == NULL
        {
            inventory_->push(*itemEntity);
        }
    }
    else // !itemEntity->item_->stackable
    {
        inventory_->push(*itemEntity);
    } 
    // Remove item from game entityList
    wsl::DLNode<Entity> * current = game_->entityList()->head();
    while(current != NULL)
    {
        Entity * curEntity = &current->data;
        if(curEntity->isItem() && (curEntity->pos() == itemEntity->pos()) && (curEntity->name() == itemEntity->name()))
        {
            break;
        }
        current = current->next;
    }
    game_->entityList()->remove(current);
}

void Entity::drop(int index)
{
    wsl::DLNode<Entity> * itemNode = inventory_->at(index);
    if(!itemNode)
    {
        return;
    }
    Entity itemEntity = itemNode->data;
    itemEntity.item_->carried = false;
    itemEntity.setPos(pos_);
    game_->entityList()->push(itemEntity);
    inventory_->remove(itemNode);
}

void Entity::use(int index)
{
    wsl::DLNode<Entity> * itemNode = inventory_->at(index);
    if(!itemNode)
    {
        return;
    }
    Entity & itemEntity = itemNode->data;
    // Check use function
    switch(itemEntity.item_->useFunction)
    {
        case Item::UseFunction::Heal:
        {
            use_heal_();
            break;
        }
        default: break;
    }
    // Reduce quantity
    itemEntity.item_->quantity -= 1;
    if(itemEntity.item_->quantity <= 0)
    {
        // --if qty <= 0, remove from inventory
        inventory_->remove(itemNode);
    }
}

void Entity::use_heal_()
{
    if(!isActor())
    {
        return;
    }
    actor_->HP += int(actor_->maxHP / 3);
    if(actor_->HP > actor_->maxHP)
    {
        actor_->HP = actor_->maxHP;
    }
}
