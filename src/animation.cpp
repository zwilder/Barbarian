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
#include <iostream>
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
    frames.push_back(AnimationFrame());
}

void Animation::update(int dt)
{
    if(check(Flags::DEAD) || frames.size() == 0)
    {
        return;
    }

    if(dt + lastUpdate >= nextUpdate)
    {
        currentFrame += 1;
        if(currentFrame >= (int(frames.size()) - 1))
        {
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
    }
    else
    {
        lastUpdate += dt;
    }
}

void Animation::draw(Engine * engine)
{
    if(frames.size() == 0)
    {
        return;
    }
    AnimationFrame & frame = frames[currentFrame];
    for(size_t i = 0; i < frame.tiles.size(); ++i)
    {
        wsl::Vector2i & pos = frame.tiles[i].pos;
        wsl::Glyph & tile = frame.tiles[i].glyph;
        wsl::Glyph consoleTile = engine->console()->get(pos.x,pos.y);
        wsl::Color fg = frame.check(AnimationFrame::Flags::APPLY_FG) ? tile.color() : consoleTile.color();
        wsl::Color bg = frame.check(AnimationFrame::Flags::APPLY_BG) ? tile.bgColor() : consoleTile.bgColor();
        uint8_t symbol = frame.check(AnimationFrame::Flags::APPLY_GLYPH) ? tile.symbol() : consoleTile.symbol();
        if(fov::contains(engine->visible(), wsl::Vector2i(pos.x,pos.y)) || frame.check(AnimationFrame::Flags::ALL_VIS))
        {
            engine->console()->put(pos.x, pos.y, wsl::Glyph(symbol, fg, bg));
        }
        if(frame.check(AnimationFrame::Flags::LEAVE_TILE))
        {
            if(frame.check(AnimationFrame::Flags::APPLY_FG)) engine->gameMap()->tileAt(pos).glyph().setColor(tile.color());
            if(frame.check(AnimationFrame::Flags::APPLY_BG)) engine->gameMap()->tileAt(pos).glyph().setBgColor(tile.bgColor());
            // if(frame.check(AnimationFrame::Flags::APPLY_GLYPH)) engine->gameMap()->tileAt(pos).glyph().setSym(tile.symbol());
        }
    }
}

namespace Animated
{
Animation explosion(wsl::Vector2i origin, int radius)
{
    uint32_t seed = uint32_t(std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count());
    wsl::RNGState rng(123987445, seed); // Random numbers
    const int ANIMATION_DURATION = 250;
    Animation result;
    int frameDuration = ANIMATION_DURATION / (radius * 2); // Outward explosion/Inward Explosion
    int frameMask = AnimationFrame::Flags::APPLY_FG | AnimationFrame::Flags::APPLY_BG | AnimationFrame::Flags::APPLY_GLYPH;
    //Outward explosion
    for(int i = 1; i <= radius; ++i)
    {
        AnimationFrame frame;
        for(int x = origin.x - i; x <= origin.x + i; ++x)
        {
            for(int y = origin.y - i; y <= origin.y + i; ++y)
            {
                // Without adding in an if sqrt(x^2 + y^2) <= r this just makes a square instead of a circle
                // if(sqrt(pow(x, 2) + pow(y, 2)) <= radius) continue;
                if(sqrt(pow(x - origin.x, 2) + pow(y - origin.y, 2)) > radius) continue;
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
                // int randomGlyph = wsl::randomInt('A','z',&rng);
                // frame.tiles.push_back(AnimationTile(wsl::Glyph(randomGlyph,wsl::Color::White,bg), wsl::Vector2i(x,y)));
                // frame.tiles.push_back(AnimationTile(wsl::Glyph(' ',bg,bg), wsl::Vector2i(x,y)));
                frame.tiles.push_back(AnimationTile(wsl::Glyph('.',wsl::Color::Yellow,bg), wsl::Vector2i(x,y)));
            }
        }
        frame.duration = frameDuration;
        frame.engage(frameMask);
        result.frames.push_back(frame);
    }
    //Inward explosion
    for(int i = radius; i >= 1; --i)
    {
        AnimationFrame frame;
        for(int x = origin.x - i; x <= origin.x + i; ++x)
        {
            for(int y = origin.y - i; y <= origin.y + i; ++y)
            {
                if(sqrt(pow(x - origin.x, 2) + pow(y - origin.y, 2)) > radius) continue;
                if(wsl::randomInt(1,100,&rng) >= 25)
                {
                    continue;
                }
                wsl::Color bg = wsl::Color::Red;
                switch(wsl::randomInt(1,3,&rng))
                {
                    case 1: bg = wsl::Color::Yellow; break;
                    case 2: bg = wsl::Color::Orange; break;
                    case 3: bg = wsl::Color::Red; break;
                    case 4: bg = wsl::Color::LtGrey; break;
                    case 5: bg = wsl::Color::White; break;
                    default: break;
                }
                // int randomGlyph = wsl::randomInt('A','z',&rng);
                // frame.tiles.push_back(AnimationTile(wsl::Glyph(randomGlyph,wsl::Color::White,bg), wsl::Vector2i(x,y)));
                // frame.tiles.push_back(AnimationTile(wsl::Glyph(' ',bg,bg), wsl::Vector2i(x,y)));
                // frame.tiles.push_back(AnimationTile(wsl::Glyph(wsl::randomInt(176,178,&rng),wsl::Color::Yellow,bg), wsl::Vector2i(x,y)));
                frame.tiles.push_back(AnimationTile(wsl::Glyph('.',wsl::Color::Yellow,bg), wsl::Vector2i(x,y)));
            }
        }
        frame.duration = frameDuration;
        frame.engage(frameMask);
        // frame.engage(AnimationFrame::Flags::APPLY_GLYPH);
        // frame.engage(AnimationFrame::Flags::APPLY_FG);
        // frame.engage(AnimationFrame::Flags::APPLY_BG);
        result.frames.push_back(frame);
    }
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
    if(origin == destination)
    {
        return result;
    }
    std::vector<wsl::Vector2i> path;
    path::bhline(origin, destination, &path);
    int frameDuration = ANIMATION_DURATION / int(path.size());
    for(size_t i = 0; i < path.size(); ++i)
    {
        AnimationFrame frame;
        frame.tiles.push_back(AnimationTile(glyph, path[i]));
        frame.duration = frameDuration;
        frame.engage(AnimationFrame::Flags::APPLY_FG | AnimationFrame::Flags::APPLY_GLYPH);
        result.frames.push_back(frame);
    }
    return result;
}

Animation beam(wsl::Vector2i origin, wsl::Vector2i destination, wsl::Color color)
{
    Animation result = projectile('/', origin, destination);
    for(size_t i = 0; i < result.frames.size(); ++i)
    {
        if((i % 2) == 0)
        {
            continue;
        }
        result.frames.at(i).tiles[0].glyph = wsl::Glyph(92,color);
    }
    return result;
}

Animation screenflash(wsl::Vector2i screenDimensions, wsl::Color color)
{
    const int ANIMATION_DURATION = 25;
    Animation result;
    AnimationFrame frame;
    for(int x = 0; x < screenDimensions.x; ++x)
    {
        for(int y = 0; y < screenDimensions.y; ++y)
        {
            frame.tiles.push_back(AnimationTile(wsl::Glyph(177,color,wsl::Color::LtGrey), wsl::Vector2i(x,y)));
        }
    }
    frame.duration = ANIMATION_DURATION;
    frame.engage(AnimationFrame::Flags::ALL_VIS | AnimationFrame::Flags::APPLY_FG | AnimationFrame::Flags::APPLY_BG | AnimationFrame::Flags::APPLY_GLYPH);
    result.frames.push_back(frame);
    // result.engage(Animation::Flags::APPLY_BG | Animation::Flags::APPLY_FG | Animation::Flags::APPLY_GLYPH);
    return result;
}

Animation lightning(wsl::Vector2i origin, wsl::Vector2i destination)
{
    const int ANIMATION_DURATION = 150;
    Animation result = screenflash(wsl::Vector2i(88,42), wsl::Color::DkYellow);
    Animation bolt = beam(origin, destination, wsl::Color::Yellow);
    wsl::Vector2i prev = origin;
    int frameDuration = ANIMATION_DURATION / bolt.frames.size();
    for(size_t i = 1; i < bolt.frames.size(); ++i)
    {
        //light up previous tile 
        bolt.frames.at(i).tiles.push_back(AnimationTile(wsl::Glyph(219,wsl::Color::LtYellow),prev));
        prev = bolt.frames.at(i).tiles[0].pos;
        bolt.frames.at(i).duration = frameDuration;
        result.frames.push_back(bolt.frames.at(i));
    }
    return result;
}

Animation firebolt(wsl::Vector2i origin, wsl::Vector2i destination)
{
    Animation result = projectile(wsl::Glyph(7,wsl::Color::Red),origin,destination);
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
    // Animation fireProj = projectile(wsl::Glyph('*', wsl::Color::Red), origin, destination);
    Animation fireProj = firebolt(origin, destination);
    Animation result = fireProj;
    // std::cout << result.frames.size() << std::endl;
    Animation screenFlash = screenflash(wsl::Vector2i(88,42), wsl::Color::DkYellow);
    for(size_t i = 0; i < screenFlash.frames.size(); ++i)
    {
        result.frames.push_back(screenFlash.frames.at(i));
    }
    // std::cout << result.frames.size() << std::endl;
    Animation fireExpl = explosion(destination, radius);
    for(size_t i = 0; i < fireExpl.frames.size(); ++i)
    {
        result.frames.push_back(fireExpl.frames.at(i));
    }

    AnimationFrame burnFrame = result.frames[result.frames.size() - radius - 1];
    for(size_t i = 0; i < burnFrame.tiles.size(); ++i)
    {
        burnFrame.tiles.at(i).glyph = wsl::Glyph('.',wsl::Color::Black,wsl::Color::DkGrey);
    }
    // AnimationFrame burnFrame;
    // for(int x = destination.x - radius; x <= destination.x + radius; ++x)
    // {
    //     for(int y = destination.y - radius; y <= destination.y + radius; ++y)
    //     {
    //         if(sqrt(pow(x - destination.x, 2) + pow(y - destination.y, 2)) > radius) continue;
    //         burnFrame.tiles.push_back(AnimationTile(wsl::Glyph('.',wsl::Color::Black,wsl::Color::DkGrey),wsl::Vector2i(x,y)));
    //     }
    // }
    burnFrame.duration = 1;
    burnFrame.set(AnimationFrame::Flags::NONE);
    burnFrame.engage(AnimationFrame::Flags::APPLY_FG | AnimationFrame::Flags::LEAVE_TILE);
    burnFrame.engage(AnimationFrame::Flags::APPLY_BG);
    result.frames.push_back(burnFrame);
    return result;
}
} //namepace Animated
