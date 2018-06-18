#pragma once
#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "color.hpp"
#include "vector.hpp"
#include "rect.hpp"

namespace wsl
{
    class Texture;
    class Sprite
	{
	public:
		Sprite();
		Sprite(SDL_Rect rect, Texture * texture = NULL);
		Sprite(Rect rect, Texture * texture = NULL);
		~Sprite();
	
		void setPos(int x, int y) {pos_.x = x; pos_.y = y;}
		void setPos(Vector2i pos) {pos_ = pos;}
		Vector2i getPos() {return pos_; }

		void setTexPos(SDL_Rect rect) { texturePos_ = rect; }
		void setTexPos(Rect rect);
		Rect getTexPos();
	
		void render(SDL_Renderer * renderer = NULL, int spriteRed = 255, int spriteGreen = 255, int spriteBlue = 255, int spriteAlpha = 255);
		void render(SDL_Renderer * renderer, Color color) { render(renderer, color.r, color.g, color.b, color.a); }

	private:
		Vector2i pos_;
		Texture * texture_;
		SDL_Rect texturePos_;
	};

} // namespace wsl

#endif // SPRITE_HPP
