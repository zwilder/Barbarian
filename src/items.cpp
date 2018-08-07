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

namespace item
{

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

} //namespace item
