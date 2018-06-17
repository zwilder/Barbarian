#pragma once
#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <vector>
#include "color.hpp"

namespace wsl
{
   class Glyph
    {
        // The background is always 219 on the CP437 font (the blank square)
        public:
            Glyph(int symbol, Color color = Color(), Color bg = Color(0,0,0)) : symbol_(symbol), color_(color), bgColor_(bg) { }

            int symbol() { return symbol_; }
            Color color() { return color_; }
            Color bgColor() { return bgColor_; }
            void setColor(Color color) { color_ = color; }
            void setBgColor(Color color) { bgColor_ = color; }

        private:
            int symbol_;
            Color color_;
            Color bgColor_;
    };

    class Console
    {
        public:
            Console(int width = 80, int height = 60);

            int width() { return width_; }
            int height() { return height_; }
            Glyph get(int x, int y);
            void put(int x, int y, Glyph glyph);
            void clear(int x, int y);
            int index(int x, int y) { return (x + (y * width_)); }           
            void flush();
        private:
            int width_;
            int height_;
            std::vector<Glyph> screen_;

    };

} //Namespace wsl

#endif //CONSOLE_HPP
