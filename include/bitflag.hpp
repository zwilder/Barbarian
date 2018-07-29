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
#ifndef BITFLAG_HPP
#define BITFLAG_HPP

namespace wsl
{

class BitFlag
{
    public:
        BitFlag() { mask_ = 0; }
        inline int mask() { return mask_;}
        inline bool check(int flag) { return((mask_ & flag) == flag); } // Checks if a flag is turned on
        inline void toggle(int flag) { mask_ ^= flag; } // Toggles a flag on or off
        inline void remove(int flag) { mask_ &= ~flag; } // Removes a flag (turns it off)
        inline void engage(int flag) { mask_ |= flag; } // Adds a flag (turns it on)
        void set(int mask) { mask_ = mask; } // Sets the mask

        int mask_;
         // mask_ WAS a private variable - but then serialization kinda screwed that. It makes more sense to
         // set it public now. Kept the naming convention (appending the underscore) just to make sure I don't
         // try and access it later on through another class. "BPBD" 
};

} //namespace wsl
#endif // BITFLAG_HPP
