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

Entity::Entity()
{
    game_ = nullptr;
    pos_ = wsl::Vector2i();
    glyph_ = wsl::Glyph();
    name_ = "";
    mask_ = Flags::NONE;
    actor_ = nullptr;
}

Entity::Entity(Engine * game, wsl::Vector2i pos, wsl::Glyph glyph, std::string name) : game_(game), pos_(pos), glyph_(glyph), name_(name)
{
    mask_ = Flags::POS | Flags::GLYPH;
    actor_ = nullptr;
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
    // actor_ = new Actor();
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
    actor_->HP -= damage;
    if(actor_->HP <= 0)
    {
        remove(Flags::ACTOR);
        remove(Flags::BLOCKS);
        if(this == game_->player())
        {
            glyph() = wsl::Glyph('%', wsl::Color::Black, wsl::Color::DkRed);
            std::cout << game_->player()->name() << " has perished!\n";
            game_->playerDied();
        }
        else
        {
            wsl::Glyph oldGlyph = glyph();
            glyph() = wsl::Glyph('%', oldGlyph.color(), oldGlyph.bgColor());
            std::cout << "The " << name_ << " collapses!\n";
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
        // Almost all of this could be moved into a separate AI component...
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
                    std::cout << name_ << " kicks the " << entity->name() << ", much to it's annoyance.\n"; 
                }
                else
                {
                    setPos(next);
                }
            }
            else if(next == game_->player()->pos())
            {
                std::cout << "The " << name_ << " viciously claws at " << game_->player()->name() << "!\n"; 
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
