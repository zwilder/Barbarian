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

#include <stringstream>

#include "../include/monsters.hpp"
#include "../include/entity.hpp"
#include "../include/engine.hpp"
#include "../include/items.hpp"

namespace monster
{
/*
wsl::DLList<Entity> loadMonsters()
{
     // * 1) Open ../assets/monsters.txt
     // * 2) Start reading file, ignore lines where the first character is a '#'
     // * 3) Read word 'name:' -> start new entry
     // * 4) read lines and add to entryString until read ;
     // * 5) call parseEntry(entryString)
     // * 6) repeat 3-5 until EOF
}

Entity parseEntry(std::string entry)
{
    // # name: foo             # Name of the monster
    // # symbol: +             # Glyph symbol
    // # fg: 31                # Glyph foreground color
    // # bg: 5                 # Glyph background color
    // # speed: 50             # Speed
    // # vision: 1             # Field of view radius
    // # maxHP: 1              # Maximum health
    // # defense: 1            # Defense
    // # power: 1              # Power
    // # xp: 0                 # Experience gained on kill
    // # inventory: 0          # False/True (0/1) - has inventory component
    // # level: 0              # False/True (0/1) - has level component
    // # ai: 1                 # AI None/Simple (0,1)
    // # items:                # Names of items to add to entity inventory (comma separated)
    // # minLevel: 1           # Minimum depth monster is found 
    // # maxLevel: 2           # Maximum depth monster is found
    // # ;                     # End of entry
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
    // break entry into lines
    std::vector<std::string> lines;
    std::string delimiter = "\n";
    std::string token;
    size_t pos = 0;
    while((pos = s.find(delimeter)) != std::string::npos)
    {
        token = entry.substr(0,pos);
        lines.push_back(token);
        entry.erase(0, pos + delimiter.length());
    }
    // for each line:
    for(size_t i = 0; i < lines.size(); ++i)
    {
        std::string & currentLine = lines[i];
        std::stringstream iss(currentLine);
        //  break line into words
        std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
        for(size_t j = 0; j < results.size(); ++j)
        {
            std::cout << results[i] << "\t";
        }
        std::cout << std::endl;
        //  first word is id, second is value
        //  set value to id 
    }
    // return result entity 
}
*/

Entity player(Engine * engine, wsl::Vector2i pos)
{
    Entity player(engine, pos, wsl::Glyph('@', wsl::Color::Black, wsl::Color::Green), "Griff");
    player.makeActor(Actor(50,5,100,1,2)); //s,v,mH,d,p,x
    player.makeInventory();
    player.makeLevel(Level());

    {
        Entity dagger = item::dagger(engine);
        engine->entityList()->push(dagger);
    }   

    Entity * dagger = &(engine->entityList()->head()->data);
    player.pickup(dagger);
    player.use(0);
    
    return player;
}

Entity skeleton(Engine * engine, wsl::Vector2i pos)
{
    Entity skeleton(engine, pos, wsl::Glyph('s', wsl::Color::LtGrey), "skeleton");
    skeleton.makeActor(Actor(25,8,20,0,4,35)); //s,v,mH,d,p,x
    skeleton.engage(Entity::Flags::AI);
    return skeleton;
}

Entity shamblingCorpse(Engine * engine, wsl::Vector2i pos)
{
    Entity corpse(engine, pos, wsl::Glyph('Z', wsl::Color::Red), "shambling corpse");
    corpse.makeActor(Actor(75,8,30,2,8,100)); //s,v,mH,d,p,x
    corpse.engage(Entity::Flags::AI);
    return corpse;
}

} //namespace monster
