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


#include "../include/console.hpp"

namespace wsl
{

Glyph::Glyph()
{
    symbol_ = 0;
    color_ = wsl::Color::White;
    bgColor_ = wsl::Color::Black;
}


Glyph::Glyph(uint8_t symbol, Color color, Color bg) : symbol_(symbol), color_(color), bgColor_(bg)
{
    //
}

const Color & Glyph::color()
{
    return color_;
}

const Color & Glyph::bgColor()
{
    return bgColor_;
}

void Glyph::setColor(Color color)
{
    color_ = color;
}

void Glyph::setBgColor(Color color)
{
    bgColor_ = color;
}

Console::Console(int width, int height) : width_(width), height_(height)
{
    screen_.assign(width_ * height_, Glyph(' '));
}

Glyph Console::get(int x, int y)
{
    return screen_[x + (y * width_)];
}

void Console::put(int x, int y, Glyph glyph)
{
    screen_[x + (y * width_)] = glyph;
}

void Console::clear(int x, int y)
{
    screen_[x + (y * width_)] = Glyph(' ');
}

void Console::print(int x, int y, std::string msg)
{
    size_t msgLength = msg.size();
    int widthAvailable = width_ - x;
    int dX = 0;
    int dY = y;
    for(size_t i = 0; i < msgLength; ++i)
    {
        if(dY != y)
        {
            dX = x + int(i) - widthAvailable;
        }
        else
        {
            dX = x + int(i);
        }
        if(dX >= width_)
        {
            dX = 0;
            dY += 1;
        }
        screen_[dX + (dY * width_)] = msg[i];
    }
}

void Console::flush()
{
    for(size_t i = 0; i < screen_.size(); ++i)
    {
        screen_[i] = Glyph(' ');
    }
}
} // namespace wsl
