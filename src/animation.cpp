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
#include "../include/pathfinding.hpp"
#include "../include/console.hpp"

AnimationTile::AnimationTile(wsl::Glyph t, wsl::Vector2i p) : tile(t), pos(p) { }

Frame::Frame(wsl::DLList<AnimationTile> t, int d) : tiles(t), duration(d)
{

}

// Frame::Frame(Frame & other)
// {
//     // for(wsl::DLNode<AnimationTile> * node = other.tiles.head(); node != NULL; node = node->next)
//     // {
//     //     tiles.push(node->data);
//     // }
//     if(!other.tiles.isEmpty())
//     {
//         tiles = other.tiles;
//     }
//     duration = other.duration;
// }
//
// Frame::~Frame()
// {
//
// }
        
Animation::Animation(wsl::DLList<Frame> f) : frames(f)
{
    lastUpdate = 0;
    nextUpdate = 0;
    if(!f.isEmpty())
    {
        nextUpdate = f.head()->data.duration;
    }
}

void Animation::update(int dt)
{
    if(check(Flags::DEAD))
    {
        return;
    }
    if(dt + lastUpdate >= nextUpdate)
    {
        frames.popFront();
        lastUpdate += dt;
        if(frames.isEmpty())
        {
            engage(Flags::DEAD);
        }
        else
        {
            nextUpdate = lastUpdate + frames.head()->data.duration;
        }
    }
    else
    {
        lastUpdate += dt;
    }
}

void Animation::draw(wsl::Console * console)
{
    Frame * currentFrame = &frames.head()->data;
    for(wsl::DLNode<AnimationTile> * node = currentFrame->tiles.head(); node != NULL; node = node->next)
    {
        wsl::Vector2i & pos = node->data.pos;
        wsl::Glyph tile = node->data.tile;
        wsl::Glyph consoleTile = console->get(pos.x,pos.y);
        // Draw tile at pos on console, following flags (Apply fg, apply bg, apply glyph)
        wsl::Color fg = check(Flags::APPLY_FG) ? tile.color() : consoleTile.color();
        wsl::Color bg = check(Flags::APPLY_BG) ? tile.bgColor() : consoleTile.bgColor();
        uint8_t symbol = check(Flags::APPLY_GLYPH) ? tile.symbol() : consoleTile.symbol();

        console->put(pos.x, pos.y, wsl::Glyph(symbol, fg, bg));
    }
}

namespace Animated
{
// Animation explosion(wsl::Vector2i origin, int radius)
// {
    /*
     * 
     */
// }

Animation projectile(wsl::Glyph glyph, wsl::Vector2i origin, wsl::Vector2i destination)
{
    /*
     * A projectile draws a path from start to finish, adds the frames from each step with the glyph and returns the result
     * Applys glyph fg, bg, and symbol
     */
    //Unsure how long animations should take, so starting at 500ms (half a second)
    // const int ANIMATION_DURATION = 500;
    // std::vector<wsl::Vector2i> path;
    // path::bhline(origin, destination, &path);
    // int frameDuration = ANIMATION_DURATION / int(path.size());
    wsl::DLList<Frame> frames;
    // for(size_t i = 0; i < path.size(); ++i)
    // {
    //     // AnimationTile atile(glyph, path[i]);
    //     wsl::DLList<AnimationTile> tiles;
    //     tiles.push(AnimationTile(glyph, path[i]));
    //     Frame frame(tiles, frameDuration);
    //     frames.push(frame);
    // }
    Animation result(frames);
    // Animation result;
    // result.frames = frames;
    // result.engage(Animation::Flags::APPLY_FG | Animation::Flags::APPLY_BG | Animation::Flags::APPLY_GLYPH);
    return result;
}

// Animation fireball(wsl::Vector2i origin, wsl::Vector2i destination)
// {
    /*
     * A fireball animation starts off with the frames from a projectile, then adds the frames from explosion and returns the result
     */
// }
} //namepace Animated
