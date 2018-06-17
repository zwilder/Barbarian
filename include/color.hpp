#pragma once
#ifndef COLOR_HPP
#define COLOR_HPP

namespace wsl
{
    class Color
    {
        public:
            Color(int red = 255, int green = 255, int blue = 255, int alpha = 255) : r(red), g(green), b(blue), a(alpha) { }

            int r;
            int g;
            int b;
            int a;
    };
} // namespace wsl

#endif // COLOR_HPP
