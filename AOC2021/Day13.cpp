#define _CRT_SECURE_NO_WARNINGS
#include "Common.h"

using namespace std;

static auto stoi_transform = [](string const& s) { return stoi(s); };

/*

fold along x=655
fold along y=447
fold along x=327
fold along y=223
fold along x=163
fold along y=111
fold along x=81
fold along y=55
fold along x=40
fold along y=27
fold along y=13
fold along y=6
*/

void fold(bool y, int f, set<ivec2>& points)
{
	if (y)
	{
		set<ivec2> next;
		int yf = f;
		for (ivec2 p : points)
		{
			if (p.y < yf)
			{
				next.insert(p);
			}
			else
			{
				ivec2 q(p.x, yf - (p.y - yf));
				next.insert(q);
			}
		}

		swap(points, next);
	}
	else
	{
		set<ivec2> next;
		int xf = f;
		for (ivec2 p : points)
		{
			if (p.x < xf)
			{
				next.insert(p);
			}
			else
			{
				ivec2 q(xf - (p.x - xf), p.y);
				next.insert(q);
			}
		}

		swap(points, next);
	}
}

static auto day = setDay(13, "Transparent Origami",
	[&](auto answer)
	{
		set<ivec2> points;

		auto lines = lines_in_file("input/13.txt");

		for (auto line : lines)
		{
			ivec2 p;

			(void)sscanf(line.c_str(), "%d,%d", &p.x, &p.y);
			points.insert(p);
		}

		fold(false, 655, points);
		fold(true,  447, points);
		fold(false, 327, points);
		fold(true, 223, points);
		fold(false, 163, points);
		fold(true, 111, points);
		fold(false, 81, points);
		fold(true, 55, points);
		fold(false, 40, points);
		fold(true, 27, points);
		fold(true, 13, points);
		fold(true, 6, points);

		for (int y = 0; y < 6; ++y)
		{
			for (int x = 0; x < 40; ++x)
			{
				if (points.count(ivec2(x, y)))
				{
					print("#");
				}
				else
				{
					print(".");
				}
			}
			println("");
		}

		uint64_t part1 = points.size();
		answer(1, part1);
		answer(2, 0);
	}
);
