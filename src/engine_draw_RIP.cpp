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
#include <ctime>

#include "../include/engine.hpp"

void Engine::draw_RIP_()
{
    // This function draws a cool gameover screen
    int xOfs = (console_->width() - 44) / 2; // Width of console - length of graphic, divided by two
    int yOfs = (console_->height() - 27) / 2;

    /*
     * Name Goes here centered
     * x,14
     * where 16 < x < 38 (17 + ofs)
     */
    std::string name = player_->name();
    int nameOfs = (22 - name.size()) / 2;
    console_->printf(17 + xOfs + nameOfs, 14 + yOfs, name, wsl::Color::White);

    /*
     * Depth goes here, formatted "XXXXft"
     * 30,17
     */
    std::string depth = std::to_string(gameMap_->currentLevel() * 50) + "ft";
    console_->printf(xOfs + 30, 17 + yOfs, depth, wsl::Color::White);

    /*
     * Date goes here, formatted "mm/dd/yyyy"
     * 22,19
     */
    // std::string date = "mm/dd/yyyy";
    std::time_t t = std::time(0);
    std::tm * now = std::localtime(&t);
    std::string mon = now->tm_mon + 1 < 10 ? "0" + std::to_string(now->tm_mon + 1) : std::to_string(now->tm_mon + 1);
    std::string day = now->tm_mday < 10 ? "0" + std::to_string(now->tm_mday) : std::to_string(now->tm_mday);
    std::string date = mon  + "/" + day  + "/" + std::to_string(1900 + now->tm_year);
    console_->printf(xOfs + 22, 19 + yOfs, date, wsl::Color::White);

    /*
     * XP goes here centered, formatted "XXXX xp."
     * x,20
     * where 16 < x < 38
     */
    std::string xp = std::to_string(player_->currentXP()) + " xp.";
    int xpOfs = (22 - xp.size()) / 2;
    console_->printf(17 + xOfs + xpOfs, 20 + yOfs, xp, wsl::Color::White);

    /*
     * "Killed by a" printed here if monster is cause of death
     * 22,22
     */

    /*
     * Cause of Death centered on
     * x,23
     * where 16 < x < 38
     */

    /*
     * [Press any key to continue]
     */
    console_->printf(1, console_->height() - 2, "[Press F2 to screenshot or any other key to continue]", wsl::Color::Grey);

    // This is the graphic, drawn in REXPaint, Zach Wilder (c) 2018
    console_->put(xOfs + 21,yOfs + 1 ,wsl::Glyph(46,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 1 ,wsl::Glyph(46,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 1 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 24,yOfs + 1 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 1 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 26,yOfs + 1 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 1 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 1 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 1 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 30,yOfs + 1 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 1 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs +  9,yOfs + 2 ,wsl::Glyph(46,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 2 ,wsl::Glyph(46,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 2 ,wsl::Glyph(46,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 2 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 2 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 2 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 33,yOfs + 2 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 8 ,yOfs + 3 ,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 10,yOfs + 3 ,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 3 ,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 3 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 3 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 3 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 3 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 17,yOfs + 4 ,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 4 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 4 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs +  2,yOfs + 5 ,wsl::Glyph(44,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs +  3,yOfs + 5 ,wsl::Glyph(46,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 5 ,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 17,yOfs + 5 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 37,yOfs + 5 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 1 ,yOfs + 6 ,wsl::Glyph(46,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 4 ,yOfs + 6 ,wsl::Glyph(96,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 5 ,yOfs + 6 ,wsl::Glyph(46,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 6 ,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 6 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 24,yOfs + 6 ,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 26,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 30,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 33,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 6 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 6 ,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 6 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 1 ,yOfs + 7 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 2 ,yOfs + 7 ,wsl::Glyph(82,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 3 ,yOfs + 7 ,wsl::Glyph(73,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 4 ,yOfs + 7 ,wsl::Glyph(80,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 5 ,yOfs + 7 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 7 ,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 7 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 7 ,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 7 ,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 7 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 7 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 7 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 7 ,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 24,yOfs + 7 ,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 7 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 26,yOfs + 7 ,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 7 ,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 7 ,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 7 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 30,yOfs + 7 ,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 7 ,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 7 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 33,yOfs + 7 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 7 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 7 ,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 7 ,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 7 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 1 ,yOfs + 8 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 5 ,yOfs + 8 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 8 ,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 8 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 8 ,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 8 ,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 8 ,wsl::Glyph(124,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 8 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 8 ,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 8 ,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 24,yOfs + 8 ,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 8 ,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 26,yOfs + 8 ,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 8 ,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 8 ,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 8 ,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 30,yOfs + 8 ,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 8 ,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 8 ,wsl::Glyph(124,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 33,yOfs + 8 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 8 ,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 8 ,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 8 ,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 8 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 1 ,yOfs + 9 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 5 ,yOfs + 9 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 9 ,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 9 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 9 ,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 9 ,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 9 ,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 9 ,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 9 ,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 9 ,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 24,yOfs + 9 ,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 9 ,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 26,yOfs + 9 ,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 9 ,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 9 ,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 9 ,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 30,yOfs + 9 ,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 9 ,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 9 ,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 33,yOfs + 9 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 9 ,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 9 ,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 9 ,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 9 ,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 1 ,yOfs + 10,wsl::Glyph(126,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 4 ,yOfs + 10,wsl::Glyph(126,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 5 ,yOfs + 10,wsl::Glyph(126,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 10,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 10,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 10,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 10,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 10,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 10,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 24,yOfs + 10,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 10,wsl::Glyph(95,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 26,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 10,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 30,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 10,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 33,yOfs + 10,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 10,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 10,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 10,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 10,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 3 ,yOfs + 11,wsl::Glyph(126,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 11,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 11,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 11,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 11,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 11,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 11,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 11,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 11,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 24,yOfs + 11,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 11,wsl::Glyph(92,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 26,yOfs + 11,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 11,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 11,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 11,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 30,yOfs + 11,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 11,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 11,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 33,yOfs + 11,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 11,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 11,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 11,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 11,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 12,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 12,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 12,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 12,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 12,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 12,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 12,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 12,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 24,yOfs + 12,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 12,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 26,yOfs + 12,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 12,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 12,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 12,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 30,yOfs + 12,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 12,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 12,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 33,yOfs + 12,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 12,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 12,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 12,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 12,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 13,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 13,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 24,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 26,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 30,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 13,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 13,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 33,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 13,wsl::Glyph(32,wsl::Color::LtGrey,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 13,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 14,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 14,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 14,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 15,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 15,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 24,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 26,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 30,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 33,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 15,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 15,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 16,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 16,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 16,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 17,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 17,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 17,yOfs + 17,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 17,wsl::Glyph(80,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 17,wsl::Glyph(101,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 17,wsl::Glyph(114,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 24,yOfs + 17,wsl::Glyph(105,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 17,wsl::Glyph(115,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 26,yOfs + 17,wsl::Glyph(104,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 17,wsl::Glyph(101,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 17,wsl::Glyph(100,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 17,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 17,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 18,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 18,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 18,wsl::Glyph(98,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 18,wsl::Glyph(101,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 18,wsl::Glyph(108,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 18,wsl::Glyph(111,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 18,wsl::Glyph(119,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 24,yOfs + 18,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 18,wsl::Glyph(116,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 26,yOfs + 18,wsl::Glyph(104,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 18,wsl::Glyph(101,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 18,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 18,wsl::Glyph(115,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 30,yOfs + 18,wsl::Glyph(117,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 18,wsl::Glyph(114,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 18,wsl::Glyph(102,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 33,yOfs + 18,wsl::Glyph(97,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 18,wsl::Glyph(99,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 18,wsl::Glyph(101,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 18,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 19,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 19,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 19,wsl::Glyph(111,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 19,wsl::Glyph(110,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 19,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 19,wsl::Glyph(32,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 33,yOfs + 19,wsl::Glyph(119,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 19,wsl::Glyph(105,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 19,wsl::Glyph(116,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 19,wsl::Glyph(104,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 19,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 40,yOfs + 19,wsl::Glyph(39,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 41,yOfs + 19,wsl::Glyph(34,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 42,yOfs + 19,wsl::Glyph(39,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 20,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 20,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 20,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 39,yOfs + 20,wsl::Glyph(34,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 40,yOfs + 20,wsl::Glyph(92,wsl::Color::Orange,wsl::Color::Black));
    console_->put(xOfs + 41,yOfs + 20,wsl::Glyph(124,wsl::Color::Orange,wsl::Color::Black));
    console_->put(xOfs + 42,yOfs + 20,wsl::Glyph(47,wsl::Color::Orange,wsl::Color::Black));
    console_->put(xOfs + 43,yOfs + 20,wsl::Glyph(34,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 21,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 21,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 21,wsl::Glyph(39,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 39,yOfs + 21,wsl::Glyph(45,wsl::Color::Orange,wsl::Color::Black));
    console_->put(xOfs + 40,yOfs + 21,wsl::Glyph(40,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 41,yOfs + 21,wsl::Glyph(58,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 42,yOfs + 21,wsl::Glyph(41,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 43,yOfs + 21,wsl::Glyph(45,wsl::Color::Orange,wsl::Color::Black));
    console_->put(xOfs + 44,yOfs + 21,wsl::Glyph(39,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 22,wsl::Glyph(58,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 22,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 22,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 39,yOfs + 22,wsl::Glyph(34,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 40,yOfs + 22,wsl::Glyph(47,wsl::Color::Orange,wsl::Color::Black));
    console_->put(xOfs + 41,yOfs + 22,wsl::Glyph(124,wsl::Color::Orange,wsl::Color::Black));
    console_->put(xOfs + 42,yOfs + 22,wsl::Glyph(92,wsl::Color::Orange,wsl::Color::Black));
    console_->put(xOfs + 43,yOfs + 22,wsl::Glyph(34,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 23,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 23,wsl::Glyph(124,wsl::Color::DkGrey,wsl::Color::Black));
    console_->put(xOfs + 40,yOfs + 23,wsl::Glyph(39,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 41,yOfs + 23,wsl::Glyph(34,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 42,yOfs + 23,wsl::Glyph(39,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 12,yOfs + 24,wsl::Glyph(126,wsl::Color::Sepia,wsl::Color::Black));
    console_->put(xOfs + 13,yOfs + 24,wsl::Glyph(92,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 24,wsl::Glyph(34,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 24,wsl::Glyph(47,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 24,wsl::Glyph(92,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 41,yOfs + 24,wsl::Glyph(124,wsl::Color::Green,wsl::Color::Black));
    console_->put(xOfs + 44,yOfs + 24,wsl::Glyph(47,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 13,yOfs + 25,wsl::Glyph(124,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 14,yOfs + 25,wsl::Glyph(92,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 25,wsl::Glyph(39,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 25,wsl::Glyph(34,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 17,yOfs + 25,wsl::Glyph(39,wsl::Color::Yellow,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 25,wsl::Glyph(47,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 25,wsl::Glyph(124,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 25,wsl::Glyph(247,wsl::Color::Green,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 25,wsl::Glyph(126,wsl::Color::Sepia,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 25,wsl::Glyph(126,wsl::Color::Sepia,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 25,wsl::Glyph(126,wsl::Color::Sepia,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 25,wsl::Glyph(126,wsl::Color::Sepia,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 25,wsl::Glyph(247,wsl::Color::Green,wsl::Color::Black));
    console_->put(xOfs + 37,yOfs + 25,wsl::Glyph(126,wsl::Color::Sepia,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 25,wsl::Glyph(124,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 39,yOfs + 25,wsl::Glyph(92,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 40,yOfs + 25,wsl::Glyph(126,wsl::Color::Sepia,wsl::Color::Black));
    console_->put(xOfs + 41,yOfs + 25,wsl::Glyph(124,wsl::Color::Green,wsl::Color::Black));
    console_->put(xOfs + 43,yOfs + 25,wsl::Glyph(47,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 44,yOfs + 25,wsl::Glyph(124,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 13,yOfs + 26,wsl::Glyph(47,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 14,yOfs + 26,wsl::Glyph(95,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 26,wsl::Glyph(92,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 26,wsl::Glyph(124,wsl::Color::Green,wsl::Color::Black));
    console_->put(xOfs + 17,yOfs + 26,wsl::Glyph(47,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 26,wsl::Glyph(95,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 26,wsl::Glyph(92,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 26,wsl::Glyph(126,wsl::Color::Sepia,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 26,wsl::Glyph(126,wsl::Color::Sepia,wsl::Color::Black));
    console_->put(xOfs + 24,yOfs + 26,wsl::Glyph(247,wsl::Color::Green,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 26,wsl::Glyph(126,wsl::Color::Sepia,wsl::Color::Black));
    console_->put(xOfs + 26,yOfs + 26,wsl::Glyph(247,wsl::Color::Green,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 26,wsl::Glyph(92,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 26,wsl::Glyph(126,wsl::Color::Sepia,wsl::Color::Black));
    console_->put(xOfs + 30,yOfs + 26,wsl::Glyph(126,wsl::Color::Sepia,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 26,wsl::Glyph(47,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 26,wsl::Glyph(126,wsl::Color::Sepia,wsl::Color::Black));
    console_->put(xOfs + 33,yOfs + 26,wsl::Glyph(247,wsl::Color::Green,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 26,wsl::Glyph(47,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 39,yOfs + 26,wsl::Glyph(95,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 40,yOfs + 26,wsl::Glyph(92,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 41,yOfs + 26,wsl::Glyph(124,wsl::Color::Green,wsl::Color::Black));
    console_->put(xOfs + 42,yOfs + 26,wsl::Glyph(47,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 43,yOfs + 26,wsl::Glyph(95,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 44,yOfs + 26,wsl::Glyph(92,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 27,wsl::Glyph(47,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 27,wsl::Glyph(92,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 27,wsl::Glyph(124,wsl::Color::Green,wsl::Color::Black));
    console_->put(xOfs + 30,yOfs + 27,wsl::Glyph(47,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 27,wsl::Glyph(92,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 39,yOfs + 27,wsl::Glyph(47,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 40,yOfs + 27,wsl::Glyph(95,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 41,yOfs + 27,wsl::Glyph(124,wsl::Color::Green,wsl::Color::Black));
    console_->put(xOfs + 42,yOfs + 27,wsl::Glyph(95,wsl::Color::LtGreen,wsl::Color::Black));
    console_->put(xOfs + 43,yOfs + 27,wsl::Glyph(92,wsl::Color::LtGreen,wsl::Color::Black));
}
