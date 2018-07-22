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

Actor::Actor(int s, int v, int mH, int d, int p) : speed(s), vision(v), maxHP(mH), defense(d), power(p)
{
    HP = maxHP;
    energy = 0;
}

Item::Item(int use, int qty)
{
    useFunction = UseFunction(use);
    quantity = qty;
    carried = false;
    stackable = false;
}

Entity::Entity()
{
    game_ = nullptr;
    pos_ = wsl::Vector2i();
    glyph_ = wsl::Glyph();
    name_ = "";
    mask_ = Flags::NONE;
    actor_ = nullptr;
    item_ = nullptr;
    inventory_ = nullptr;
}

Entity::Entity(Engine * game, wsl::Vector2i pos, wsl::Glyph glyph, std::string name) : game_(game), pos_(pos), glyph_(glyph), name_(name)
{
    mask_ = Flags::POS | Flags::GLYPH;
    actor_ = nullptr;
    item_ = nullptr;
} 

void Entity::move(wsl::Vector2i delta)
{
    pos_ += delta;
}

wsl::Vector2i Entity::pos()
{
    return pos_;
}

void Entity::setPos(wsl::Vector2i pos)
{
    pos_ = pos;
}

wsl::Glyph & Entity::glyph()
{
    return glyph_;
}

void Entity::makeActor(Actor actor)
{
    engage(Flags::VISION);
    engage(Flags::ACTOR);
    engage(Flags::BLOCKS);
    actor_ = std::make_shared<Actor>();
    *actor_ = actor;
}

// void Entity::grantEnergy()
// {
//     if(check(Flags::ACTOR))
//     {
//         energy_ += speed_;
//     }
// }
void Entity::takeDamage(int damage)
{
    if((actor_->HP <= 0) || check(Flags::DEAD))
    {
        return;
    }
    actor_->HP -= damage;
    if(actor_->HP <= 0)
    {
        remove(Flags::ACTOR);
        remove(Flags::BLOCKS);
        if(this == game_->player())
        {
            glyph() = wsl::Glyph('%', wsl::Color::Black, wsl::Color::DkRed);
            game_->addMessage(game_->player()->name() + " has perished!");
            game_->changeState(GameState::GAME_OVER);
        }
        else
        {
            wsl::Glyph oldGlyph = glyph();
            glyph() = wsl::Glyph('%', oldGlyph.color(), oldGlyph.bgColor());
            game_->addMessage("The " + name_ + " collapses!");
            engage(Flags::DEAD);
        }
    }
}

bool Entity::update()
{
    bool success = false;
    if(!check(Flags::ACTOR))
    {
        success = false;
    }
    else if(!check(Flags::AI))
    {
        //Player update
        success = true;
    }
    else // if(fov::contains(game_->visible(), pos_)) // Right now the entities only move when they see the player
    {
        //Enemy update
        // All of this will be moved to separate functions depending on the type of AI.
        // The AI component will also have a state (Hunting, exploring, fleeing, etc)
        std::vector<wsl::Vector2i> visible;
        fov::visible(&visible, game_->gameMap(), this);
        if(fov::contains(&visible, game_->player()->pos()))
        {
            wsl::Vector2i next = path::bfsStep(game_->gameMap(), pos_, game_->player()->pos());
            Entity * entity = game_->gameMap()->entityAt(next);
            if(entity != NULL)
            {
                if(entity->isActor())
                {
                    game_->addMessage(name_ + " kicks the " + entity->name() + ", much to it's annoyance."); 
                }
                else
                {
                    setPos(next);
                }
            }
            else if(next == game_->player()->pos())
            {
                game_->addMessage("The " + name_ + " viciously claws at " + game_->player()->name() + "!"); 
                game_->player()->takeDamage(power() - game_->player()->defense());
            }
            else
            {
                //BFS will never set the next position in a blocked tile so there is no need to check for that here.
                setPos(next);
            }
        }
        success = true;
    }
    return success;
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
    inventory_ = std::make_shared< std::vector<Entity> >();
}

void Entity::pickup(Entity * itemEntity)
{
    std::cout << "pickup called\n";
    if(!itemEntity->isItem())
    {
        std::cout << "itemEntity.name(): " << itemEntity->name() << " is not an item!\n";
        return;
    }
    // Add Item to inventory
    if(!hasInventory())
    {
        std::cout << name_ << " does not have an inventory!\n";
        return;
    }
    itemEntity->item_->carried = true;
    if(itemEntity->item_->stackable)
    {
        //if inventory has an item of the same name (?) increase quantity and return 
        for(size_t i = 0; i < inventory_->size(); ++i)
        {
            Entity & listEntity = inventory_->at(i);
            if(listEntity.name() == itemEntity->name())
            {
                listEntity.item_->quantity += 1;
                break;
            }
        }
    }
    else // !itemEntity->item_->stackable
    {
        inventory_->push_back(*itemEntity);
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
    for(size_t i = 0; i < inventory_->size(); ++i)
    {
        std::cout << i << ": " << inventory_->at(i).name() << std::endl;
    }
}

void Entity::drop()
{
    if(!isItem())
    {
        return;
    }
    // item_->carried = false;
    // Remove item from inventory
    // set position to player position
}

void Entity::use()
{
    if(!isItem())
    {
        return;
    }
    // Reduce quantity
    // --if qty <= 0, remove from inventory
    // Check use function
}
