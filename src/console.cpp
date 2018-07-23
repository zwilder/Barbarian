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

#include <sstream>
#include <iostream>
#include <iterator>

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
    std::istringstream iss(msg);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
    int curX = x;
    int curY = y;
    for(size_t i = 0; i < results.size(); ++i)
    {
        // Each results[i] is a word to be printed
        // So we need the length of the word
        std::string & word = results[i];
        size_t wordLength = word.size();
        // We then check to see if there is enough room to print the word
        bool enoughRoom = (curX + int(wordLength)) < width_;
        // If there is enough room print, the word. Otherwise advance the curY, reset the curX to x, and print the word.
        if(enoughRoom)
        {
            for(size_t j = 0; j < wordLength; ++j)
            {
                screen_[curX + (curY * width_)] = Glyph(word[j]);
                curX++;
            }
            screen_[curX + (curY * width_)] = Glyph(' '); 
            curX++;
        }
        else //!enoughRoom
        {
            curY++;
            curX = x;
            for(size_t j = 0; j < wordLength; ++j)
            {
                screen_[curX + (curY * width_)] = Glyph(word[j]);
                curX++;
            }
            screen_[curX + (curY * width_)] = Glyph(' '); 
            curX++;
        }
    }
}

void Console::printf(int x, int y, std::string msg, Color fg, Color bg)
{
    // This is a separate function from Console::print for no reason right now - eventually I want to have in string formatting
    // so I can do things like:
    //  msg = "Hello {{Color::Green}}World!{{/}}" 
    // or something. Don't know how to do that, yet.
    std::istringstream iss(msg);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
    int curX = x;
    int curY = y;
    for(size_t i = 0; i < results.size(); ++i)
    {
        // Each results[i] is a word to be printed
        // So we need the length of the word
        std::string & word = results[i];
        size_t wordLength = word.size();
        // We then check to see if there is enough room to print the word
        bool enoughRoom = (curX + int(wordLength)) < width_;
        // If there is enough room print, the word. Otherwise advance the curY, reset the curX to x, and print the word.
        if(enoughRoom)
        {
            for(size_t j = 0; j < wordLength; ++j)
            {
                screen_[curX + (curY * width_)] = Glyph(word[j], fg, bg);
                curX++;
            }
            screen_[curX + (curY * width_)] = Glyph(' ', fg, bg); 
            curX++;
        }
        else //!enoughRoom
        {
            curY++;
            curX = x;
            for(size_t j = 0; j < wordLength; ++j)
            {
                screen_[curX + (curY * width_)] = Glyph(word[j], fg, bg);
                curX++;
            }
            screen_[curX + (curY * width_)] = Glyph(' ', fg, bg); 
            curX++;
        }
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
