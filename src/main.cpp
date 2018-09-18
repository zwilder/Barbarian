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


#include <chrono>
#include <memory>
#include "../include/engine.hpp"

int main(int argc, char * argv [])
{
    using namespace std::chrono;
    const milliseconds MS_PER_FRAME = std::chrono::milliseconds(16); // 16ms = ~60fps, 33ms = ~30fps

    std::unique_ptr<Engine> engine = std::make_unique<Engine>();

    milliseconds previous = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    milliseconds lag = std::chrono::milliseconds(0);
    while(engine->running())
    {
        milliseconds current = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        milliseconds elapsed = current - previous;
        previous = current;
        lag += elapsed;

        engine->handleEvents();
        engine->update(int(elapsed.count()));
        engine->draw();
        while(lag >= MS_PER_FRAME)
        {
            // Move update here, and put draw below to separate Update more frequently than draw
            // Not an issue in a turn based game.
            lag -= MS_PER_FRAME;
        }
    }

    engine->saveGame();
    engine->cleanup();

    return 0;
}
