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
#include <cmath>

#include "../include/entity.hpp"
#include "../include/game_map.hpp"
#include "../include/engine.hpp"
#include "../include/pathfinding.hpp"
#include "../include/animation.hpp"

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
    // inventory_ = std::make_shared< wsl::DLList<Entity> >();
    inventory_ = std::make_shared<wsl::PQList<Entity, int> >();
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
        // Check if inventory has an item of the same type using the item's mask
        Entity * invItem = NULL;
        for(wsl::PQNode<Entity, int> * temp = inventory_->head(); temp != NULL; temp = temp->next)
        {
            Entity * listEntity = &temp->data;
            if(listEntity->item().mask() == itemEntity->item().mask())
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
            inventory_->push(*itemEntity, itemEntity->itemPriority());
        }
    }
    else // !itemEntity->item_->stackable
    {
        inventory_->push(*itemEntity, itemEntity->itemPriority());
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
    // wsl::DLNode<Entity> * itemNode = inventory_->at(index);
    wsl::PQNode<Entity, int> * itemNode = inventory_->at(index);
    if(!itemNode)
    {
        return;
    }
    Entity itemEntity = itemNode->data;
    if(itemEntity.isEquipment())
    {
        if(itemEntity.equipped())
        {
            toggleEquip(&itemNode->data); //Because itemEntity is a copy a pointer to the original is needed
            return;
        }
    }
    if(itemEntity.quantity() > 1 )
    {
        game_->addMessage("You drop the " + itemEntity.name() + "s.");
    }
    else
    {
        game_->addMessage("You drop the " + itemEntity.name() + ".");
    }
    itemEntity.item_->carried = false;
    itemEntity.setPos(pos_);
    game_->entityList()->push(itemEntity);
    inventory_->remove(itemNode);
}

void Entity::use(int index)
{
    wsl::PQNode<Entity, int> * itemNode = inventory_->at(index);
    if(!itemNode)
    {
        return;
    }
    Entity & itemEntity = itemNode->data;

    // Check use functions
    bool success = false;
    if(itemEntity.item_->check(Item::Flags::HEAL))
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
        success = use_heal_();
    }
    if(itemEntity.item_->check(Item::Flags::CAST_LIGHTNING))
    {
        success = use_cast_lightning_();
    }
    if(itemEntity.item_->check(Item::Flags::CAST_FIREBOLT))
    {
        success = use_cast_firebolt_();
    }
    if(itemEntity.item_->check(Item::Flags::CAST_FIREBALL))
    {
        success = use_cast_fireball_();
    }
    if(itemEntity.item_->check(Item::Flags::EQUIP))
    {
        toggleEquip(&itemNode->data);
        return;
    }

    // Reduce quantity
    if(success)
    {
        itemEntity.item_->quantity -= 1;
        if(itemEntity.item_->quantity <= 0)
        {
            // --if qty <= 0, remove from inventory
            inventory_->remove(itemNode);
        }
    }
    else
    {
        game_->addMessage(name() + " changes their mind, and puts the " + itemEntity.name() + " away.");
    }
}

int Entity::itemPriority()
{
    int result = 5; //Arbitrary number greater than number of item types
    if(item_->check(Item::Flags::EQUIP)) result = 1;
    else if(item_->check(Item::Flags::POTION)) result = 2;
    else if(item_->check(Item::Flags::SCROLL)) result = 3;
    return result;
}

bool Entity::use_heal_()
{
    if(!isActor())
    {
        return false;
    }
    heal(actor_->maxHP / 3);
    return true;
}

bool Entity::use_cast_lightning_()
{
    if(this == game_->player())
    {
        game_->addMessage("A bolt of lightning is summoned!");
        Entity * target = game_->gameMap()->closestActorTo(pos_);
        if(fov::contains(game_->visible(), target->pos()))
        {
            game_->addMessage("It arcs towards the " + target->name() + ".");
            // target->takeDamage(20); // This magic number needs to be changed
            dealDamage(target, 40);
            game_->animations()->push(Animated::lightning(pos(), target->pos()));
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
    return true;
}

bool Entity::use_cast_firebolt_()
{
    wsl::Vector2i animationOrigin = pos();
    wsl::Vector2i animationTarget;
    if(this == game_->player())
    {
        game_->target();
        Entity * target = game_->gameMap()->entityAt(game_->cursor());
        animationTarget = game_->cursor();
        game_->addMessage("A bolt of fire shoots out of " + name() + "\'s hands!");
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
                // target->takeDamage(10);
                dealDamage(target, 10);
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
            // tile.glyph().setColor(wsl::Color::DkGrey);
        }
    }
    // Animation fireProjectile = Animated::projectile(wsl::Glyph('*',wsl::Color::LtOrange), animationOrigin, animationTarget);
    // Animation animation;
    // game_->animations()->push(animation);
    // game_->animations()->push(Animated::projectile(wsl::Glyph(9,wsl::Color::Red), animationOrigin, animationTarget));
    game_->animations()->push(Animated::firebolt(animationOrigin, animationTarget));
    return true;
}

bool Entity::use_cast_fireball_()
{
    wsl::Vector2i animationOrigin = pos();
    wsl::Vector2i animationTarget;
    int radius = 3; // These might get passed in eventually or be based on a player's wisdom stat or something
    int damage = 25;
    if(this == game_->player())
    {
        game_->target();

        // Need all entities with a radius of the selected position
        wsl::Vector2i targetPos;
        if(!game_->targetSelected())
        {
            // targetPos = pos();
            return false; // No target selected;
        }
        else
        {
            targetPos = game_->cursor();
            animationTarget = game_->cursor();
        }

        game_->addMessage("Fire explodes out of " + name() + "\'s hands!");
        for(int x = targetPos.x - radius; x <= targetPos.x + radius; ++x)
        {
            for(int y = targetPos.y - radius; y <= targetPos.y + radius; ++y)
            {
                if(sqrt(pow(x - targetPos.x, 2) + pow(y - targetPos.y, 2)) > radius) continue;
                Entity * target = game_->gameMap()->entityAt(x,y);
                if(target)
                {
                    if(target->isActor())
                    {
                        game_->addMessage("The " + target->name() + " is scorched!");
                        // target->takeDamage(5);
                        dealDamage(target, damage);
                    }
                    else if(target->isItem())
                    {
                        game_->addMessage("An item on the ground bursts into flame and is destroyed!");
                        target->engage(Flags::DEAD);
                    }
                }
                else
                {
                    if(pos() == wsl::Vector2i(x,y))
                    {
                        game_->addMessage(name() + " is caught in the explosion!");
                        takeDamage(damage);
                    }
                    // else
                    // {
                    //
                    //     Tile & tile = game_->gameMap()->tileAt(x,y);
                    //     if(tile.check(Tile::Flags::FLOOR))
                    //     {
                    //         // game_->addMessage("The ground is scorched!");
                    //         tile.glyph().setColor(wsl::Color::DkGrey);
                    //     }
                    //     else if(tile.check(Tile::Flags::WALL))
                    //     {
                    //         // game_->addMessage("The dungeon wall is charred black!");
                    //         tile.glyph().setColor(wsl::Color::Black);
                    //     }
                    // }
                }
            }
        }
    }

    game_->animations()->push(Animated::fireball(radius,animationOrigin, animationTarget));
    return true;
}
