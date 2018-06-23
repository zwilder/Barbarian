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
#ifndef VECTOR_HPP
#define VECTOR_HPP 

#include <algorithm>

namespace wsl
{

	template <typename T>
	class Vector2
	{
	public:
		Vector2();
		Vector2(T x, T y);
		T x;
		T y;

		Vector2<T> operator *(T a) { return Vector2<T>(x * a, y * a); }
		Vector2<T> operator +(T a) { return Vector2<T>(x + a, y + a); }
		Vector2<T> operator -(T a) { return Vector2<T>(x - a, y - a); }
		Vector2<T> operator /(T a) { return Vector2<T>(x / a, y / a); }

		Vector2<T> operator *(Vector2<T> a) { return Vector2<T>(x * a.x, y * a.y); }
		Vector2<T> operator +(Vector2<T> a) { return Vector2<T>(x + a.x, y + a.y); }
		Vector2<T> operator -(Vector2<T> a) { return Vector2<T>(x - a.x, y - a.y); }
		Vector2<T> operator /(Vector2<T> a) { return Vector2<T>(x / a.x, y / a.y); }

        Vector2<T> operator *=(Vector2<T> a) { return Vector2<T>(x *= a.x, y *= a.y); }
        Vector2<T> operator +=(Vector2<T> a) { return Vector2<T>(x += a.x, y += a.y); }
        Vector2<T> operator -=(Vector2<T> a) { return Vector2<T>(x -= a.x, y -= a.y); }
        Vector2<T> operator /=(Vector2<T> a) { return Vector2<T>(x /= a.x, y /= a.y); }

        inline T distanceTo(Vector2<T> a) { return (sqrt(pow(x - a.x,2) + pow(y - a.y,2))); }
	};

	template <typename T>
	Vector2<T>::Vector2()
	{
		x = 0;
		y = 0;
	}

	template <typename T>
	Vector2<T>::Vector2(T x, T y) : x(x), y(y)
	{

	}

	template <typename T>
	inline bool operator ==(const Vector2<T> & a, const Vector2<T> & b)
	{
		return ((a.x == b.x) && (a.y == b.y));
	}

	template <typename T>
	inline bool operator !=(const Vector2<T> & a, const Vector2<T> & b)
	{
		return (!(a == b));
	}

    typedef Vector2<int> Vector2i;
    typedef Vector2<float> Vector2f;
    typedef Vector2<unsigned int> Vector2u;

} // namespace wsl

#endif // VECTOR_HPP
