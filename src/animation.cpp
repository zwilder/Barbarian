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

#include "../include/animation.hpp"
#include "../include/engine.hpp"

Animation::Animation(wsl::DLList<Frame> f) : frames(f)
{
    lastUpdate = 0;
    nextUpdate = 0;
    if(!frames.empty())
    {
        nextUpdate = frames.head()->duration;
    }
}

void Animation::update(int dt)
{
    /*
     * Check if dt + lastUpdate >= nextUpdate
     *  - frames.pop()
     *  - lastUpdate += dt;
     *  - nextUpdate = lastUpdate + frames.head()->data.duration;
     * Else:
     *  -lastUpdate += dt
     */
}

void Animation::draw(Engine * engine)
{
    Frame * currentFrame = &frames.head()->data;
    for(DLNode<AnimationTile> * node = currentFrame->tiles.head(); node != null; node = node->next)
    {
        wsl::Vector2i & pos = node->data->pos;
        Tile & tile = node->data->tile;
        // Draw tile at pos on console, following flags (Apply fg, apply bg, apply glyph)
    }
}
