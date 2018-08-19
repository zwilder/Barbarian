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

#include "../include/items.hpp"
#include "../include/entity.hpp"
#include "../include/engine.hpp"
#include "../include/monsters.hpp"

namespace item
{

void loadItems(Engine * engine)
{
    wsl::DLList<Entity> * list = engine->itemList();
    list->clear();
    std::ifstream file("assets/items.config");
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
    //Entity
    std::string name = "foo";
    char symbol = '+';
    wsl::Color fgColor = wsl::Color::White;
    wsl::Color bgColor = wsl::Color::Black;
    int mlvl = 0;
    int wt = 0;
    //Item
    int qty = 1;
    bool stackable = false;
    std::string useFlagString;
    //Equip
    int hpBonus = 0;    
    int defenseBonus = 0;
    int powerBonus = 0;
    std::string equipFlagString;

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
                //Entity
                if(nvp.x == "name") name = nvp.y;
                if(nvp.x == "sym") symbol = nvp.y[0];
                if(nvp.x == "fg") fgColor = monster::parseColor(std::stoi(nvp.y));
                if(nvp.x == "bg") bgColor = monster::parseColor(std::stoi(nvp.y));
                if(nvp.x == "wt") wt = std::stoi(nvp.y);
                if(nvp.x == "mlvl") mlvl = std::stoi(nvp.y);

                //Item
                if(nvp.x == "stk" && nvp.y == "1") stackable = true;
                if(nvp.x == "qty") qty = std::stoi(nvp.y);
                if(nvp.x == "use") useFlagString = nvp.y;

                //Equip
                if(nvp.x == "mhp") hpBonus = std::stoi(nvp.y);
                if(nvp.x == "def") defenseBonus = std::stoi(nvp.y);
                if(nvp.x == "pow") powerBonus = std::stoi(nvp.y);
                if(nvp.x == "eqp") equipFlagString = nvp.y;
            }
        }
    }

    Entity resultEntity(engine, wsl::Vector2i(), wsl::Glyph(symbol, fgColor, bgColor), name, wt, mlvl);
    //Make Item component
    resultEntity.makeItem(Item(parseUse(useFlagString), qty, stackable));
    //Make Equip component
    if(resultEntity.isEquipment())
    {
        result.makeEquipment(Equipment(parseEquip(equipFlagString, powerBonus, defenseBonus, hpBonus)); // Equipment(Equipment::Flags, atkBonus, defBonus, hpBonus)
    }
    return resultEntity;
}

int parseUse(std::string useString)
{
    //Take string, split and return mask 
/*
# Use
# 1   - Heal
# 2   - Cast Lightning
# 3   - Potion
# 4   - Scroll
# 5   - Cast Fireball
# 6   - Cast Firebolt
# 7   - Equip
#
*/
}

int parseEquip(std::string eqpString)
{
    //Take string, split and return mask 
    /*
# Eqp
# 1   - Main Hand
# 2   - Off Hand
# 3   - Body
# 4   - Back
# 5   - L Ring
# 6   - R Ring
# 7   - Boots
# 8   - Ranged
# 9   - Ammo
    */
}

// Below will be deleted
Entity healingPotion(Engine * engine, wsl::Vector2i pos)
{
    Entity result(engine, pos, wsl::Glyph('!', wsl::Color::LtRed), "healing potion");
    result.makeItem(Item(Item::Flags::HEAL | Item::Flags::POTION, 1, true)); // Item(Item::Flags, quantity, stackable)
    return result;
}

Entity lightningScroll(Engine * engine, wsl::Vector2i pos)
{
    Entity result(engine, pos, wsl::Glyph('?', wsl::Color::LtYellow), "scroll of lightning");
    result.makeItem(Item(Item::Flags::CAST_LIGHTNING | Item::Flags::SCROLL, 1, false)); // Item(Item::Flags, quantity, stackable)
    return result;
}

Entity fireballScroll(Engine * engine, wsl::Vector2i pos)
{
    Entity result(engine, pos, wsl::Glyph('?', wsl::Color::LtYellow), "scroll of fireball");
    result.makeItem(Item(Item::Flags::CAST_FIREBALL | Item::Flags::SCROLL, 1, false)); // Item(Item::Flags, quantity, stackable)
    return result;
}

Entity fireboltScroll(Engine * engine, wsl::Vector2i pos)
{
    Entity result(engine, pos, wsl::Glyph('?', wsl::Color::LtYellow), "scroll of firebolt");
    result.makeItem(Item(Item::Flags::CAST_FIREBOLT | Item::Flags::SCROLL, 1, false)); // Item(Item::Flags, quantity, stackable)
    return result;
}

Entity woodenShield(Engine * engine, wsl::Vector2i pos)
{
    Entity result(engine, pos, wsl::Glyph(']', wsl::Color::Sepia), "wooden shield");
    result.makeEquipment(Equipment(Equipment::Flags::OFF_HAND, 0, 1, 0)); // Equipment(Equipment::Flags, atkBonus, defBonus, hpBonus)
    return result;
}

Entity battleAxe(Engine * engine, wsl::Vector2i pos)
{
    Entity result(engine, pos, wsl::Glyph(')', wsl::Color::LtCyan), "battle axe");
    result.makeEquipment(Equipment(Equipment::Flags::MAIN_HAND, 4, 0, 0)); // Equipment(Equipment::Flags, atkBonus, defBonus, hpBonus)
    return result;
}

Entity dagger(Engine * engine, wsl::Vector2i pos)
{
    Entity result(engine, pos, wsl::Glyph(')', wsl::Color::LtCyan), "dagger");
    result.makeEquipment(Equipment(Equipment::Flags::OFF_HAND, 2, 0, 0));
    return result;
}

} //namespace item
