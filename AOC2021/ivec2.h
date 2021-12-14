#pragma once
#include <ostream>

struct ivec2
{
	union {
		int val[2];
		struct {
			int x;
			int y;
		};
	};

	ivec2() : x(0), y(0)
	{
	}

	ivec2(int ix, int iy)
		: x(ix)
		, y(iy)
	{
	}

	ivec2(ivec2 const& other)
		: x(other.x)
		, y(other.y)
	{
	}

	inline ivec2& operator = (ivec2 const& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	inline ivec2& operator += (ivec2 const& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	inline ivec2& operator -= (ivec2 const& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	inline ivec2& operator *= (int s)
	{
		x *= s;
		y *= s;

		return *this;
	}
};

inline bool operator == (ivec2 const& a, ivec2 const& b)
{
	return a.x == b.x && a.y == b.y;
}

inline bool operator != (ivec2 const& a, ivec2 const& b)
{
	return !(a == b);
}

inline ivec2 operator + (ivec2 const& a, ivec2 const& b)
{
	return ivec2{ a.x + b.x, a.y + b.y };
}

inline ivec2 operator - (ivec2 const& a, ivec2 const& b)
{
	return ivec2{ a.x - b.x, a.y - b.y };
}

inline ivec2 operator * (ivec2 const& a, int s)
{
	return ivec2{ a.x * s, a.y * s };
}

inline ivec2 operator * (int s, ivec2 const& a)
{
	return a * s;
}

inline bool operator < (ivec2 const& a, ivec2 const& b)
{
	return (a.x == b.x) ? (a.y < b.y) : (a.x < b.x);
}

inline std::ostream& operator << (std::ostream& os, ivec2 const& v)
{
	os << '(' << v.x << ',' << v.y << ')';
	return os;
}
