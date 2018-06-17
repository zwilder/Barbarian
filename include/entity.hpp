#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "vector.hpp"
#include "console.hpp"

class Entity
{
    public:
        Entity(wsl::Vector2i pos = wsl::Vector2i(0,0), wsl::Glyph glyph = wsl::Glyph(' ')) : pos_(pos), glyph_(glyph) { } 
        
        void move(wsl::Vector2i delta) { pos_ += delta; }
        wsl::Vector2i pos() { return pos_; }
        void setPos(wsl::Vector2i pos) { pos_ = pos; }
        wsl::Glyph glyph() { return glyph_; }

    private:
        wsl::Vector2i pos_; // x, y
        wsl::Glyph glyph_; // Color, symbol

};

#endif //ENTITY_HPP
