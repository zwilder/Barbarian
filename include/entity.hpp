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

#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include <memory>
#include <string>
#include "dllist.hpp"
#include "vector.hpp"
#include "console.hpp"
#include "bitflag.hpp"

class Actor
{
    public:
        Actor(int s = 50, int v = 4, int mH = 30, int d = 1, int p = 6);
        
        // enum Action
        // {
        //     None,
        //     Attack,
        //     Move,
        //     Rest
        // };
        
        int speed;
        int vision;
        int energy;
        int maxHP;
        int HP;
        int defense;
        int power;
};

class Item
{
    public:
        Item(int u = 0, int q = 0, bool s = false);
        enum UseFunction : uint8_t
        {
            None,
            Heal
        };
        bool carried;
        bool stackable;
        int quantity;
        UseFunction useFunction;
};

class Engine;
class Entity : public wsl::BitFlag
{
    public:
        Entity();
        Entity(Engine * game, wsl::Vector2i pos, wsl::Glyph glyph, std::string name);

        // Component flags
        enum Flags : uint16_t
        {
            NONE = 0,
            POS = 0x0002,
            GLYPH = 0x0004,
            VISION = 0X0008,
            BLOCKS = 0x0010,
            ACTOR = 0x0020,
            AI = 0x0040,
            DEAD = 0x0080,
            ITEM = 0x0100,
            INVENTORY = 0x0200
        };
        
        // Component checks
        bool hasPos() { return check(Flags::POS); }
        bool hasGlyph() { return check(Flags::GLYPH); }
        bool hasVision() { return check(Flags::VISION); }
        bool blocks() { return check(Flags::BLOCKS); }
        bool isActor() { return check(Flags::ACTOR); }
        bool isItem() { return check(Flags::ITEM); }
        bool hasInventory() { return check(Flags::INVENTORY); }

        // Generic Entity functions
        void move(wsl::Vector2i delta);
        wsl::Vector2i pos();
        void setPos(wsl::Vector2i pos);
        wsl::Glyph & glyph();
        std::string name() { return name_; }
        
        // Actor functions
        void makeActor(Actor actor);
        // void grantEnergy();
        // int & energy() { return energy_; }
        // int & speed() { return speed_; }
        // void setNextAction(Action action);
        int & hp() { return actor_->HP; }
        int & maxHP() { return actor_->maxHP; }
        int & defense() { return actor_->defense; }
        int & power() { return actor_->power; }
        int vision() { return actor_->vision; }
        void takeDamage(int damage);
        bool update();

        // Item/Inventory Functions
        void makeItem(Item item);
        void makeInventory();
        bool carried() { return item_->carried; }
        void pickup(Entity * itemEntity);
        void drop(int index);
        void use(int index);
        wsl::DLList<Entity> * inventory() { return inventory_.get(); }
        int & quantity() { return item_->quantity; }
        bool stackable() { return item_->stackable; }

        Engine * game() { return game_; }

    private:
        Engine * game_;

        // Components
        wsl::Vector2i pos_; 
        wsl::Glyph glyph_; 
        std::string name_;
        std::shared_ptr<Actor> actor_;
        std::shared_ptr<Item> item_;
        std::shared_ptr< wsl::DLList<Entity> > inventory_;

        // Use Functions
        void use_heal_();
};

#endif //ENTITY_HPP
