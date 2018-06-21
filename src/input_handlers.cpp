// #include <SFML/Window.hpp>
#include <SDL2/SDL.h>
#include "../include/input_handlers.hpp"

Action::Action(int cmd) : cmdMask_(cmd)
{
   //
}

Action::Action(int cmd, wsl::Vector2i delta) : cmdMask_(cmd), dir_(delta)
{
    //
}

Action handleKeys(int key)
{
    switch(key)
    {
        case SDLK_DOWN:
        case SDLK_KP_2:
        {
            return Action(Cmd::MOVE, wsl::Vector2i(0,1)); 
        }
        case SDLK_LEFT:
        case SDLK_KP_4:
        {
            return Action(Cmd::MOVE, wsl::Vector2i(-1,0));
        }
        case SDLK_UP:
        case SDLK_KP_8:
        {
            return Action(Cmd::MOVE, wsl::Vector2i(0,-1));
        }
        case SDLK_RIGHT:
        case SDLK_KP_6:
        {
            return Action(Cmd::MOVE, wsl::Vector2i(1,0));
        }
        case SDLK_KP_7:
        {
            return Action(Cmd::MOVE, wsl::Vector2i(-1,-1));
        }
        case SDLK_KP_9:
        {
            return Action(Cmd::MOVE, wsl::Vector2i(1,-1));
        }
        case SDLK_KP_3:
        {
            return Action(Cmd::MOVE, wsl::Vector2i(1,1));
        }
        case SDLK_KP_1:
        {
            return Action(Cmd::MOVE, wsl::Vector2i(-1,1));
        }
        case SDLK_q:
        case SDLK_ESCAPE:
        {
            return Action(Cmd::QUIT);
        }
        case SDLK_RETURN:
        case SDLK_KP_ENTER:
        {
            return Action(Cmd::NEXT_LEVEL);
        }
        default: { break; }
    }

    return Action(Cmd::NONE);
}
