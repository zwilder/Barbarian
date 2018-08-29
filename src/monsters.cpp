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
#include <fstream>
#include <sstream>

#include "../include/monsters.hpp"
#include "../include/entity.hpp"
#include "../include/engine.hpp"
#include "../include/items.hpp"

namespace monster
{
void loadMonsters(Engine * engine)
{
    wsl::DLList<Entity> * list = engine->monsterList();
    list->clear();
    std::ifstream file("assets/monsters.config");
    std::string entry;
    wsl::DLList<std::string> entries;

    while(std::getline(file, entry, ';'))
    {
        Entity readEntity = parseEntry(entry, engine);
        if(readEntity.name() != "foo")
        {
            list->push(readEntity);
        }
    }
}

Entity parseEntry(std::string entry, Engine * engine)
{
    if(!engine)
    {
        std::cout << "Warning, parseEntry called with NULL engine\n";
    }
    std::string name = "foo";
    char symbol = '+';
    wsl::Color fgColor = wsl::Color::White;
    wsl::Color bgColor = wsl::Color::Black;
    int speed = 0;
    int vision = 0;
    int maxHP = 0;    
    int defense = 0;
    int power = 0;
    int xp = 0;
    bool inventory = false;
    bool level = false;
    bool ai = false;
    int mlvl = 0;
    int wt = 0;
    std::string items;

    wsl::Vector2<std::string> nvp;
    std::istringstream inString(entry);
    std::string line;
    while(std::getline(inString, line))
    {
        std::istringstream isLine(line);
        if(std::getline(isLine, nvp.x, ':'))
        {
            if(nvp.x[0] == '#') continue;
            if(std::getline(isLine, nvp.y))
            {
                if(nvp.x == "name") name = nvp.y;
                if(nvp.x == "sym") symbol = nvp.y[0];
                if(nvp.x == "fg") fgColor = parseColor(std::stoi(nvp.y));
                if(nvp.x == "bg") bgColor = parseColor(std::stoi(nvp.y));
                if(nvp.x == "spd") speed = std::stoi(nvp.y);
                if(nvp.x == "vis") vision = std::stoi(nvp.y);
                if(nvp.x == "mhp") maxHP = std::stoi(nvp.y);
                if(nvp.x == "def") defense = std::stoi(nvp.y);
                if(nvp.x == "pow") power = std::stoi(nvp.y);
                if(nvp.x == "xp") xp = std::stoi(nvp.y);
                if(nvp.x == "inv" && nvp.y == "1") inventory = true;
                if(nvp.x == "lvl" && nvp.y == "1") level = true;
                if(nvp.x == "ai" && nvp.y == "1") ai = true;
                if(nvp.x == "items") items = nvp.y;
                if(nvp.x == "wt") wt = std::stoi(nvp.y);
                if(nvp.x == "mlvl") mlvl = std::stoi(nvp.y);
            }
        }
    }

    Entity resultEntity(engine, wsl::Vector2i(), wsl::Glyph(symbol, fgColor, bgColor), name, wt, mlvl);
    resultEntity.makeActor(Actor(speed, vision, maxHP, defense, power, xp));
    if(inventory) resultEntity.makeInventory();
    if(ai) resultEntity.engage(Entity::Flags::AI); // This needs to be made into a proper Entity::makeAI(int type) component
    if(level) resultEntity.makeLevel(Level());
    if(items != "")
    {
        // If the entity has items listed in the config file, this breaks up the string (comma delimited)
        // and adds those items to the engine's entity list, then picks them up. I do it this way instead of
        // adding to the inventory directly, because there's less code this way... Might as well use stuff I've
        // already written, right?
        std::string itemString;
        std::istringstream isLine(items);
        while(std::getline(isLine, itemString, ','))
        {
            Entity * item = monster::pick(engine->itemList(), itemString);
            if(item)
            {
                Entity itemEntity = *item;
                engine->entityList()->push(itemEntity);
                resultEntity.pickup(&(engine->entityList()->head()->data));
            }
        }
    }
    return resultEntity;
}

wsl::Color parseColor(int colorInt)
{
    switch(colorInt)
    {
        case 1:   return wsl::Color::LtRed;
        case 2:   return wsl::Color::Red;
        case 3:   return wsl::Color::DkRed;
        case 4:   return wsl::Color::LtOrange;
        case 5:   return wsl::Color::Orange;
        case 6:   return wsl::Color::DkOrange;
        case 7:   return wsl::Color::LtYellow;
        case 8:   return wsl::Color::Yellow;
        case 9:   return wsl::Color::DkYellow;
        case 10:  return wsl::Color::LtGreen;
        case 11:  return wsl::Color::Green;
        case 12:  return wsl::Color::DkGreen;
        case 13:  return wsl::Color::LtBlue;
        case 14:  return wsl::Color::Blue;
        case 15:  return wsl::Color::DkBlue;
        case 16:  return wsl::Color::LtViolet;
        case 17:  return wsl::Color::Violet;
        case 18:  return wsl::Color::DkViolet;
        case 19:  return wsl::Color::LtSepia;
        case 20:  return wsl::Color::Sepia;
        case 21:  return wsl::Color::DkSepia;
        case 22:  return wsl::Color::LtGrey;
        case 23:  return wsl::Color::Grey;
        case 24:  return wsl::Color::DkGrey;
        case 25:  return wsl::Color::LtMagenta;
        case 26:  return wsl::Color::Magenta;
        case 27:  return wsl::Color::DkMagenta;
        case 28:  return wsl::Color::LtCyan;
        case 29:  return wsl::Color::Cyan;
        case 30:  return wsl::Color::DkCyan;
        case 31:  return wsl::Color::Black;
        case 32:  return wsl::Color::White;
        default:  return wsl::Color::White;
    }
}

Entity * pick(wsl::DLList<Entity> * list, std::string name)
{
    Entity * result = NULL;
    for(wsl::DLNode<Entity> * node = list->head(); node != NULL; node = node->next)
    {
        if(node->data.name() == name)
        {
            result = &node->data;
        }
    }
    return result;
}
            
} //namespace monster
