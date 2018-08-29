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
#include <chrono>
// #include <ctime>
// #include "../include/random.hpp"
#include "../include/game_map.hpp"
#include "../include/engine.hpp"
#include "../include/pqlist.hpp"
#include "../include/dllist.hpp"
#include "../include/entity.hpp"
#include "../include/items.hpp"
#include "../include/monsters.hpp"

std::array<wsl::Vector2i, 8> GameMap::DIRS = {
    wsl::Vector2i(-1,0),
    wsl::Vector2i(1,0),
    wsl::Vector2i(0,-1),
    wsl::Vector2i(0,1),
    wsl::Vector2i(-1,1),
    wsl::Vector2i(1,1),
    wsl::Vector2i(-1,-1),
    wsl::Vector2i(1,-1)
};

GameMap::GameMap(Engine * owner, int w, int h, int roomSizeMax, int roomSizeMin, int numRoomsMax) : owner_(owner), width_(w), height_(h), roomSizeMax_(roomSizeMax),
    roomSizeMin_(roomSizeMin), numRoomsMax_(numRoomsMax)
{
    uint32_t seed = uint32_t(std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count());
    // std::time_t t = std::time(0);
    // std::tm * now = std::localtime(&t);
    // uint32_t seed = (now->tm_sec * 1000); // Current seconds after the minute, to milliseconds
    // seed += (now->tm_min * 60 * 1000); // Minutes after the hour, to minutes, to milliseconds
    // seed += (now->tm_hour * 60 * 60 * 1000); // Hours after midnight, to minutes, to seconds, to milliseconds
    std::cout << "Map seed: " << seed << std::endl;
    rngState_ = std::make_shared<wsl::RNGState>(seed);
    currentLevel_ = 1;
    
    if(owner)
    {
        initTiles_();
        initActorList_();
        initItemList_();
        makeMap_();
    }
}

GameMap::GameMap(const GameMap & other) // copy constructor
{
    tiles = other.tiles;
    rooms = other.rooms;
    owner_ = other.owner_;
    rngState_ = std::make_shared<wsl::RNGState>(*other.rngState_.get());
    width_ = other.width_;
    height_ = other.height_;
    roomSizeMax_ = other.roomSizeMax_;
    roomSizeMin_ = other.roomSizeMin_;
    numRoomsMax_ = other.numRoomsMax_;
    currentLevel_ = other.currentLevel_;
    // monsterWeights_ = other.monsterWeights_;
    initActorList_();
    initItemList_();
}

GameMap & GameMap::operator=(GameMap other) // Copy assignment
{
    swap(*this, other);
    return *this;
}

void GameMap::nextLevel()
{
    // Eventually these funcions will look up fun stuff in "loot tables"
    // to generate more interesting dungeons
    ++currentLevel_;

    tiles.clear();
    rooms.clear();
    initActorList_();
    initItemList_();
    initTiles_();
    makeMap_();

    wsl::Vector2i playerPos = owner_->player()->pos();
    wsl::DLList<Entity> followingEntities;
    for(auto dir : DIRS)
    {
        if(actorAt(playerPos + dir))
        {
            Entity entity = *actorAt(playerPos + dir);
            entity.setPos(rooms[0].center() + dir);
            followingEntities.push(entity);
        }
    }
    owner_->entityList()->clear();
    if(followingEntities.isEmpty())
    {
        owner_->addMessage("After a brief rest, you feel ready to continue your journey.");
        owner_->player()->hp() += (owner_->player()->maxHP() / 3);
        if(owner_->player()->hp() > owner_->player()->maxHP())
        {
            owner_->player()->hp() = owner_->player()->maxHP();
        }
    }
    else
    {
        while(!followingEntities.isEmpty())
        {
            Entity entity = followingEntities.popFront();
            owner_->entityList()->push(entity);
        }
        if(followingEntities.size() > 1)
        {
            owner_->addMessage("Some monsters come crashing down the stairs behind you!");
        }
        else
        {
            owner_->addMessage("A monster comes crashing down the stairs behind you!");
        }
    }

    owner_->player()->setPos(rooms[0].center());
    placeActors(2); // Magic number - will eventually be determined based on level
    placeItems(5); // Same - actually this doesnt even do anything now (every room has an item)
}

// std::array<wsl::Vector2i, 4> GameMap::DIRS = {
//     wsl::Vector2i(-1,0),
//     wsl::Vector2i(1,0),
//     wsl::Vector2i(0,-1),
//     wsl::Vector2i(0,1)
// };

Tile & GameMap::tileAt(int x, int y)
{
    return (tiles[index(x,y)]);
}

Tile & GameMap::tileAt(wsl::Vector2i pos)
{
    return (tileAt(pos.x,pos.y));
}

Entity * GameMap::entityAt(wsl::Vector2i pos)
{
    Entity * result = NULL;
    wsl::DLList<Entity> * entityList = owner_->entityList();

    for(wsl::DLNode<Entity> * temp = entityList->head(); temp != NULL; temp = temp->next)
    {
        Entity * entity = &temp->data;
        if(entity->pos() == pos)
        {
            result = entity;
            break;
        }
    }

    return result;
}

Entity * GameMap::entityAt(int x, int y)
{
    return entityAt(wsl::Vector2i(x,y));
}

Entity * GameMap::itemAt(wsl::Vector2i pos)
{
    Entity * result = NULL;
    wsl::DLList<Entity> * entityList = owner_->entityList();

    for(wsl::DLNode<Entity> * temp = entityList->head(); temp != NULL; temp = temp->next)
    {
        Entity * entity = &temp->data;
        if(entity->isItem() && (entity->pos() == pos))
        {
            result = entity;
            break;
        }
    }

    return result;
}

Entity * GameMap::itemAt(int x, int y)
{
    return itemAt(wsl::Vector2i(x,y));
}

Entity * GameMap::actorAt(wsl::Vector2i pos)
{
    Entity * result = NULL;
    wsl::DLList<Entity> * entityList = owner_->entityList();
    for(wsl::DLNode<Entity> * temp = entityList->head(); temp != NULL; temp = temp->next)
    {
        Entity * entity = &temp->data;
        if(entity->isActor() && (entity->pos() == pos))
        {
            result = entity;
            break;
        }
    }

    return result;
}

Entity * GameMap::actorAt(int x, int y)
{
    return actorAt(wsl::Vector2i(x,y));
}

Entity * GameMap::closestEntityTo(int x, int y)
{
    return closestEntityTo(wsl::Vector2i(x,y));
}

Entity * GameMap::closestEntityTo(wsl::Vector2i pos)
{
    Entity * result = NULL;
    // This is a job for wsl::PQList! The priority in this case will be the distance of the entity to the pos
    wsl::PQList<Entity *, int> distanceList;
    wsl::DLList<Entity> * entityList = owner_->entityList();

    for(wsl::DLNode<Entity> * temp = entityList->head(); temp != NULL; temp = temp->next)
    {
        Entity * entity = &temp->data;
        wsl::Vector2i entityPos = entity->pos();
        distanceList.push(entity, entityPos.distanceTo(pos));
    }
    
    if(!distanceList.isEmpty())
    {
        result = distanceList.pop();
    }
    return result;
}

Entity * GameMap::closestActorTo(int x, int y)
{
    return closestEntityTo(wsl::Vector2i(x,y));
}

Entity * GameMap::closestActorTo(wsl::Vector2i pos)
{
    Entity * result = NULL;
    // This is a job for wsl::PQList! The priority in this case will be the distance of the entity to the pos
    wsl::PQList<Entity *, int> distanceList;
    wsl::DLList<Entity> * entityList = owner_->entityList();

    for(wsl::DLNode<Entity> * temp = entityList->head(); temp != NULL; temp = temp->next)
    {
        Entity * entity = &temp->data;
        if(entity->isActor())
        {
            wsl::Vector2i entityPos = entity->pos();
            distanceList.push(entity, entityPos.distanceTo(pos));
        }
    }
    
    if(!distanceList.isEmpty())
    {
        result = distanceList.pop();
    }
    return result;
}

void GameMap::initTiles_()
{
    Tile wallTile = Tile::Wall;
    tiles.assign(width_ * height_, wallTile);
}

void GameMap::initActorList_()
{
    //Loop through owner_->monsterList(), creating weighted list for currentLevel
    //Each monster has a minLvl they can be found, and a weight
    //If minLvl >= (currentLevel) + 2 -> 25% chance of adding that monster at reduced weight
    //   currentLevel - 2 <= minLevel <= currentLevel + 2
    //If minLvl >= (currentLevel) + 1 -> 50% chance of adding that monster at reduced weight
    //   currentLevel - 1 <= minLevel <= currentLevel + 1
    if(!owner_)
    {
        return;
    }
    wsl::DLList<Entity> * monsterList = owner_->monsterList();
    if(!monsterList)
    {
        return;
    }
    // int fMin = currentLevel_ - 1;
    // int fMax = currentLevel_ + 1;
    // int tMin = currentLevel_ - 2;
    // int tMax = currentLevel_ + 2;

    monsterWeights_.clear();
    for(wsl::DLNode<Entity> * node = monsterList->head(); node != NULL; node = node->next)
    {
        int minLvl = node->data.minLvl();
        Entity entity = node->data;
        entity.setGame(owner_);
        if(minLvl <= currentLevel_)
        {
            // 100% chance added, at wt
            monsterWeights_.push(entity, node->data.wt());
        }
        // if(minLvl == fMin || minLvl == fMax)
        // {
        //     //50% chance added at wt 1 
        //     monsterWeights_.push(node->data, 1);
        // }
        // if(minLvl == tMin || minLvl == tMax)
        // {
        //     //25% chance added at wt 1
        //     monsterWeights_.push(node->data, 1);
        // }
    }
}

void GameMap::initItemList_()
{
    if(!owner_)
    {
        return;
    }
    wsl::DLList<Entity> * itemList = owner_->itemList();
    if(!itemList)
    {
        return;
    }

    itemWeights_.clear();
    for(wsl::DLNode<Entity> * node = itemList->head(); node != NULL; node = node->next)
    {
        int minLvl = node->data.minLvl();
        Entity entity = node->data;
        entity.setGame(owner_);
        if(minLvl <= currentLevel_)
        {
            itemWeights_.push(entity, node->data.wt());
        }
    }
}

void GameMap::createRoom_(wsl::Rect room)
{
    for(int x = room.x1 + 1; x < room.x2; ++x)
    {
        for(int y = room.y1 + 1; y < room.y2; ++y)
        {
            tiles[index(x,y)] = Tile::Floor;
        }
    }
}

void GameMap::hTunnel_(int x1, int x2, int y)
{
    int min = (x1 < x2 ? x1 : x2);
    int max = (x1 > x2 ? x1 : x2);
    for(int i = min; i <= max; ++i)
    {
        tiles[index(i,y)] = Tile::Floor;
        if(tileAt(i + 1,y) == Tile::Floor)
        {
            // break;
        }
    }
}

void GameMap::vTunnel_(int y1, int y2, int x)
{
    int min = (y1 < y2 ? y1 : y2);
    int max = (y1 > y2 ? y1 : y2);
    for(int i = min; i <= max; ++i)
    {
        tiles[index(x,i)] = Tile::Floor;
        if(tileAt(x,i+1) == Tile::Floor)
        {
            // break;
        }
    }
}

void GameMap::makeMap_()
{
    // Basic Tutorial algorithm
    int numRooms = 0;
    while(numRooms < numRoomsMax_)
    {
        int w = wsl::randomInt(roomSizeMin_, roomSizeMax_, rngState_.get());
        int h = wsl::randomInt(roomSizeMin_, roomSizeMax_, rngState_.get());
        int x = wsl::randomInt(0, width_ - w - 1, rngState_.get());
        while(x % 2 != 0)
        {
            x = wsl::randomInt(0, width_ - w - 1, rngState_.get());
        }
        int y = wsl::randomInt(0, height_ - h - 1, rngState_.get());
        while(y % 2 != 0)
        {
            y = wsl::randomInt(0, height_ - h - 1, rngState_.get());
        }

        wsl::Rect newRoom = wsl::Rect(x,y,w,h);
        bool intersect = false;
        for(size_t j = 0; j < rooms.size(); ++j)
        {
            if(rooms[j].intersect(newRoom))
            {
                intersect = true;
            }
        }
        if(!intersect)
        {
            createRoom_(newRoom);
            if(rooms.size() > 0)
            {
                wsl::Vector2i previous(rooms[rooms.size() - 1].center());
                wsl::Vector2i current(newRoom.center());
                if(wsl::randomBool(rngState_.get()))
                {
                    hTunnel_(previous.x, current.x, previous.y);
                    vTunnel_(previous.y, current.y, current.x);
                }
                else // wsl::randomBool() == false
                {
                    vTunnel_(previous.y, current.y, previous.x);
                    hTunnel_(previous.x, current.x, current.y);
                }
            }
            rooms.push_back(newRoom);
            numRooms += 1;
        }
    }
    
    // Place stairs in center of last room
    wsl::Vector2i stairPos = rooms[rooms.size() - 1].center(); 
    // wsl::Vector2i stairPos = rooms[0].center();
    tiles[index(stairPos.x,stairPos.y)] = Tile::Stairs;
}

bool GameMap::isBlocked(wsl::Vector2i pos)
{
    return isBlocked(pos.x,pos.y);
}

bool GameMap::isBlocked(int x, int y)
{
    bool success = false;
    if(tiles[index(x,y)].blocksMovement())
    {
        success = true;
    }
    if(entityAt(x,y) != NULL)
    {
        if(entityAt(x,y)->blocks())
        {
            success = true;
        }
    }
    return success;
}

void GameMap::placeActors(int maxPerRoom)
{
    wsl::DLList<Entity> * entityList = owner_->entityList();
    // wsl::WeightedList<Entity> entityWeights;

    // entityWeights.add(monster::skeleton(owner_), 10);
    // entityWeights.add(monster::shamblingCorpse(owner_), (0.5 * currentLevel_));
    // these next three lines are temporary, the game map class will have a weighted list thats
    // generated dynamically each level using the monsters minimum dungeon level
    // entityWeights.add(*(monster::pick(owner_, "skeleton")), 10);
    // entityWeights.add(*(monster::pick(owner_, "shambling corpse")), (0.5 * currentLevel_));
    // entityWeights.add(*(monster::pick(owner_, "confused carcass")), 2);

    for(size_t i = 1; i < rooms.size(); ++i)
    {
        wsl::Rect & room = rooms[i];
        int numEntities = wsl::randomInt(0, maxPerRoom, rngState_.get());

        for(int j = 0; j <= numEntities; ++j)
        {
            int x = wsl::randomInt(room.x1 + 1,room.x2 - 1, rngState_.get());
            int y = wsl::randomInt(room.y1 + 1, room.y2 - 1, rngState_.get());
            if(tileAt(x,y).blocksMovement())
            {
                continue;
            }
            wsl::Vector2i newPos(x,y);
            if(!entityAt(newPos))
            {
                Entity entity = monsterWeights_.pick(rngState_.get());
                entity.setPos(newPos);
                entityList->push(entity);
            }
        }
    }
}

void GameMap::placeItems(int max)
{
    wsl::DLList<Entity> * entityList = owner_->entityList();

    // wsl::WList<Entity> itemWeights;
    // itemWeights.push(item::healingPotion(owner_), 4);
    // itemWeights.push(item::lightningScroll(owner_), 2);
    // itemWeights.push(item::fireballScroll(owner_), 2);
    // itemWeights.push(item::fireboltScroll(owner_), 2);
    // itemWeights.push(item::battleAxe(owner_), 1);
    // itemWeights.push(item::woodenShield(owner_), 1);
    // itemWeights.push(item::dagger(owner_), 1);
    // int numItems = wsl::randomInt(0,max);
    int numItems = max;
    int placedItems = 0;
    for(size_t i = 1; i < rooms.size(); ++i)
    {
        if(placedItems >= numItems)
        {
            // break;
        }
        wsl::Rect & room = rooms[i];
        int x = wsl::randomInt(room.x1 + 1,room.x2 - 1, rngState_.get());
        int y = wsl::randomInt(room.y1 + 1, room.y2 - 1, rngState_.get());
        if(!entityAt(x,y))
        {
            wsl::Vector2i newPos(x,y);
            Entity entity = itemWeights_.pick(rngState_.get());
            entity.setPos(newPos);
            entityList->push(entity);
        }
    }
}

std::vector<wsl::Vector2i> GameMap::neighbors(wsl::Vector2i start)
{
    std::vector<wsl::Vector2i> results;
    for(wsl::Vector2i dir : DIRS)
    {
        wsl::Vector2i next = start + dir;
        if(!isBlocked(next) && inBounds_(next))
        {
            results.push_back(next);
        }
    }
    return results;

}

bool GameMap::inBounds_(wsl::Vector2i pos)
{
    return (0 <= pos.x) && (pos.x < width_) && (0 <= pos.y) && (pos.y < height_);
}

