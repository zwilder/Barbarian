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
#include <iterator>
#include <sstream>
#include "../include/engine.hpp"

void Engine::update()
{
    /*
    if(!schedule_->isEmpty())
    // while(schedule_->head() != NULL)
    {
        // std::cout << "Schedule is not empty\n";
        // if(curActor_ == NULL)
        // {
        //     curActor_ = schedule_->popFront();
        // }
        // if(gameState_ == GameState::PLAYERS_TURN)
        // {
        //     return;
        // }
        // else
        // {
        //     //curActor_->update();
        // }
        // std::cout << curActor_->name() << " took turn!\n";
        if(!curActor_->update())
        {
            return; // Current actor failed to take turn
        }
        curActor_->energy() -= ACTION_COST;
        curActor_ = schedule_->popFront();
        return;
    }
    else
    {
        // for(int i = 0; i < entityList_->size(); ++i)
        for(wsl::DLNode<Entity> * temp = entityList_.head(); temp != NULL; temp = temp->next)
        {
            // if(entityList_->at(i).actor() == NULL)
            Entity & entity = temp->data;
            Actor * actor = entity.actor();
            if(actor == NULL)
            {
                continue;
            }
            // Actor * actor = entityList_->at(i).actor();
            actor->grantEnergy();
            if(actor->energy() >= ACTION_COST)
            {
                schedule_->push(actor);
            }
        }
        player_->actor()->grantEnergy();
        if(player_->actor()->energy() >= ACTION_COST)
        {
            schedule_->push(player_->actor());
        }
        gameState_ = GameState::PLAYERS_TURN;
    }
    */
    if(gameState_ == GameState::ENEMY_TURN)
    {
        for(wsl::DLNode<Entity> * temp = entityList_.head(); temp != NULL; temp = temp->next)
        {
            Entity & entity = temp->data;
            entity.update();
        }
        if((gameState_ != GameState::GAME_OVER))// && (gameState_ != GameState::MSG_WAIT))
        {
            changeState(GameState::PLAYERS_TURN);
        }

        advanceMsg_();
    }
    //Remove dead entities (and leave corpses!)
    wsl::DLNode<Entity> * current = entityList_.head();
    while(current != NULL)
    {
        if(current->data.check(Entity::Flags::DEAD))
        {
            wsl::DLNode<Entity> * dead = current;
            current = current->next;
            gameMap_->tileAt(dead->data.pos()).glyph() = wsl::Glyph(dead->data.glyph().symbol(), dead->data.glyph().color(), dead->data.glyph().bgColor());
            entityList_.remove(dead);
        }
        else
        {
            current = current->next;
        }
    }
}

