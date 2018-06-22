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
#include "../include/texture.hpp"

namespace wsl
{
Texture::Texture()
{
	texture_ = NULL;
	pixels_ = NULL;
	pitch_ = 0;
	width_ = 0;
	height_ = 0;
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(std::string path, SDL_Renderer * renderer)
{
	free();
	SDL_Texture * newTexture = NULL;
	SDL_Surface * loadedSurface = IMG_Load(path.c_str());

	if (renderer == NULL)
	{
		std::cout << "NULL renderer!\n";
		return false;
	}
	if(loadedSurface == NULL)
	{
		std::cout << "Unable to load \"" << path << "\": " << SDL_GetError() << std::endl;
	}
	else
	{
		SDL_Surface * formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
		if(formattedSurface == NULL)
		{
			std::cout << "Unable to convert loaded surface: " << SDL_GetError() << std::endl;
		}
		else
		{
			newTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if(newTexture == NULL)
			{
				std::cout << "Unable to create blank texture: " << SDL_GetError() << std::endl;
			}
			else
			{
				SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
	
				SDL_LockTexture(newTexture, &formattedSurface->clip_rect, &pixels_, &pitch_);
	
				memcpy(pixels_, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);
	
				width_ = formattedSurface->w;
				height_ = formattedSurface->h;
	
				Uint32 * pixels = (Uint32*) pixels_;
				int pixelCount = (pitch_ / 4) * height_;
	
				//Uint32 colorKey = SDL_MapRGB(formattedSurface->format, 0, 0xFF, 0xFF); // This wont work (I think) to make the background transparent unless the transparent color is exactly (0,255,255)
				Uint32 colorKey = getPixel32(0,0); // This gets the pixel at the very top left and whatever color that is (or isn't) becomes transparent
				Uint32 transparent = SDL_MapRGBA(formattedSurface->format, 0x00, 0xFF, 0xFF, 0x00); 
	
				for(int i = 0; i < pixelCount; ++i)
				{
					if(pixels[i] == colorKey)
					{
						pixels[i] = transparent;
					}
				}
				SDL_UnlockTexture(newTexture);
				pixels_ = NULL;
			}
			SDL_FreeSurface(formattedSurface);
		}
		SDL_FreeSurface(loadedSurface);
	}

	texture_ = newTexture;
	return (texture_ != NULL);
}

void Texture::free()
{
	if(texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
		pixels_ = NULL;
		pitch_ = 0;
		width_ = 0;
		height_ = 0;
	}
}

void Texture::render(int x, int y, SDL_Renderer * renderer, SDL_Rect clip)
{
	SDL_Rect renderQuad;
    renderQuad.x = x;
    renderQuad.y = y;
	renderQuad.w = clip.w;
	renderQuad.h = clip.h;

	if (renderer != NULL)
	{
		SDL_RenderCopy(renderer, texture_, &clip, &renderQuad);	
	}
}

bool Texture::lockTexture()
{
	bool success = true;

	//Texture is already locked
	if( pixels_ != NULL )
	{
		std::cout << "Texture is already locked!\n";
		success = false;
	}
	//Lock texture
	else
	{
		if( SDL_LockTexture( texture_, NULL, &pixels_, &pitch_ ) != 0 )
		{
			std::cout << "Unable to lock texture: " << SDL_GetError() << std::endl;
			success = false;
		}
	}

	return success;
}

bool Texture::unlockTexture()
{
	bool success = true;

	//Texture is not locked
	if( pixels_ == NULL )
	{
		std::cout << "Texture is not locked!\n";
		success = false;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture( texture_ );
		pixels_ = NULL;
		pitch_ = 0;
	}

	return success;
}

Uint32 Texture::getPixel32( unsigned int x, unsigned int y )
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32*)pixels_;

	//Get the pixel requested
	return pixels[ ( y * ( pitch_ / 4 ) ) + x ]; //Divide by four because there is 4 bytes per pixel, and pitch is in bytes
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(texture_, red, green, blue);
}

void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture_, alpha);
}

void Texture::setColor(const Color & color)
{
	SDL_SetTextureColorMod(texture_, color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(texture_, color.a);
}
} // Namespace wsl
