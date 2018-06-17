#include "../include/texture.hpp"
#include "../include/sprite.hpp"

namespace wsl
{
Sprite::Sprite()
{
	texturePos_ = NULL;
	pos_.x = 0;
	pos_.y = 0;
	texture_ = NULL;
}

Sprite::Sprite(SDL_Rect & rect, Texture * texture) : texture_(texture)
{
	texturePos_ = new SDL_Rect;
	*texturePos_ = rect;
	pos_.x = 0;
	pos_.y = 0;
}

Sprite::Sprite(Rect & rect, Texture * texture) : texture_(texture)
{
	texturePos_ = new SDL_Rect;
	(*texturePos_).x = rect.x1;
	(*texturePos_).y = rect.y1;
	(*texturePos_).w = rect.w;
	(*texturePos_).h = rect.h;

	pos_.x = 0;
	pos_.y = 0;
}

Sprite::~Sprite()
{
	texture_ = NULL;
	texturePos_ = NULL;
	delete texture_;
	delete texturePos_;
}

void Sprite::setTexPos(Rect & rect)
{
	(*texturePos_).x = rect.x1;
	(*texturePos_).y = rect.y1;
	(*texturePos_).w = rect.w;
	(*texturePos_).h = rect.h;	
}

Rect Sprite::getTexPos()
{
	Rect rect;
	rect.x1 = (*texturePos_).x;
	rect.y1 = (*texturePos_).y;
	rect.w = (*texturePos_).w;
	rect.h = (*texturePos_).h;

	return rect;
}

void Sprite::render(SDL_Renderer * renderer, int spriteRed, int spriteGreen, int spriteBlue, int spriteAlpha)
{
	texture_->setColor(spriteRed, spriteGreen, spriteBlue);
	texture_->setAlpha(spriteAlpha);
	texture_->render(pos_.x, pos_.y, renderer, texturePos_);
}


} //namespace wsl
