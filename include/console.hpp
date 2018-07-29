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
#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>
#include <vector>
#include "color.hpp"

namespace wsl
{
   class Glyph
    {
        // The background is always 219 on the CP437 font (the blank square)
        public:
            Glyph();
            Glyph(uint8_t symbol, Color color = Color(), Color bg = Color(0,0,0));

            uint8_t symbol() { return symbol_; }
            const Color & color();
            const Color & bgColor();
            void setColor(Color color);
            void setBgColor(Color color);

            template<class Archive>
            void serialize(Archive & ar)
            {
                ar(symbol);
                ar(color_);
                ar(bgColor_);
            }

        private:
            uint8_t symbol_;
            Color color_;
            Color bgColor_;
    };

    class Console
    {
        public:
            Console(int width = 80, int height = 60);

            int width() { return width_; }
            int height() { return height_; }
            Glyph get(int x, int y);
            void put(int x, int y, Glyph glyph);
            void clear(int x, int y);
            inline int index(int x, int y) { return (x + (y * width_)); }           
            void flush();
            void print(int x, int y, std::string msg);
            void printf(int x, int y, std::string msg, Color fg = Color::White, Color bg = Color::Black);

            template<class Archive>
            void serialize(Archive & ar)
            {
                ar(width_, height_);
                ar(screen_);
            }
        private:
            int width_;
            int height_;
            std::vector<Glyph> screen_;

    };

} //Namespace wsl

#endif //CONSOLE_HPP
