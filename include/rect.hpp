#pragma once
#ifndef RECT_HPP
#define RECT_HPP

namespace wsl
{

    class Rect
    {
        public:
            Rect(int x, int y, int w, int h) : x1(x), y1(y), x2(x+w), y2(y+h) { }

            int x1;
            int x2;
            int y1;
            int y2;
    };


} // Namespace wsl

#endif //RECT_HPP
