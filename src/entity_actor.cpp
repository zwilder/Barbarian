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

#include "../include/game_map.hpp"
#include "../include/engine.hpp"
#include "../include/pathfinding.hpp"
#include "../include/random.hpp"

/* 
 * BonusStruct is a convience structure so that I don't have to repeat some code below - makes it so that I can
 *  check all the actor's slots ONCE and return all the bonuses, instead of repeating the code multiple times.
 *  This will also help when I eventually change the combat system and add new bonuses.
 * Since it's solely a convience structure, it shouldn't be used elsewhere.
 */
class BonusStruct
{
    public:
        BonusStruct(int h = 0, int d = 0, int p = 0) : hp(h), def(d), pow(p) { }
        int hp;
        int def;
        int pow;
};

BonusStruct getBonus(Entity * entity)
{
    BonusStruct bonus;
    if(!entity->isActor())
    {
        return bonus;
    }

    Actor actor = entity->actor();
    if(actor.check(Actor::Flags::EQUIP_MAIN_HAND))
    {
        Entity * item = entity->itemInSlot(Equipment::Flags::MAIN_HAND);
        if(item)
        {
            bonus.hp += item->healthBonus();
            bonus.def += item->defenseBonus();
            bonus.pow += item->powerBonus();
        }
    }
    if(actor.check(Actor::Flags::EQUIP_OFF_HAND))
    {
        Entity * item = entity->itemInSlot(Equipment::Flags::OFF_HAND);
        if(item)
        {
            bonus.hp += item->healthBonus();
            bonus.def += item->defenseBonus();
            bonus.pow += item->powerBonus();
        }
    }
    if(actor.check(Actor::Flags::EQUIP_BODY))
    {
        Entity * item = entity->itemInSlot(Equipment::Flags::BODY);
        if(item)
        {
            bonus.hp += item->healthBonus();
            bonus.def += item->defenseBonus();
            bonus.pow += item->powerBonus();
        }
    }
    if(actor.check(Actor::Flags::EQUIP_BACK))
    {
        Entity * item = entity->itemInSlot(Equipment::Flags::BACK);
        if(item)
        {
            bonus.hp += item->healthBonus();
            bonus.def += item->defenseBonus();
            bonus.pow += item->powerBonus();
        }
    }
    if(actor.check(Actor::Flags::EQUIP_LRING))
    {
        Entity * item = entity->itemInSlot(Equipment::Flags::LRING);
        if(item)
        {
            bonus.hp += item->healthBonus();
            bonus.def += item->defenseBonus();
            bonus.pow += item->powerBonus();
        }
    }
    if(actor.check(Actor::Flags::EQUIP_RRING))
    {
        Entity * item = entity->itemInSlot(Equipment::Flags::RRING);
        if(item)
        {
            bonus.hp += item->healthBonus();
            bonus.def += item->defenseBonus();
            bonus.pow += item->powerBonus();
        }
    }
    if(actor.check(Actor::Flags::EQUIP_BOOTS))
    {
        Entity * item= entity->itemInSlot(Equipment::Flags::BOOTS);
        if(item)
        {
            bonus.hp += item->healthBonus();
            bonus.def += item->defenseBonus();
            bonus.pow += item->powerBonus();
        }
    }
    if(actor.check(Actor::Flags::EQUIP_RANGED))
    {
        Entity * item= entity->itemInSlot(Equipment::Flags::RANGED);
        if(item)
        {
            bonus.hp += item->healthBonus();
            bonus.def += item->defenseBonus();
            bonus.pow += item->powerBonus();
        }
    }
    if(actor.check(Actor::Flags::EQUIP_AMMO))
    {
        Entity * item = entity->itemInSlot(Equipment::Flags::AMMO);
        if(item)
        {
            bonus.hp += item->healthBonus();
            bonus.def += item->defenseBonus();
            bonus.pow += item->powerBonus();
        }
    }
    return bonus;
}

Actor::Actor(int s, int v, int mH, int d, int p, int x) : speed(s), vision(v), maxHP(mH), defense(d), power(p), xp(x)
{
    HP = maxHP;
    energy = 0;
}

void Entity::makeActor(Actor actor)
{
    engage(Flags::VISION);
    engage(Flags::ACTOR);
    engage(Flags::BLOCKS);
    actor_ = std::make_shared<Actor>();
    *actor_ = actor;
}

int Entity::maxHP()
{
    if(!isActor())
    {
        return 0;
    }
    int bonus = getBonus(this).hp;
    return (actor_->maxHP + bonus);
}

int Entity::defense()
{
    if(!isActor())
    {
        return 0;
    }
    int bonus = getBonus(this).def;
    return (actor_->defense + bonus);
}

int Entity::power()
{
    if(!isActor())
    {
        return 0;
    }
    int bonus = getBonus(this).pow;
    return (actor_->power + bonus);
}

// void Entity::grantEnergy()
// {
//     if(check(Flags::ACTOR))
//     {
//         energy_ += speed_;
//     }
// }
void Entity::takeDamage(int damage)
{
    if((actor_->HP <= 0) || check(Flags::DEAD))
    {
        return;
    }
    if(damage <= 0)
    {
        if(this == game_->player())
        {
            game_->addMessage("The attack bounces off " + name() + "'s gleaming muscles harmlessly!");
        }
        else
        {
            game_->addMessage(name() + " barely notices the attack.");
        }
    }
    else
    {
        actor_->HP -= damage;
    }
    if(actor_->HP <= 0)
    {
        // remove(Flags::ACTOR);
        // remove(Flags::BLOCKS);
        if(this == game_->player())
        {
            glyph() = wsl::Glyph('%', wsl::Color::Black, wsl::Color::DkRed);
            game_->addMessage(game_->player()->name() + " has perished!");
            game_->changeState(GameState::GAME_OVER);
        }
        else
        {
            wsl::Glyph oldGlyph = glyph();
            glyph() = wsl::Glyph('%', oldGlyph.color(), oldGlyph.bgColor());
            game_->addMessage("The " + name() + " collapses!");
            engage(Flags::DEAD);
        }
    }
}

void Entity::dealDamage(Entity * target, int damage)
{
    // int dealtDamage = wsl::randomInt(damage, game_->rng());
    // int critChance = wsl::randomInt(100, game_->rng());
    // if(critChance <= 10)
    // {
    //     dealtDamage += wsl::randomInt(1, damage, game_->rng());
    //     game_->addMessage(target->name() + " grunts in agony!");
    // }
    // target->takeDamage(dealtDamage);
    target->takeDamage(damage);
    if(target->check(Flags::DEAD))
    {
        bool levelUp = false;
        if(hasLevel())
        {
            levelUp = addXP(target->xp());
        }
        if(levelUp && (this == game_->player()))
        {
            game_->changeState(GameState::LEVEL_UP);
        }
    }
}

void Entity::heal(int qty)
{
    if(!isActor())
    {
        return;
    }
    actor_->HP += qty;
    if(actor_->HP > maxHP())
    {
        actor_->HP = maxHP();
    }
}

bool Entity::update()
{
    bool success = false;
    if(!check(Flags::ACTOR))
    {
        success = false;
    }
    else if(!check(Flags::AI))
    {
        //Player update
        success = true;
    }
    else if(!check(Flags::DEAD)) // if(fov::contains(game_->visible(), pos_)) // Right now the entities only move when they see the player
    {
        //Enemy update
        // All of this will be moved to separate functions depending on the type of AI.
        // The AI component will also have a state (Hunting, exploring, fleeing, etc)
        std::vector<wsl::Vector2i> visible;
        fov::visible(&visible, game_->gameMap(), this);
        if(fov::contains(&visible, game_->player()->pos()))
        {
            wsl::Vector2i next = path::bfsStep(game_->gameMap(), pos_, game_->player()->pos());
            Entity * entity = game_->gameMap()->actorAt(next);
            if(entity != NULL)
            {
                if(entity->isActor())
                {
                    game_->addMessage(name() + " kicks the " + entity->name() + ", much to it's annoyance."); 
                }
                else
                {
                    setPos(next);
                }
            }
            else if(next == game_->player()->pos())
            {
                game_->addMessage("The " + name() + " claws at " + game_->player()->name() + "!"); 
                // game_->player()->takeDamage(power() - game_->player()->defense());
                dealDamage(game_->player(), power() - game_->player()->defense());
            }
            else
            {
                //BFS will never set the next position in a blocked tile so there is no need to check for that here.
                setPos(next);
            }
        }
        success = true;
    }
    return success;
}
