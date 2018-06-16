#pragma once
#ifndef INPUT_HANDLERS_HPP
#define INPUT_HANDLERS_HPP

#include <SFML/Graphics.hpp>

// Bit flags are overkill and possibly not the best way to do this... 
enum Cmd : int
{
    NONE = 0,
    MOVE = 0x02,
    QUIT = 0x04,
    FULLSCREEN = 0x04,
    NEXT_LEVEL = 0x08
};
        

class Action
{
    public:
        Action(int cmd = Cmd::NONE);
        Action(int cmd, sf::Vector2i delta);

        bool move() { return((cmdMask_ & Cmd::MOVE) == Cmd::MOVE); }
        bool quit() { return((cmdMask_ & Cmd::QUIT) == Cmd::QUIT); }
        bool fullscreen() { return((cmdMask_ & Cmd::FULLSCREEN) == Cmd::FULLSCREEN); }
        bool nextLevel() { return((cmdMask_ & Cmd::NEXT_LEVEL) == Cmd::NEXT_LEVEL); }

        sf::Vector2i dir() { return dir_; }
    private:
        int cmdMask_;
        sf::Vector2i dir_; 
 };

Action handleKeys(int key);

#endif //INPUT_HANDLERS_HPP
