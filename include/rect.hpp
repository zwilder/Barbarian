#pragma once
#ifndef RECT_HPP
#define RECT_HPP

#include "vector.hpp"

namespace wsl
{

    class Rect
    {
        public:
            Rect(int x = 0, int y = 0, int w = 0, int h = 0) : x1(x), y1(y), x2(x+w), y2(y+h) { }

            int x1;
            int x2;
            int y1;
            int y2;

            wsl::Vector2i center() { return wsl::Vector2i((x1 + x2) / 2, (y1 + y2) / 2); }
            bool intersect(Rect other) { return((x1 <= other.x2) && (x2 >= other.x1) && (y1 <= other.y2) && (y2 >= other.y1)); }
    };


} // Namespace wsl

#endif //RECT_HPP
