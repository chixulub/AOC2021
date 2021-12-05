#define _CRT_SECURE_NO_WARNINGS
#include "Common.h"

using namespace std;

struct point_pair
{
	int x1, x2, y1, y2;
};

static auto day = setDay(5, "Hydrothermal Venture",
	[&](auto answer)
	{
		auto lines = lines_in_file("input/5.txt");

		Grid2D<int> grid(1000, 1000, 0);

		list<point_pair> diagonals;

		for (auto line : lines)
		{
			point_pair p;
			(void)sscanf(line.c_str(), "%d,%d -> %d,%d", &p.x1, &p.y1, &p.x2, &p.y2);

			if (p.y1 == p.y2)
			{
				if (p.x1 > p.x2) swap(p.x1, p.x2);

				for (int x = p.x1; x <= p.x2; ++x)
				{
					grid.at(x, p.y1) += 1;
				}
			}
			else if (p.x1 == p.x2)
			{
				if (p.y1 > p.y2) swap(p.y1, p.y2);

				for (int y = p.y1; y <= p.y2; ++y)
				{
					grid.at(p.x1, y) += 1;
				}
			}
			else
			{
				if (p.x1 > p.x2)
				{
					swap(p.x1, p.x2);
					swap(p.y1, p.y2);
				}
				diagonals.push_back(p);
			}	
		}

		int part1 = 0;
		for (auto i : grid.indexRange())
		{
			if (grid[i] > 1)
			{
				++part1;
			}
		}

		for (auto p : diagonals)
		{

			int d = (p.y1 < p.y2) ? 1 : -1;
			int y = p.y1;
			for (int x = p.x1; x <= p.x2; ++x, y += d)
			{
				grid.at(x, y) += 1;
			}
		}

		int part2 = 0;
		for (auto i : grid.indexRange())
		{
			if (grid[i] > 1)
			{
				++part2;
			}
		}

		answer(1, part1);
		answer(2, part2);
	}
);
