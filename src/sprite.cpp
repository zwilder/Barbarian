/*
* Barbarian!
* Copyright (C) 2018
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
#include "../include/texture.hpp"
#include "../include/sprite.hpp"

namespace wsl
{
Sprite::Sprite()
{
	pos_.x = 0;
	pos_.y = 0;
	texture_ = NULL;
}

Sprite::Sprite(SDL_Rect rect, Texture * texture) : texture_(texture)
{
	texturePos_ = rect;
	pos_.x = 0;
	pos_.y = 0;
}

Sprite::Sprite(Rect rect, Texture * texture) : texture_(texture)
{
	texturePos_.x = rect.x1;
	texturePos_.y = rect.y1;
	texturePos_.w = rect.w;
	texturePos_.h = rect.h;

	pos_.x = 0;
	pos_.y = 0;
}

Sprite::~Sprite()
{
	texture_ = NULL;
}

void Sprite::setTexPos(Rect rect)
{
	texturePos_.x = rect.x1;
	texturePos_.y = rect.y1;
	texturePos_.w = rect.w;
	texturePos_.h = rect.h;	
}

Rect Sprite::getTexPos()
{
    return Rect(texturePos_.x, texturePos_.y, texturePos_.w, texturePos_.h);
}

void Sprite::render(SDL_Renderer * renderer, int spriteRed, int spriteGreen, int spriteBlue, int spriteAlpha)
{
	texture_->setColor(spriteRed, spriteGreen, spriteBlue);
	texture_->setAlpha(spriteAlpha);
	texture_->render(pos_.x, pos_.y, renderer, texturePos_);
}
} //namespace wsl
