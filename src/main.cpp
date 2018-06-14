#include <iostream>
#include "../include/engine.hpp"

int main(int argc, char * argv [])
{
    Engine * engine = new Engine();
    while(engine->running())
    {
        engine->handleEvents();
        engine->update();
        engine->draw();
    }
    engine->cleanup();

    return 0;
}
