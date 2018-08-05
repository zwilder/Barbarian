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

Actor::Actor(int s, int v, int mH, int d, int p, int x) : speed(s), vision(v), maxHP(mH), defense(d), power(p), xp(x)
{
    HP = maxHP;
    energy = 0;
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
    std::cout << name() << " has " << std::to_string(actor_->HP) << " health.\n";
    if((actor_->HP <= 0) || check(Flags::DEAD))
    {
        return;
    }
    actor_->HP -= damage;
    if(actor_->HP <= 0)
    {
        // remove(Flags::ACTOR);
        // remove(Flags::BLOCKS);
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
            game_->addMessage("The " + name() + " collapses!");
            engage(Flags::DEAD);
        }
    }
}

void Entity::dealDamage(Entity * target, int damage)
{
    target->takeDamage(damage);
    if(target->check(Flags::DEAD))
    {
        bool levelUp = false;
        if(hasLevel())
        {
            levelUp = addXP(target->xp());
        }
        if(levelUp && (this == game_->player()))
        {
            game_->changeState(GameState::LEVEL_UP);
        }
    }
}

void Entity::heal(int qty)
{
    if(!isActor())
    {
        return;
    }
    actor_->HP += qty;
    if(actor_->HP > actor_->maxHP)
    {
        actor_->HP = actor_->maxHP;
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
            Entity * entity = game_->gameMap()->actorAt(next);
            if(entity != NULL)
            {
                if(entity->isActor())
                {
                    game_->addMessage(name() + " kicks the " + entity->name() + ", much to it's annoyance."); 
                }
                else
                {
                    setPos(next);
                }
            }
            else if(next == game_->player()->pos())
            {
                game_->addMessage("The " + name() + " viciously claws at " + game_->player()->name() + "!"); 
                // game_->player()->takeDamage(power() - game_->player()->defense());
                dealDamage(game_->player(), power() -game_->player()->defense());
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
