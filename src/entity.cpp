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
// #include "../include/game_map.hpp"

/*****
 * Generic Entity Functions
 ****/
Entity::Entity()
{
    mask_ = Flags::NONE;
} 

Entity::Entity(wsl::Vector2i pos, wsl::Glyph glyph, std::string name) : pos_(pos), glyph_(glyph), name_(name)
{
    mask_ = Flags::POS | Flags::GLYPH;
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

/*****
 * Actor Functions
 ****/
void Entity::makeActor(int speed, int vision)
{ 
    engage(Flags::VISION);
    engage(Flags::ACTOR);
    engage(Flags::BLOCKS);
    actor_ = Actor(speed, vision);
}

void Entity::makeActor(Actor actor)
{
    engage(Flags::VISION);
    engage(Flags::ACTOR);
    engage(Flags::BLOCKS);
    actor_ = actor;
}

int Entity::vision()
{
    int result = 0;
    if(check(Flags::VISION))
    {
        result = actor_.vision();
    }
    return result;        
}

int & Entity::energy()
{
    // int result = 0;
    // if(check(Flags::ACTOR))
    // {
        // result = actor_.energy();
    // }
    // return result;
    return actor_.energy();
}

void Entity::grantEnergy()
{
    if(check(Flags::ACTOR))
    {
        actor_.grantEnergy();
    }
}

Actor * Entity::actor()
{
    Actor * result = NULL;
    if(check(Flags::ACTOR))
    {
        result = &actor_;
    }

    return result;
}
/*
void Entity::update(GameMap * map)
{
    if(!check(Flags::ACTOR))
    {
        return;
    }

    if(check(Flags::AI))
    {
        action = actor_->update(GameMap * map);
    }
    
    int action = actor_->getAction();
    // Do cool stuff
}
*/
Actor::Actor(int speed, int vision) : speed_(speed), vision_(vision)
{
    energy_ = 0;
}

void Actor::grantEnergy()
{
    energy_ += speed_;
}
/*
void Actor::update(GameMap * map)
{
    //
}

void Actor::setNextAction(int cmd, wsl::Vector2i dir)
{
    nextAction_ = cmd;
    actionDir_ = dir; 
}

int Actor::getAction()
{
    int result = nextAction_;
    nextAction = Cmd::NONE;
    return result;
}*/
