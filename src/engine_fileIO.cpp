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
#include <fstream>

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/xml.hpp>
// #include <cereal/archives/json.hpp>

#include "../include/engine.hpp"
#include "../include/wsl_cereal.hpp"

class CerealEntity
{
    public:
       
        void convert(Entity entity);
        Entity extract();
        int mask;
        wsl::Vector2i pos;
        wsl::Glyph glyph;
        std::string name;
        Actor actor;
        Item item;
        std::vector<CerealEntity> inventory;

        template<class Archive>
        void serialize(Archive & ar)
        {
            ar(mask);
            ar(pos);
            ar(glyph);
            ar(name);
            ar(actor);
            ar(item);
            ar(inventory);
        }
};

void CerealEntity::convert(Entity entity)
{
    mask = entity.mask();
    pos = entity.pos();
    glyph = entity.glyph();
    name = entity.name();

    if(entity.isActor())
    {
        actor = entity.actor();
    }
    else
    {
        actor = Actor();
    }

    if(entity.isItem())
    {
        item = entity.item();
    }
    else
    {
        item = Item();
    }

    if(entity.hasInventory())
    {
        // Loop through inventory, creating CerealEntities for each item and pushing them into the inventory vector
        for(wsl::DLNode<Entity> * node = entity.inventory()->head(); node != NULL; node = node->next)
        {
            CerealEntity itemEntity;
            itemEntity.convert(node->data);
            inventory.push_back(itemEntity);
        }
    }
}

Entity CerealEntity::extract()
{
    Entity resultEntity(NULL,pos,glyph,name);
    resultEntity.set(mask);
    if(resultEntity.isActor())
    {
        resultEntity.makeActor(actor);
    }
    if(resultEntity.isItem())
    {
        resultEntity.makeItem(item);
    }
    if(resultEntity.hasInventory())
    {
        resultEntity.makeInventory();
        for(size_t i = 0; i < inventory.size(); ++i)
        {
            Entity itemEntity = inventory[i].extract();
            resultEntity.inventory()->push(itemEntity);
        }
    }
    return resultEntity;
}

void Engine::saveGame()
{
    std::vector<CerealEntity> entityListCereal;
    
    for(wsl::DLNode<Entity> * node = entityList_.head(); node != NULL; node = node->next)
    {
        CerealEntity entity;
        entity.convert(node->data);
        entityListCereal.push_back(entity);
    }

    CerealEntity player;
    player.convert(*player_);

    GameMap map = *gameMap_;

    wsl::CerealDLList<std::string> msgListCereal;
    msgListCereal.convert(&msgList_);
    {
        std::ofstream os("assets/gamedata.bin", std::ios::binary);
        cereal::BinaryOutputArchive ar(os);
        // std::ofstream os("assets/gamedata.xml", std::ios::binary);
        // cereal::XMLOutputArchive ar(os);
        ar(map);
        ar(entityListCereal);
        ar(player);
        ar(gameState_);
        ar(prevGameState_);
        ar(msgListCereal);
        ar(currentMsg_);
    }
}

bool Engine::loadGame()
{
    bool success = true;
    std::vector<CerealEntity> entityListCereal;
    CerealEntity player;
    GameMap map;
    wsl::CerealDLList<std::string> msgListCereal;
    {
        std::ifstream inputFile("assets/gamedata.bin", std::ios::binary);
        // std::ifstream inputFile("assets/gamedata.xml", std::ios::binary);
        if(inputFile.good())
        {
            // std::cout << "Input file good!\n";
            cereal::BinaryInputArchive ar(inputFile);
            // cereal::XMLInputArchive ar(inputFile);
            ar(map);
            // std::cout << "Game Map loaded. ";
            ar(entityListCereal);
            // std::cout << "Cerealized entity list loaded. ";
            ar(player);
            // std::cout << "Cerealized player loaded. ";
            ar(gameState_);
            // std::cout << "gameState loaded. ";
            ar(prevGameState_);
            // std::cout << "prevGameState loaded. ";
            ar(msgListCereal);
            // std::cout << "Cerealized msg list loaded. ";
            ar(currentMsg_);
            // std::cout << "Current Message loaded. ";
            // std::cout << "Loaded saved objects..\n";

            // create game map and set owner
            map.setOwner(this);
            // std::cout << "Set map owner, ";
            *gameMap_ = map;
            // std::cout << "Recreated map...";
            //create normal entity list from entityListCereal
            entityList_.clear();
            for(size_t i = 0; i < entityListCereal.size(); ++i)
            {
                Entity entity = entityListCereal[i].extract();
                entity.setGame(this);
                entityList_.push(entity);
            }
            // std::cout << "Recreated entity list...";
            //create normal entity player from player
            Entity playerEntity = player.extract();
            playerEntity.setGame(this);
            *player_= playerEntity;
            // std::cout << "Recreated player entity...";
            //create normal message list from msgListCereal
            // msgList_ = msgListCereal.extract();
            // std::cout << "Recreated message list...";
        }
        else
        {
            success = false;
        }
    }
    // std::cout << "Finished!\n";
    return success;
}
