#pragma once
#ifndef VECTOR_HPP
#define VECTOR_HPP 

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
