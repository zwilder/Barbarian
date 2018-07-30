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
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <string>
#include <array>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cereal/types/memory.hpp>

#include "console.hpp"
#include "input_handlers.hpp"
#include "entity.hpp"
#include "game_map.hpp"
#include "fov.hpp"
#include "texture.hpp"
#include "sprite.hpp"
#include "dllist.hpp"

enum class GameState : uint8_t
{
    TITLE,
    PLAYERS_TURN,
    ENEMY_TURN,
    GAME_OVER,
    MSG_WAIT,
    INVENTORY,
    EQUIP,
    DROP,
    TARGET,
    LOOK
};

class Engine
{
    public:
        Engine();

        // Engine main functions - the main loop is handleEvents() -> update() -> draw()
        bool init();
        void cleanup();
        void handleEvents();
        void update();
        void draw();

        // Variable access functions
        bool running() { return running_; }
        int windowWidth() { return windowWidth_; }
        int windowHeight() { return windowHeight_; }
        GameMap * gameMap() { return gameMap_.get(); }
        wsl::DLList<Entity> * entityList() { return &entityList_; }
        Entity * player() { return player_; }
        std::vector<wsl::Vector2i> * visible() { return visible_.get(); }
        wsl::Vector2i cursor();
        bool targetSelected() { return targetSelected_; }

        // Utility functions
        void newGame();
        bool loadGame();
        void saveGame();
        void changeState(GameState newState); // Changes game state
        void revertState(); // Reverts to previous state
        void addMessage(std::string msg);
        void target(bool look = false); // target() is a miniature main loop, calls handleEvents() and draw()
        void look() { target(true); } // look() is just target, but with a different GameState

    private:
        // handleEvents() and draw() were huge functions - so I split them into separate implementation files
        void handleEvents_player_(Input input); // engine_events_player.cpp
        void handleEvents_inventory_(Input input); // engine_events_inventory.cpp
        void handleEvents_target_(Input input); // engine_events_target.cpp
        void handleEvents_look_(Input input); // engine_events_target.cpp
        void handleEvents_title_(Input input);
        void draw_title_(); // engine_draw_title.cpp
        void draw_inventory_(); // engine_draw_inventory.cpp
        void draw_game_(); // engine_draw_game.cpp
        void draw_target_(); // engine_draw_target.cpp

        // Engine utility functions/variables
        void advanceMsg_();
        bool running_;

        // Console/Graphics
        wsl::Vector2i spriteSize_;
        int consoleWidth_;
        int consoleHeight_;
        int windowWidth_;
        int windowHeight_;
        std::string windowTitle_;
        bool fullscreen_;

        std::unique_ptr<wsl::Console> console_;
        
        SDL_Window * window_;
        SDL_Renderer * renderer_;
        wsl::Texture * spriteSheet_;

        std::array<wsl::Rect, 256> spriteRects_;
        int spriteIndex_(int x, int y) { return (x + (y*consoleWidth_)); }

        // Game Map
        std::unique_ptr<GameMap> gameMap_;
        int maxRoomSize_; // Do these three variables need to be stored?
        int minRoomSize_;
        int maxRooms_;
        
        // FoV
        std::unique_ptr< std::vector<wsl::Vector2i> > visible_; 

        // Entities
        int ACTION_COST;
        Entity * player_;
        wsl::DLList<Entity> entityList_;
        wsl::DLList<Entity *> schedule_;
        Entity * curActor_;

        // Game state
        GameState gameState_;
        GameState prevGameState_;

        // GUI
        wsl::DLList<std::string> msgList_;
        std::string currentMsg_;

        // Targeting
        bool targetSelected_;
        bool targeting_;
        wsl::Vector2i cursorPos_;
};

#endif // ENGINE_HPP
