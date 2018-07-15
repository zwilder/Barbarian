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
#include <iostream>

#include "../include/actor.hpp"
#include "../include/entity.hpp"
#include "../include/engine.hpp"

/*****
 * Action Functions
 ****/
Action::Action(Actor * owner, int type, wsl::Vector2i dir) : actor_(owner), type_(type), dir_(dir)
{
    success_ = false;
}

void Action::perform()
{
    switch(type_)
    {
        case Type::Attack: attack_(); break;
        case Type::Move: move_(); break;
        case Type::Rest: rest_(); break;
    }
}

void Action::attack_()
{
    wsl::Vector2i pos = dir_ + actor_->owner()->pos();
    Entity * entity = actor_->owner()->game()->gameMap()->entityAt(pos, actor_->owner()->game()->entityList());
    if(entity != NULL && entity != actor_->owner())
    {
        if(entity->check(Entity::Flags::ACTOR))
        {

            std::cout << actor_->owner()->name() << " kicks the " << entity->name() << ", much to it's annoyance.\n"; 
            success_ = true;
        }
    }
    else
    {
        //Attack failed, try move action
        move_();
    }
}

void Action::move_()
{
    wsl::Vector2i pos = dir_ + actor_->owner()->pos();
    if(!actor_->owner()->game()->gameMap()->tileAt(pos).blocksMovement())
    {
        actor_->owner()->move(dir_);// Need to move this to the player's "update" routine, so the player takes their turn in proper order.
        // fov::visible(visible_.get(), gameMap_.get(), player_.get());
        success_ = true;
    }
    else
    {
        // Move failed
        rest_();
    }
}

void Action::rest_()
{
    std::cout << actor_->owner()->name() << " contemplates it's existence.\n";
    success_ = true;
}

/*****
 * Actor Functions
 ****/
Actor::Actor()
{
    owner_ = NULL;
    speed_ = 0;
    vision_ = 0;
    energy_ = 0;
    std::cout << "Null entity created!\n";
}
Actor::Actor(Entity * owner, int speed, int vision) : owner_(owner), speed_(speed), vision_(vision)
{
    energy_ = 0;
    std::cout << owner->name() << ": " << owner  << ", " << owner_ << std::endl;
}

void Actor::grantEnergy()
{
    energy_ += speed_;
}

void Actor::setNextAction(int type, wsl::Vector2i dir)
{
    // Passes a NEW action, nextAction_ = action;
    // nextAction_ = action;
    nextAction_ = new Action(this, type, dir);
}

Action * Actor::getAction()
{
    // Returns Action, nextAction_ = NULL
    std::cout << "Getting next action...";
    Action * result = nextAction_;
    nextAction_ = NULL;
    return result;
}

bool Actor::update()
{
    std::cout << owner_ << std::endl;
    if(owner_ == NULL)
    {
        std::cout << "ERROR! Owner is NULL!\n";
        return false;
    }
    //IF AI, update AI component of owner (??). getAction(). !NULL ? action->perform(). action->succcess() ? DELETE action, return true
    std::cout << "Update start.\n";
    bool success = false;
    std::cout << "Checking owner flags...\t" << Entity::Flags::AI << std::endl;
    if(owner_->check(Entity::Flags::AI))
    {
        // owner_->ai()->update();
        std::cout << "AI update\n";
        setNextAction(Action::Type::Rest); // Temporary, until the AI component is added
    }

    std::cout << "Calling getAction()... ";
    Action * action = getAction();
    std::cout << "Got next action...";
    if(action != NULL)
    {
        action->perform();
        std::cout << " Performed.\n";
        if(action->success())
        {
            std::cout << "Action successful!\n";
            delete action;
            success = true;
        }
    }
    return success;
}

