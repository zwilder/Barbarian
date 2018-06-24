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

#include "../include/color.hpp"

namespace wsl
{

/*
* These colors and their definitions are from: http://nethack4.org/blog/portable-terminal-codes.html
*/
// const Color Color::Black(uint32_t(0x000000FF));
// const Color Color::DarkRed(uint32_t(0xAF0000FF));
// const Color Color::DarkGreen(uint32_t(0x008700FF));
// const Color Color::Brown(uint32_t(0xAF5F00FF));
// const Color Color::DarkBlue(uint32_t(0x0000AFFF));
// const Color Color::DarkMagenta(uint32_t(0x870087FF));
// const Color Color::DarkCyan(uint32_t(0x00AF87FF));
// const Color Color::Grey(uint32_t(0xAFAFAFFF));
// const Color Color::DarkGrey(uint32_t(0x5F5F5FFF));
// const Color Color::Orange(uint32_t(0xFF5F00FF));
// const Color Color::BrightGreen(uint32_t(0x00FF00FF));
// const Color Color::Yellow(uint32_t(0xFFFF00FF));
// const Color Color::BrightBlue(uint32_t(0x875FFFFF));
// const Color Color::BrightMagenta(uint32_t(0xFF5FAFFF));
// const Color Color::BrightCyan(uint32_t(0x00D7FFFF));
// const Color Color::White(uint32_t(0xFFFFFFFFF));

/* 
 * These are some of the DawnBringer colors
 */
// const Color Color::Black(0,0,0);
// const Color Color::White(255,255,255);
// const Color Color::Red(217,0,0);
// const Color Color::Green(0,217,0);
// const Color Color::Blue(0,0,217);
// const Color Color::DkGrey(51,51,51);
// const Color Color::LtGrey(128,128,128);
// const Color Color::Orange(217,108,0);
// const Color Color::Yellow(217,217,0);
// const Color Color::Cyan(0,217,217);
// const Color Color::Brown(128,102,64);
// const Color Color::Purple(217,0,217);

/*
* These are some cherry picked colors from libtcod
*/
const Color Color::LtRed(255,115,115);
const Color Color::Red(255,0,0);
const Color Color::DkRed(128,0,0);
const Color Color::LtOrange(255,185,115);
const Color Color::Orange(255,127,0);
const Color Color::DkOrange(128,64,0);
const Color Color::LtYellow(255,255,115);
const Color Color::Yellow(255,255,0);
const Color Color::DkYellow(128,128,0);
const Color Color::LtGreen(115,255,115);
const Color Color::Green(0,255,0);
const Color Color::DkGreen(0,128,0);
const Color Color::LtBlue(115,115,255);
const Color Color::Blue(127,0,255);
const Color Color::DkBlue(0,0,128);
const Color Color::LtViolet(85,115,255);
const Color Color::Violet(127,0,255);
const Color Color::DkViolet(64,0,128);
const Color Color::LtBrown(158,134,100);
const Color Color::Brown(127,101,63);
const Color Color::DkBrown(63,50,31);
const Color Color::LtGrey(159,159,159);
const Color Color::Grey(127,127,127);
const Color Color::DkGrey(63,63,63);
const Color Color::LtMagenta(255,115,220);
const Color Color::Magenta(255,0,191);
const Color Color::DkMagenta(128,0,95);
const Color Color::LtCyan(115,255,255);
const Color Color::Cyan(0,255,255);
const Color Color::DkCyan(0,128,128);
const Color Color::Black(0,0,0);
const Color Color::White(255,255,255);

Color::Color() : r(255),g(255),b(255),a(255)
{
    //
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue), a(255)
{
    //
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : r(red), g(green), b(blue), a(alpha)
{
    //
}

Color::Color(uint32_t color) : r((color & 0xff000000) >> 24), g((color & 0x00ff0000) >> 16), b((color & 0x0000ff00) >> 8), a((color & 0x000000ff) >> 0)
{
    //
}

} // namespace wsl
