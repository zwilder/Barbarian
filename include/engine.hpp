#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include "console.hpp"
#include "input_handlers.hpp"
#include "entity.hpp"
#include "game_map.hpp"

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
        wsl::Console * console_;
        sf::RenderWindow * window_;
        sf::Texture * spritesheet_;
        sf::Sprite spriteChars_[256];
        GameMap * gameMap_;

        void handleKeys_(int key);
        
        // Temporary variables
        Entity player_;
        int pX_;
        int pY_;

};

#endif //ENGINE_HPP
