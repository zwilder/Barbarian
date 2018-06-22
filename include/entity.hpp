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

#include "vector.hpp"
#include "console.hpp"

class Entity
{
    public:
        Entity(wsl::Vector2i pos = wsl::Vector2i(0,0), wsl::Glyph glyph = wsl::Glyph(' ')) : pos_(pos), glyph_(glyph) { } 
        
        void move(wsl::Vector2i delta) { pos_ += delta; }
        wsl::Vector2i pos() { return pos_; }
        void setPos(wsl::Vector2i pos) { pos_ = pos; }
        wsl::Glyph glyph() { return glyph_; }

    private:
        wsl::Vector2i pos_; // x, y
        wsl::Glyph glyph_; // Color, symbol

};

#endif //ENTITY_HPP
