#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <string>
#include <array>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "console.hpp"
#include "input_handlers.hpp"
#include "entity.hpp"
#include "game_map.hpp"
#include "texture.hpp"
#include "sprite.hpp"

class Engine
{
    public:
        Engine();

        bool running() { return running_; }
        bool init();
        void cleanup();
        void handleEvents();
        void update();
        void draw();

        int windowWidth() { return windowWidth_; }
        int windowHeight() { return windowHeight_; }

    private:
        bool running_;
        int spriteSize_;
        int consoleWidth_;
        int consoleHeight_;
        int windowWidth_;
        int windowHeight_;
        std::string windowTitle_;

        wsl::Console * console_;
        
        SDL_Window * window_;
        SDL_Renderer * renderer_;
        wsl::Texture * spriteSheet_;

        std::array<wsl::Rect, 256> spriteRects_;
        // std::vector< std::unique_ptr<wsl::Sprite> > consoleSprites_;
        int spriteIndex_(int x, int y) { return (x + (y*consoleWidth_)); }

        GameMap * gameMap_;
        int maxRoomSize_; // Do these three variables need to be stored?
        int minRoomSize_;
        int maxRooms_;

        void handleKeys_(int key);
        
        // Temporary variables
        Entity player_;

};

#endif //ENGINE_HPP
