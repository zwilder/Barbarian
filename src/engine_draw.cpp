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
#include <iterator>
#include <sstream>
#include "../include/engine.hpp"

void Engine::draw()
{
    // Render order, GameMap (Tiles) >> Stairs >> Items >> Entities.
    // Translate GameMap to virtual console (right now this is the 'root' console)
    console_->flush();

    // Render tiles first, this loops through the entirety of the console_ width/height, since Tiles remain visible after being explored.
    if(gameState_ == GameState::TITLE)
    {
        draw_title_();
    }
    else if(gameState_ == GameState::ENEMY_TURN || gameState_ == GameState::PLAYERS_TURN || gameState_ == GameState::GAME_OVER)
    {
        draw_game_();
    }
    else if(gameState_ == GameState::INVENTORY || gameState_ == GameState::DROP || gameState_ == GameState::EQUIP)
    {
        draw_inventory_();
    }
    else if(gameState_ == GameState::TARGET || gameState_ == GameState::LOOK)
    {
        draw_target_();
    }
    else if(gameState_ == GameState::LEVEL_UP)
    {
        draw_levelup_();
    }
    else if(gameState_ == GameState::RIP)
    {
        draw_RIP_();
    }

    // Render animations
    for(wsl::DLNode<Animation> * node = animations_->head(); node != NULL; node = node->next)
    {
        node->data.draw(console_.get());
    }

    // Clear the SDL window
    SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer_);

    // Create sprites from the template sprites in spriteChars_ to represent the characters on the virtual console, and draw them to the screen
    wsl::Sprite cursorSprite = wsl::Sprite(wsl::Rect(0,0,spriteSize_.x,spriteSize_.y),spriteSheet_); 
    wsl::Sprite bgCursorSprite = wsl::Sprite(wsl::Rect(0,0,spriteSize_.x,spriteSize_.y),spriteSheet_);
    int xOfs = (windowWidth_ - (console_->width() * spriteSize_.x)) / 2; // Centers the console on the window
    int yOfs = (windowHeight_ - (console_->height() * spriteSize_.y)) / 2;
    for(int x = 0; x < console_->width(); ++x)
    {
        for(int y = 0; y < console_->height(); ++y)
        {
            wsl::Color bgColor = console_->get(x,y).bgColor();
            if(bgColor != wsl::Color::Black)
            {
                bgCursorSprite.setTexPos(spriteRects_[219]); // 219 is the white square in the CP437 font
                bgCursorSprite.setPos((x * spriteSize_.x) + xOfs, (y * spriteSize_.y) + yOfs);
            
                bgCursorSprite.render(renderer_, bgColor);
            }
            wsl::Rect & textureRect = spriteRects_[console_->get(x,y).symbol()];
            cursorSprite.setPos((x * spriteSize_.x) + xOfs, (y * spriteSize_.y) + yOfs);
            cursorSprite.setTexPos(wsl::Rect(textureRect.x1, textureRect.y1, textureRect.w, textureRect.h));
            wsl::Color color = console_->get(x,y).color();

            cursorSprite.render(renderer_, color);
        }
    }
    
    // Display the SDL window
    SDL_RenderPresent(renderer_);
}

void Engine::draw_entities_()
{
    // Loop through entities here, rendering items if they've been seen (explored)
    // Since this is the first loop through entitylist, other entities are identified here and then pushed
    // into their respective lists for the proper render order
    wsl::DLList<Entity *> actorList;
    for(wsl::DLNode<Entity> * temp = entityList_.head(); temp != NULL; temp = temp->next)
    {
        if(temp->data.isItem())
        {
            Entity & entity = temp->data;
            wsl::Vector2i entityPos = entity.pos();
            wsl::Glyph entityGlyph = entity.glyph();
            if(gameMap_->tileAt(entityPos).explored() && !entity.carried())
            {
                console_->put(entityPos.x, entityPos.y, entityGlyph);
            }
        }
        else if(temp->data.isActor())
        {
            actorList.push(&temp->data);
        }
    }
    // Loop through entities again, rendering actor entities IF they are in the visible_ coordinates.
    for(wsl::DLNode<Entity *> * temp = actorList.head(); temp != NULL; temp = temp->next)
    {
        Entity * entity = temp->data;
        wsl::Vector2i entityPos = entity->pos();
        wsl::Glyph entityGlyph = entity->glyph();
        if(fov::contains(visible_.get(), entityPos))
        // if(gameMap_->tileAt(entityPos).visible())
        {
            console_->put(entityPos.x,entityPos.y,entityGlyph);
        }
    }

    console_->put(player_->pos().x, player_->pos().y, player_->glyph());
}
