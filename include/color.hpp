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
 * A lot of this was inspired from SFML's color file and from other sources where noted
 */

#pragma once
#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>

namespace wsl
{
    class Color
    {
        public:
            Color();
            Color(uint8_t red, uint8_t green, uint8_t blue);
            Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
            Color(uint32_t color);

            /*
             * I'm not sure where I found these colors originally, but I used them in a previous project and they were pretty ok.
             */ 
            static const Color Black;
            static const Color White;
            static const Color Red;
            static const Color Green;
            static const Color Blue;
            static const Color DkGrey;
            static const Color LtGrey;
            static const Color Orange;
            static const Color Yellow;
            static const Color Cyan;
            static const Color Brown;
            static const Color Purple;

            /*
             * These colors and their definitions are from: http://nethack4.org/blog/portable-terminal-codes.html
             */
            // static const Color Black;
            // static const Color DarkRed;
            // static const Color DarkGreen;
            // static const Color Brown;
            // static const Color DarkBlue;
            // static const Color DarkMagenta;
            // static const Color DarkCyan;
            // static const Color Grey;
            // static const Color DarkGrey;
            // static const Color Orange;
            // static const Color BrightGreen;
            // static const Color Yellow;
            // static const Color BrightBlue;
            // static const Color BrightMagenta;
            // static const Color BrightCyan;
            // static const Color White;

            inline bool operator ==(const Color & other) { return((r == other.r) && (g == other.g) && (b == other.b) && (a == other.a)); }
            
            inline bool operator !=(const Color & other) { return(!(*this == other)); }
            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;
    };
} // namespace wsl

#endif // COLOR_HPP
