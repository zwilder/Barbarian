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


#pragma once
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "color.hpp"

namespace wsl
{
    class Texture
	{
	public:
		Texture();
		~Texture();
	
		bool loadFromFile(std::string path, SDL_Renderer * renderer = NULL);
		void free();

		void render(int x, int y, SDL_Renderer * renderer, SDL_Rect clip);

		bool lockTexture();
		bool unlockTexture();

		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		void setAlpha(Uint8 alpha);
		void setColor(const Color & color);
	
		Uint32 getPixel32( unsigned int x, unsigned int y );
		void* getPixels() { return pixels_; }

		int pitch() { return pitch_; }
		int width(){ return width_; }
		int height(){ return height_; }
	
	private:
		SDL_Texture * texture_;

		void * pixels_;
		int pitch_;
		int width_;
		int height_;

	};
} //namespace wsl

#endif // texture.hpp
