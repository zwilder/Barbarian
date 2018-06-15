#pragma once
#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <vector>

namespace wsl
{
    class Color
    {
        public:
            Color(int r = 255, int g = 255, int b = 255) : r_(r), g_(g), b_(b) { }

            int r() { return r_; }
            int g() { return g_; }
            int b() { return b_; }
            void set(int r = 255, int g = 255, int b = 255) { r_ = r; g_ = g; b_ = b; }

        private:
            int r_;
            int g_;
            int b_;
    };

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
