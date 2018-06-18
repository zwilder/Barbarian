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
