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
#include <cmath>
#include <chrono>

#include "../include/random.hpp"
#include "../include/animation.hpp"
#include "../include/pathfinding.hpp"
#include "../include/engine.hpp"

// AnimationTile::AnimationTile(wsl::Glyph t, wsl::Vector2i p) : tile(t), pos(p) { }
//
// Frame::Frame(wsl::DLList<AnimationTile> t, int d)
// {
//     tiles = std::make_unique< wsl::DLList<AnimationTile> >(t);
//     duration = d;
// }
//
// Frame::Frame(const Frame & other)
// {
//     // *this = other;
//     tiles = std::make_unique< wsl::DLList<AnimationTile> >();
//     if(&other == NULL)
//     {
//         return;
//     }
//     if(!other.tiles->isEmpty())
//     {
//         *tiles = *other.tiles;
//     }
//     duration = other.duration;
// }

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
        
// Animation::Animation(wsl::DLList<Frame> f)
// {
//     lastUpdate = 0;
//     nextUpdate = 0;
//     frames = std::make_unique< wsl::DLList<Frame> >();
//     if(!f.isEmpty())
//     {
//         nextUpdate = f.head()->data.duration;
//         *frames.get() = f;
//     }
// }

// Animation::Animation(Animation & other)
// {
//     *this = other;
// }

Animation::Animation()
{
    lastUpdate = 0;
    nextUpdate = 0;
    currentFrame = 0;
}

void Animation::update(int dt)
{
    if(check(Flags::DEAD) || frames.size() == 0)
    {
        return;
    }
    if(dt + lastUpdate >= nextUpdate)
    {
    //     frames->popFront();
        currentFrame += 1;
        if(currentFrame >= (int(frames.size()) - 1))
        {
            // check(Flags::LOOP) ? currentFrame = 0 : engage(Flags::DEAD);
            if(check(Flags::LOOP))
            {
                currentFrame = 0;
            }
            else
            {
                engage(Flags::DEAD);
            }
        }
        lastUpdate += dt;
        nextUpdate = lastUpdate + frames.at(currentFrame).duration;
    //     if(frames->isEmpty())
    //     {
    //         engage(Flags::DEAD);
    //     }
    //     else
    //     {
    //         nextUpdate = lastUpdate + frames->head()->data.duration;
    //     }
    }
    else
    {
        lastUpdate += dt;
    }
}

void Animation::draw(Engine * engine)
{
    if(check(Flags::DEAD) || frames.size() == 0)
    {
        return;
    }
    // Frame * currentFrame = &(frames->head()->data);
    // for(wsl::DLNode<AnimationTile> * node = currentFrame->tiles->head(); node != NULL; node = node->next)
    // {
    //     wsl::Vector2i & pos = node->data.pos;
    //     wsl::Glyph tile = node->data.tile;
    //     wsl::Glyph consoleTile = console->get(pos.x,pos.y);
    //     // Draw tile at pos on console, following flags (Apply fg, apply bg, apply glyph)
    //     wsl::Color fg = check(Flags::APPLY_FG) ? tile.color() : consoleTile.color();
    //     wsl::Color bg = check(Flags::APPLY_BG) ? tile.bgColor() : consoleTile.bgColor();
    //     uint8_t symbol = check(Flags::APPLY_GLYPH) ? tile.symbol() : consoleTile.symbol();
    //
    //     console->put(pos.x, pos.y, wsl::Glyph(symbol, fg, bg));
    // }
    AnimationFrame & frame = frames[currentFrame];
    for(size_t i = 0; i < frame.tiles.size(); ++i)
    {
        wsl::Vector2i & pos = frame.tiles[i].pos;
        wsl::Glyph & tile = frame.tiles[i].glyph;
        wsl::Glyph consoleTile = engine->console()->get(pos.x,pos.y);
        wsl::Color fg = check(Flags::APPLY_FG) ? tile.color() : consoleTile.color();
        wsl::Color bg = check(Flags::APPLY_BG) ? tile.bgColor() : consoleTile.bgColor();
        uint8_t symbol = check(Flags::APPLY_GLYPH) ? tile.symbol() : consoleTile.symbol();
        if(fov::contains(engine->visible(), wsl::Vector2i(pos.x,pos.y)))
        {
            engine->console()->put(pos.x, pos.y, wsl::Glyph(symbol, fg, bg));
        }
    }
}

namespace Animated
{
Animation explosion(wsl::Vector2i origin, int radius)
{
    /*
     * 
     */
    uint32_t seed = uint32_t(std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count());
    wsl::RNGState rng(123987445, seed); // Random numbers
    const int ANIMATION_DURATION = 250;
    Animation result;
    int frameDuration = ANIMATION_DURATION / radius;
    for(int i = 1; i <= radius; ++i)
    {
        // 1 frame is one step from radius
        AnimationFrame frame;
        // Each frame get the tiles from origin to radius
        for(int x = origin.x - i; x <= origin.x + i; ++x)
        {
            for(int y = origin.y - i; y <= origin.y + i; ++y)
            {
                // if(sqrt(pow(x, 2) + pow(y, 2)) > 2)
                // {
                    // continue;
                // }
                // Without adding in an if sqrt(x^2 + y^2) <= r this just makes a square instead of a circle
                // Light up tiles randomly (Start at 75%?) - bg Red/Orange/Yellow
                if(wsl::randomInt(1,100,&rng) >= 65)
                {
                    continue;
                }
                wsl::Color bg = wsl::Color::Red;
                switch(wsl::randomInt(1,3,&rng))
                {
                    case 1: bg = wsl::Color::Yellow; break;
                    case 2: bg = wsl::Color::Orange; break;
                    case 3: bg = wsl::Color::Red; break;
                    default: break;
                }
                frame.tiles.push_back(AnimationTile(wsl::Glyph('.',bg,bg), wsl::Vector2i(x,y)));
            }
        }
        frame.duration = frameDuration;
        result.frames.push_back(frame);
    }
    // result.engage(Animation::Flags::APPLY_GLYPH);
    result.engage(Animation::Flags::APPLY_FG);
    result.engage(Animation::Flags::APPLY_BG);
    return result;
}

Animation projectile(wsl::Glyph glyph, wsl::Vector2i origin, wsl::Vector2i destination)
{
    /*
     * A projectile draws a path from start to finish, adds the frames from each step with the glyph and returns the result
     * Applys glyph fg, bg, and symbol
     */
    //Unsure how long animations should take, so starting at 500ms (half a second)
    const int ANIMATION_DURATION = 250;
    Animation result;
    std::vector<wsl::Vector2i> path;
    path::bhline(origin, destination, &path);
    int frameDuration = ANIMATION_DURATION / int(path.size());
    for(size_t i = 0; i < path.size(); ++i)
    {
        AnimationFrame frame;
        frame.tiles.push_back(AnimationTile(glyph, path[i]));
        frame.duration = frameDuration;
        result.frames.push_back(frame);
    }
    result.engage(Animation::Flags::APPLY_FG | Animation::Flags::APPLY_GLYPH);
    return result;
}

Animation firebolt(wsl::Vector2i origin, wsl::Vector2i destination)
{
    Animation result = projectile(wsl::Glyph(9,wsl::Color::Red),origin,destination);
    for(size_t i = 0; i < result.frames.size(); ++i)
    {
        if((i % 2) == 0)
        {
            continue;
        }
        result.frames.at(i).tiles[0].glyph = wsl::Glyph('o',wsl::Color::Orange);
    }
    return result;
}

Animation fireball(int radius, wsl::Vector2i origin, wsl::Vector2i destination)
{
    /*
     * A fireball animation starts off with the frames from a projectile, then adds the frames from explosion and returns the result
     */
    const int ANIMATION_DURATION = 500;
    // Animation fireProj = projectile(wsl::Glyph('*', wsl::Color::Red), origin, destination);
    Animation fireProj = firebolt(origin, destination);
    Animation result = fireProj;
    Animation fireExpl = explosion(destination, radius);
    for(size_t i = 0; i < fireExpl.frames.size(); ++i)
    {
        result.frames.push_back(fireExpl.frames.at(i));
    }
    // int frameDuration = ANIMATION_DURATION / int(result.frames.size());
    // for(size_t i = 0; i < result.frames.size(); ++i)
    // {
    //     result.frames.at(i).duration = frameDuration;
    // }
    result.engage(Animation::Flags::APPLY_BG | Animation::Flags::APPLY_FG | Animation::Flags::APPLY_GLYPH);
    return result;
}
} //namepace Animated
