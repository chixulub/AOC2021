#pragma once
#include <ostream>

template<typename T>
struct tvec3
{
	union {
		T val[3];
		struct {
			T x;
			T y;
			T z;
		};
	};

	tvec3() : x(0), y(0), z(0)
	{
	}

	tvec3(T ix, T iy, T iz)
		: x(ix)
		, y(iy)
		, z(iz)
	{
	}

	tvec3(tvec3 const& other)
		: x(other.x)
		, y(other.y)
		, z(other.z)
	{
	}

	inline tvec3& operator = (tvec3 const& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	inline tvec3 operator - ()
	{
		return tvec3{ -x,-y,-z };
	}

	inline tvec3& operator += (tvec3 const& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	inline tvec3& operator -= (tvec3 const& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	inline tvec3& operator *= (T s)
	{
		x *= s;
		y *= s;
		z *= s;

		return *this;
	}

	inline tvec3& operator /= (T s)
	{
		x /= s;
		y /= s;
		z /= s;

		return *this;
	}
};

template<typename T>
inline bool operator == (tvec3<T> const& a, tvec3<T> const& b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

template<typename T>
inline bool operator != (tvec3<T>  const& a, tvec3<T>  const& b)
{
	return !(a == b);
}

template<typename T>
inline tvec3<T>  operator + (tvec3<T>  const& a, tvec3<T>  const& b)
{
	return tvec3<T>{ a.x + b.x, a.y + b.y, a.z + b.z };
}

template<typename T>
inline tvec3<T>  operator - (tvec3<T> const& a, tvec3<T> const& b)
{
	return tvec3<T>{ a.x - b.x, a.y - b.y, a.z - b.z };
}

template<typename T>
inline tvec3<T> operator * (tvec3<T> const& a, T s)
{
	return tvec3<T>{ a.x* s, a.y* s, a.z* s };
}

template<typename T>
inline tvec3<T> operator * (T s, tvec3<T> const& a)
{
	return a * s;
}

template<typename T>
inline tvec3<T> operator / (tvec3<T> const& a, T s)
{
	return tvec3<T>{ a.x / s, a.y / s, a.z / s };
}

template<typename T>
inline tvec3<T> operator / (T s, tvec3<T> const& a)
{
	return a / s;
}

template<typename T>
inline std::ostream& operator << (std::ostream& os, tvec3<T> const& v)
{
	os << '(' << v.x << ',' << v.y << ',' << v.z << ')';
	return os;
}
