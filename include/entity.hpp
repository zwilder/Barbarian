#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "console.hpp"

class Entity
{
    public:
        Entity(sf::Vector2i pos = sf::Vector2i(0,0), wsl::Glyph glyph = wsl::Glyph(' ')) : pos_(pos), glyph_(glyph) { } 
        
        void move(sf::Vector2i delta) { pos_ += delta; }
        sf::Vector2i pos() { return pos_; }
        wsl::Glyph glyph() { return glyph_; }

    private:
        sf::Vector2i pos_; // x, y
        wsl::Glyph glyph_; // Color, symbol

};

#endif //ENTITY_HPP
