#pragma once
#ifndef RECT_HPP
#define RECT_HPP

#include "vector.hpp"

namespace wsl
{

    // This should be a fancy template class like vector, with all sorts of cool functionality. Will probably update that when I get stuck somewhere
    // and need to take my mind off a problem. If I change this, I'll need to typedef Rect<int> as Rect, Rect<float> as fRect, and Rect<unsigned int> as uRect
    // (None of which is useful yet for Barbarian)
    class Rect
    {
        public:
            Rect(int x = 0, int y = 0, int width = 0, int height = 0) : x1(x), y1(y), x2(x+width), y2(y+height), w(width), h(height) { }

            int x1;
            int x2;
            int y1;
            int y2;
            int w;
            int h;

            wsl::Vector2i center() { return wsl::Vector2i((x1 + x2) / 2, (y1 + y2) / 2); }
            bool intersect(Rect other) { return((x1 <= other.x2) && (x2 >= other.x1) && (y1 <= other.y2) && (y2 >= other.y1)); }
    };


} // Namespace wsl

#endif //RECT_HPP
