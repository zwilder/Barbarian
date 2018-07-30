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
#include "../include/engine.hpp"

void Engine::draw_title_()
{
    // This function draws this sweet ass title screen I made:

    /*
                                                              O  
                                                              ║  
                                                             /_\ 
                                                            o| |o
                                                             | | 
    ______  ___  ____________  ___  ______ _____  ___   _   _| | 
    | ___ \/ _ \ | ___ \ ___ \/ _ \ | ___ \_   _|/ _ \ | \ | | | 
    | |_/ / /_\ \| |_/ / |_/ / /_\ \| |_/ / | | / /_\ \|  \| | | 
    | ___ \  _  ||    /| ___ \  _  ||    /  | | |  _  || . ` | | 
    | |_/ / | | || |\ \| |_/ / | | || |\ \ _| |_| | | || |\  | | 
    \____/\_| |_/\_| \_\____/\_| |_/\_| \_|\___/\_| |_/\_| \_/:| 
                                                             |;| 
                                                             |;| 
                                                             \_/ 
                                                             `;  
                                                             ,   
                                                              .  
                                                                 
                                                New Game  - a    
                                                                 
                                                Load Game - b    
                                                                 
                                                Quit      - c    
                                                                 
                                                              ,  
                                                             ;   
                                                              ;  

    (c) Zach Wilder 2018, Drawn in REXPaint
    */

    int xOfs = (console_->width() - 60) / 2; // Width of console - length of title graphic, divided by two
    int yOfs = (console_->height() - 27) / 2;

    console_->put(xOfs + 58,yOfs + 0,wsl::Glyph(79,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 58,yOfs + 1,wsl::Glyph(186,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 2,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 58,yOfs + 2,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 59,yOfs + 2,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 56,yOfs + 3,wsl::Glyph(111,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 3,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 59,yOfs + 3,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 60,yOfs + 3,wsl::Glyph(111,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 4,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 59,yOfs + 4,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 0 ,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 1 ,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 2 ,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 3 ,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 4 ,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 5 ,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 8 ,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 9 ,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 10,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 13,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 14,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 17,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 24,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 33,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 37,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 39,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 40,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 41,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 42,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 43,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 46,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 47,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 48,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 52,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 56,yOfs + 5,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 5,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 59,yOfs + 5,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 0 ,yOfs + 6,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 2 ,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 3 ,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 4 ,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 6 ,yOfs + 6,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 7 ,yOfs + 6,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 9 ,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 11,yOfs + 6,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 13,yOfs + 6,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 17,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 6,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 6,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 26,yOfs + 6,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 30,yOfs + 6,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 6,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 6,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 39,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 43,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 44,yOfs + 6,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 45,yOfs + 6,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 47,yOfs + 6,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 49,yOfs + 6,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 51,yOfs + 6,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 53,yOfs + 6,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 55,yOfs + 6,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 6,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 59,yOfs + 6,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 0 ,yOfs + 7,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 2 ,yOfs + 7,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 3 ,yOfs + 7,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 4 ,yOfs + 7,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 6 ,yOfs + 7,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 8 ,yOfs + 7,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 9 ,yOfs + 7,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 10,yOfs + 7,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 12,yOfs + 7,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 13,yOfs + 7,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 7,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 7,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 17,yOfs + 7,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 7,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 7,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 7,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 7,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 7,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 7,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 7,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 7,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 7,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 7,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 7,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 7,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 7,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 7,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 40,yOfs + 7,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 42,yOfs + 7,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 44,yOfs + 7,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 46,yOfs + 7,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 47,yOfs + 7,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 48,yOfs + 7,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 50,yOfs + 7,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 51,yOfs + 7,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 54,yOfs + 7,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 55,yOfs + 7,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 7,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 59,yOfs + 7,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 0 ,yOfs + 8,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 2 ,yOfs + 8,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 3 ,yOfs + 8,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 4 ,yOfs + 8,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 6 ,yOfs + 8,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 9 ,yOfs + 8,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 12,yOfs + 8,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 13,yOfs + 8,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 8,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 8,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 8,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 8,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 8,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 8,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 28,yOfs + 8,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 8,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 8,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 37,yOfs + 8,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 40,yOfs + 8,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 42,yOfs + 8,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 44,yOfs + 8,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 47,yOfs + 8,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 50,yOfs + 8,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 51,yOfs + 8,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 53,yOfs + 8,wsl::Glyph(46,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 55,yOfs + 8,wsl::Glyph(96,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 8,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 59,yOfs + 8,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 0 ,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 2 ,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 3 ,yOfs + 9,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 4 ,yOfs + 9,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 6 ,yOfs + 9,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 8 ,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 10,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 12,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 13,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 16,yOfs + 9,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 9,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 9,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 9,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 9,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 35,yOfs + 9,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 37,yOfs + 9,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 39,yOfs + 9,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 40,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 42,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 43,yOfs + 9,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 44,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 46,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 48,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 50,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 51,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 53,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 54,yOfs + 9,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 59,yOfs + 9,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 0 ,yOfs + 10,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 1 ,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 2 ,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 3 ,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 4 ,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 5 ,yOfs + 10,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 6 ,yOfs + 10,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 7 ,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 8 ,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 10,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 11,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 12,yOfs + 10,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 13,yOfs + 10,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 14,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 15,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 17,yOfs + 10,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 18,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 19,yOfs + 10,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 20,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 21,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 22,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 23,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 24,yOfs + 10,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 25,yOfs + 10,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 26,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 27,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 29,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 30,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 31,yOfs + 10,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 32,yOfs + 10,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 33,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 34,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 36,yOfs + 10,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 37,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 38,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 39,yOfs + 10,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 40,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 41,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 42,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 43,yOfs + 10,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 44,yOfs + 10,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 45,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 46,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 48,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 49,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 50,yOfs + 10,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 51,yOfs + 10,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 52,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 53,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 55,yOfs + 10,wsl::Glyph(92,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 56,yOfs + 10,wsl::Glyph(95,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 10,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 58,yOfs + 10,wsl::Glyph(58,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 59,yOfs + 10,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 11,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 58,yOfs + 11,wsl::Glyph(59,wsl::Color::Black,wsl::Color::Red));
    console_->put(xOfs + 59,yOfs + 11,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 12,wsl::Glyph(124,wsl::Color::Black,wsl::Color::Red));
    console_->put(xOfs + 58,yOfs + 12,wsl::Glyph(59,wsl::Color::Black,wsl::Color::Red));
    console_->put(xOfs + 59,yOfs + 12,wsl::Glyph(124,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 13,wsl::Glyph(92,wsl::Color::Black,wsl::Color::Red));
    console_->put(xOfs + 58,yOfs + 13,wsl::Glyph(95,wsl::Color::Black,wsl::Color::Red));
    console_->put(xOfs + 59,yOfs + 13,wsl::Glyph(47,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 14,wsl::Glyph(96,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 58,yOfs + 14,wsl::Glyph(59,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 15,wsl::Glyph(44,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 58,yOfs + 16,wsl::Glyph(46,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 44,yOfs + 18,wsl::Glyph(78,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 45,yOfs + 18,wsl::Glyph(101,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 46,yOfs + 18,wsl::Glyph(119,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 48,yOfs + 18,wsl::Glyph(71,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 49,yOfs + 18,wsl::Glyph(97,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 50,yOfs + 18,wsl::Glyph(109,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 51,yOfs + 18,wsl::Glyph(101,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 54,yOfs + 18,wsl::Glyph(45,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 56,yOfs + 18,wsl::Glyph(97,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 44,yOfs + 20,wsl::Glyph(76,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 45,yOfs + 20,wsl::Glyph(111,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 46,yOfs + 20,wsl::Glyph(97,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 47,yOfs + 20,wsl::Glyph(100,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 49,yOfs + 20,wsl::Glyph(71,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 50,yOfs + 20,wsl::Glyph(97,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 51,yOfs + 20,wsl::Glyph(109,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 52,yOfs + 20,wsl::Glyph(101,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 54,yOfs + 20,wsl::Glyph(45,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 56,yOfs + 20,wsl::Glyph(98,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 44,yOfs + 22,wsl::Glyph(81,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 45,yOfs + 22,wsl::Glyph(117,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 46,yOfs + 22,wsl::Glyph(105,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 47,yOfs + 22,wsl::Glyph(116,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 54,yOfs + 22,wsl::Glyph(45,wsl::Color::White,wsl::Color::Black));
    console_->put(xOfs + 56,yOfs + 22,wsl::Glyph(99,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 58,yOfs + 24,wsl::Glyph(44,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 25,wsl::Glyph(59,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 58,yOfs + 26,wsl::Glyph(59,wsl::Color::Black,wsl::Color::Red));
    console_->put(xOfs + 56,yOfs + 27,wsl::Glyph(219,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 57,yOfs + 27,wsl::Glyph(219,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 58,yOfs + 27,wsl::Glyph(219,wsl::Color::Red,wsl::Color::Black));
    console_->put(xOfs + 59,yOfs + 27,wsl::Glyph(219,wsl::Color::Red,wsl::Color::Black));
};
