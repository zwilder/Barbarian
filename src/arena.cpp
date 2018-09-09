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

/*
* Actually, this file is not a part of Barbarian at all - This is a simple program
* written to test monsters/item stats for Barbarian. It reads items.config and monsters.config,
* allows the user to choose two monsters, equip items to them, and pit them against each other
* in a fight TO THE DEATH.
*
* Well, thats what it started as, but it's devolved into an even simpler test to see if a character with 
* bare minimum stats (couch potato) with maximum equipment (forged by the gods!) could
* beat a character with maximum stats (Bruce Lee) with minimum equipment (cloth pants and his fists).
*
* In my opinion, Bruce Lee wins, no contest, every single damn time - so the stat calculations should reflect
* that. Sure, Couch Potato might get ONE lucky hit in... but after that Bruce is woopin some ass.
*
* In this test program, the weapon item owned by an actor is a combination of ALL offensive damage/bonuses.
* Likewise, armor is a combination of ALL defensive stats.
*
* g++ -std=c++17 -o Arena "src/random.cpp" "src/arena.cpp"
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <chrono>

#include "../include/dllist.hpp"
#include "../include/random.hpp"

/*****
 * Dice definition/functions
 *****/
class Dice
{
    public:
        Dice(int n=1, int s=1) : num(n), sides(s) { }

        int roll(wsl::RNGState * rng);

        int num;
        int sides;
};

int Dice::roll(wsl::RNGState * rng)
{
    int result = 0;
    for(int i = 0; i < num; ++i)
    {
        result += randomInt(1,sides,rng);
    }
    return result;
}

/*****
 * Item definition/functions
 *****/
class Item
{
    public:
        Item();

        Dice damage;
        int defBonus;
        int damBonus;
        int arBonus;
        int hpBonus;
        int strBonus;
        int vitBonus;
        int agiBonus;
        int forBonus;
        int intBonus;
};

Item::Item()
{
    damage = Dice(0,0);
    defBonus = 0;
    damBonus = 0;
    arBonus = 0;
    hpBonus = 0;
    strBonus = 0;
    vitBonus = 0;
    agiBonus = 0;
    forBonus = 0;
    intBonus = 0;
}

/*****
 * Actor definition/functions
 *****/
class Actor
{
    public:
        Actor(int s=1,int v=1,int a=1,int f=1, int i=1);

        // Calculated stats
        int totalStrength();
        int totalVitality();
        int totalAgility();
        int totalFortitude();
        int totalIntellect();
        int damageBonus();
        int defenseRating();
        int attackRating();
        int speed();
        int attackDamage(wsl::RNGState * rng);

        // Utility
        void takeDamage(int damage);
        void attack(Actor * other, wsl::RNGState * rng);

        // Derived Stats
        int hp;
        int hpMax;
        int energy;
        bool alive;
        int xp;

        // Core stats
        std::string name;
        int strength;
        int vitality;
        int agility;
        int fortitude;
        int intellect;

        // Inventory
        Item weapon;
        Item armor;
};

Actor::Actor(int s,int v,int a,int f, int i) : strength(s), vitality(v), agility(a), fortitude(f), intellect(i)
{
    alive = true;
    hpMax = 5 * (vitality + fortitude);
    hp = hpMax;
    energy = 0;
    xp = s + v + a + f + i;
    name = "Foo";
}

int Actor::totalStrength()
{
    return strength + weapon.strBonus + armor.strBonus;
}

int Actor::totalAgility()
{
    return agility + weapon.agiBonus + armor.agiBonus;
}

int Actor::totalVitality()
{
    return vitality + weapon.vitBonus + armor.vitBonus;
}

int Actor::totalFortitude()
{
    return fortitude + weapon.forBonus + armor.forBonus;
}

int Actor::totalIntellect()
{
    return intellect + weapon.intBonus + armor.intBonus;
}

int Actor::damageBonus()
{
    int result = int(std::round((totalStrength() + totalAgility()) / 5));
    result += weapon.damBonus + armor.damBonus;
    return result;
}

int Actor::defenseRating()
{
    int result = int(std::round((totalFortitude() + totalAgility()) / 1));
    result += weapon.defBonus + armor.defBonus;
    return result;
}

int Actor::attackRating()
{
    int result = totalStrength() + totalIntellect();
    result += weapon.arBonus + armor.arBonus;
    return result;
}

int Actor::speed()
{
    return int(std::round((totalAgility() + totalVitality()) * 2.5));
}

void Actor::takeDamage(int damage)
{
    hp -= damage;
    if(hp <=0) alive = false;
}

int Actor::attackDamage(wsl::RNGState * rng)
{
    int result = weapon.damBonus;
    result += weapon.damage.roll(rng);
    return result;
}

void Actor::attack(Actor * other, wsl::RNGState * rng)
{
    int defenseRoll = randomInt(1,100,rng) + other->defenseRating();
    int attackRoll = randomInt(1,100,rng) + attackRating();
    if(attackRoll >= defenseRoll)
    {
        other->takeDamage(attackDamage(rng));
    }
}

/*****
 * File handling
 *****/

// wsl::DLList<Actor> loadMonsters(std::string filename)
// {
//     wsl::DLList<Actor> result;
//     std::cout << "Loading " << filename << "..." << std::endl;
//
//     return result;
// }

// wsl::DLList<Item> loadItems(std::string filename)
// {
//     wsl::DLList<Item> result;
//     std::cout << "Loading " << filename << "..." << std::endl;
//
//     return result;
// }

/*****
 * Main
 *****/
void singleCombat(int totalRounds, Actor * combatantA, Actor * combatantB, wsl::RNGState * rng)
{
    int rounds = 0;
    int aWins = 0;
    int bWins = 0;
    int aHPLoss = combatantA->hpMax;
    int bHPLoss = combatantB->hpMax;
    combatantA->hp = combatantA->hpMax;
    combatantB->hp = combatantB->hpMax;
    for(rounds = 0; rounds < totalRounds; ++rounds)
    {
        // Run combat
        while(combatantA->alive && combatantB->alive)
        {
            while(combatantA->energy >= 25)
            {
                combatantA->attack(combatantB, rng);
                combatantA->energy -= 25;
            }
            while(combatantB->energy >= 25)
            {
                combatantB->attack(combatantA, rng);
                combatantB->energy -= 25;
            }
            combatantA->energy += combatantA->speed();
            combatantB->energy += combatantB->speed();
        }

        // Update results
        if(combatantA->alive)
        {
            aWins++;
            if(aHPLoss > combatantA->hp)
            {
                aHPLoss = combatantA->hp;
            }
        }
        else
        {
            bWins++;
            if(bHPLoss > combatantB->hp)
            {
                bHPLoss = combatantB->hp;
            }
        }
        combatantA->hp = combatantA->hpMax;
        combatantA->alive = true;
        combatantB->hp = combatantB->hpMax;
        combatantB->alive = true;
    }
    if(aHPLoss == combatantA->hpMax)
    {
        aHPLoss = 0;
    }
    if(bHPLoss == combatantB->hpMax)
    {
        bHPLoss = 0;
    }

    std::cout << "After " << rounds << " rounds..." << std::endl;
    std::cout << combatantA->name << " result wins: " << aWins << ", with the lowest hp of " << aHPLoss << " out of " << combatantA->hpMax << std::endl;
    std::cout << combatantB->name << " result wins: " << bWins << ", with the lowest hp of " << bHPLoss << " out of " << combatantB->hpMax << std::endl;
}

int toTheDeath(Actor * champion, Actor * challengers, wsl::RNGState * rng)
{
    int result = 0;
    champion->hp = champion->hpMax;
    challengers->hp = challengers->hpMax;

    while(champion->alive)
    {
        while(champion->energy > 25)
        {
            champion->attack(challengers, rng);
            champion->energy -= 25;
        }
        while(challengers->energy > 25)
        {
            if(!challengers->alive)
            {
                break;
            }
            challengers->attack(champion, rng);
            challengers->energy -= 25;
        }
        if(!challengers->alive)
        {
            challengers->hp = challengers->hpMax;
            challengers->alive = true;
            result += 1;
        }
        challengers->energy += 25;
        champion->energy += 25;
    }

    return result;
}

int main(int argc, char * argv[])
{
    // wsl::DLList<Actor> monsterList = loadMonsters("assets/monsters.config");
    // wsl::DLList<Item> itemList = loadItems("assets/items.config");
    uint32_t seed = uint32_t(std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count());
    wsl::RNGState * rng = new wsl::RNGState(seed);

    Actor maxCombatant(30,30,30,30,30);
    maxCombatant.weapon.damage = Dice(1,4);
    maxCombatant.name = "Max";
    // maxCombatant.armor.defBonus = 30;
    Actor minCombatant;
    minCombatant.name = "Min";
    minCombatant.weapon.damage = Dice(3,12);
    minCombatant.weapon.damBonus = 6;
    minCombatant.armor.defBonus = 30;

    singleCombat(100000,&maxCombatant, &minCombatant, rng);

    Actor anotherMax = maxCombatant;
    singleCombat(100, &maxCombatant, &anotherMax, rng);

    Actor player(10,10,10,10,10);
    player.weapon.damage = Dice(1,6);
    player.armor.defBonus = 5;
    player.name = "Player";
    Actor rat(2,4,2,1,1);
    rat.weapon.damage = Dice(1,4);
    rat.name = "Rat";
    singleCombat(1, &rat, &player, rng);

    std::cout << "Player fought and killed " << toTheDeath(&player, &rat, rng) << " rats before dying.\n";
    std::cout << "Max fought and killed " << toTheDeath(&anotherMax, &rat, rng) << " rats before dying.\n";

    delete rng;
    return 0;
}
