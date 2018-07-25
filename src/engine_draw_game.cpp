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
#include "../include/engine.hpp"

void Engine::draw_game_()
{
    for(int x = 0; x < console_->width(); ++x)
    {
        for(int y = 0; y < console_->height(); ++y)
        {
            int index = console_->index(x,y);
            wsl::Glyph glyph = gameMap_->tiles[index].glyph();
            if(fov::contains(visible_.get(), wsl::Vector2i(x,y)))
            { 
                console_->put(x,y,glyph);
                gameMap_->tiles[index].engage(Tile::Flags::EXPLORED);
            }
            else if(gameMap_->tiles[index].explored())
            {
                if(glyph.symbol() != '#')
                {
                    glyph.setColor(wsl::Color::Black);
                }
                else
                {
                    glyph.setColor(wsl::Color::DkGrey);
                }
                glyph.setBgColor(wsl::Color::Black);
                console_->put(x,y,glyph);
            }
        }
    }

    // Loop through entities here, rendering items if they've been seen (explored)

    // Loop through entities again, rendering entities IF they are in the visible_ coordinates.
    for(wsl::DLNode<Entity> * temp = entityList_.head(); temp != NULL; temp = temp->next)
    {
        Entity & entity = temp->data;
        wsl::Vector2i entityPos = entity.pos();
        wsl::Glyph entityGlyph = entity.glyph();
        if(fov::contains(visible_.get(), entityPos))
        {
            console_->put(entityPos.x,entityPos.y,entityGlyph);
        }
    }

    console_->put(player_->pos().x, player_->pos().y, player_->glyph());

    // UI
    console_->print(0,0, currentMsg_);
    console_->print(0,console_->height() - 2, player_->name());
    console_->print(0,console_->height() - 1, "HP: " + std::to_string(player_->hp()) + "(" + std::to_string(player_->maxHP()) + ")");
}
