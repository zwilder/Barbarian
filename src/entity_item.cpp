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
    // useFunction = UseFunction(u);
    set(u);
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

    // Check use functions
    if(itemEntity.item_->check(Item::Flags::SCROLL))
    {
        game_->addMessage(name() + " reads the " + itemEntity.name() + "!");
    }
    if(itemEntity.item_->check(Item::Flags::POTION))
    {
        game_->addMessage(name() + " drinks the " + itemEntity.name() + "!");
    }
    if(itemEntity.item_->check(Item::Flags::HEAL))
    {
        use_heal_();
    }
    if(itemEntity.item_->check(Item::Flags::CAST_LIGHTNING))
    {
        use_cast_lightning_();
    }
    if(itemEntity.item_->check(Item::Flags::CAST_FIREBOLT))
    {
        use_cast_firebolt_();
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

void Entity::use_cast_lightning_()
{
    if(this == game_->player())
    {
        game_->addMessage("A bolt of lightning is summoned!");
        Entity * target = game_->gameMap()->closestActorTo(pos_);
        if(fov::contains(game_->visible(), target->pos()))
        {
            game_->addMessage("It arcs towards the " + target->name() + ".");
            target->takeDamage(20); // This magic number needs to be changed
        }
        else
        {
            // Might be fun if the player takes damage instead... 
            game_->addMessage("It fizzles out.");
        }
    }
    // else
    // {
        // Other entities might use this function to cast lightning
    // }
}

void Entity::use_cast_firebolt_()
{
    if(this == game_->player())
    {
        game_->target();
        Entity * target = game_->gameMap()->entityAt(game_->cursor());
        game_->addMessage("A bolt of fire explodes out of " + name() + "\'s hands!");
        if(game_->cursor() == pos() || !game_->targetSelected())
        {
            game_->addMessage(name() + " catches fire!");
            takeDamage(10);
        }
        else if(target)
        {
            if(target->isActor())
            {
                game_->addMessage("The " + target->name() + " erupts in flame!");
                target->takeDamage(10);
            }
            else if(target->isItem())
            {
                game_->addMessage("An item on the ground bursts into flame and is destroyed!");
                target->engage(Flags::DEAD);
            }
        }
        else
        {
            Tile & tile = game_->gameMap()->tileAt(game_->cursor());
            if(tile.check(Tile::Flags::FLOOR))
            {
                game_->addMessage("The ground is scorched!");
            }
            else if(tile.check(Tile::Flags::WALL))
            {
                game_->addMessage("The firebolt explodes against the dungeon wall!");
            }
            tile.glyph().setColor(wsl::Color::DkGrey);
        }
    }
}
