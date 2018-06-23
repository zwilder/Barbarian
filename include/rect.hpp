/*
* Barbarian!
* Copyright (C) Zach Wilder 2018
* 
* This file is a part of Barbarian!
*
* Barbarian! is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Barbarian! is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Barbarian!.  If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once
#ifndef RECT_HPP
#define RECT_HPP

#include "vector.hpp"

namespace wsl
{

    template <typename T>
    class Rectangle
    {
        public:
            Rectangle();
            Rectangle(T x, T y, T width, T height);

            T x1;
            T x2;
            T y1;
            T y2;
            T w;
            T h;

            inline wsl::Vector2<T> center() { return wsl::Vector2<T>((x1 + x2) / 2, (y1 + y2) / 2); }
            inline bool intersect(Rectangle<T> other) { return((x1 <= other.x2) && (x2 >= other.x1) && (y1 <= other.y2) && (y2 >= other.y1)); }
    };

    template <typename T>
    Rectangle<T>::Rectangle()
    {
        x1 = 0;
        x2 = 0;
        y1 = 0;
        y2 = 0;
        w = 0;
        h = 0;
    }

    template <typename T>
    Rectangle<T>::Rectangle(T x, T y, T width, T height) : x1(x), y1(y), x2(x+width), y2(y+height), w(width), h(height)
    {
        //
    }

    template <typename T>
	inline bool operator ==(const Rectangle<T> & a, const Rectangle<T> & b)
	{
		return ((a.x1 == b.x1) && (a.y1 == b.y1) && (a.w == b.w) && (a.h == b.h));
	}

	template <typename T>
	inline bool operator !=(const Rectangle<T> & a, const Rectangle<T> & b)
	{
		return (!(a == b));
	}

    typedef Rectangle<int> Rect; // Rectangle defaults to this because when I wrote the original class all the files use it as "Rect" with ints.
    typedef Rectangle<float> fRect;
    typedef Rectangle<unsigned int> uRect; // I should have followed what I did with vector by making this Rectu, but then I would mentally call it Rectum and giggle.


} // Namespace wsl

#endif //RECT_HPP
