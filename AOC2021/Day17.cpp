#define _CRT_SECURE_NO_WARNINGS
#include "Common.h"

using namespace std;

static auto day = setDay(17, "Trick Shot",
	[&](auto answer)
	{
		auto input = lines_in_file("input/17.txt").front();

		int xleft=0, xright=0, ytop=0, ybottom=0;
		(void)sscanf(input.c_str(), "target area: x=%d..%d, y=%d..%d", &xleft, &xright, &ytop, &ybottom);
		if (ytop < ybottom) swap(ytop, ybottom);
		if (xleft > xright) swap(xleft, xright);

		auto inside_x = [=](int x)
		{
			return (x >= xleft && x <= xright);
		};
		auto inside_y = [=](int y)
		{
			return (y <= ytop && y >= ybottom);
		};
		auto inside = [=](int x, int y)
		{
			return (inside_x(x) && inside_y(y));
		};

		uint64_t part2 = 0;
		uint64_t part1 = 0;

		auto y_peak_until = [&](int vymax)
		{
			int max_peak = 0;
			for (int vy0 = 1; vy0 < vymax; ++vy0)
			{
				int peak = 0;

				int y = 0;
				int vy = vy0;
				for (int t = 1;; ++t)
				{
					y += vy;
					vy -= 1;
					peak = max(peak, y);
					if (inside_y(y))
					{
						break;
					}

					if (y < ybottom)
					{
						peak = 0;
						break;
					}
				}

				max_peak = max(peak, max_peak);
			}

			return max_peak;
		};

		part1 = y_peak_until(1000);

		auto hits = [&](int vx0, int vy0)
		{
			int x = 0;
			int y = 0;
			int vx = vx0;
			int vy = vy0;
			int dvx = vx0 < 0 ? 1 : -1;
			for (;;)
			{
				y += vy;
				vy -= 1;

				x += vx;
				if (vx != 0)
				{
					vx += dvx;
				}

				if (inside(x, y))
				{
					return true;
				}

				if (x > xright || y < ybottom)
				{
					return false;
				}
			}

			return false;
		};

		set<pair<int, int>> valids;

		for (int vx = (int)sqrt(xleft)/2; vx < xright+1; ++vx)
		{
			for (int vy = ybottom; vy <= 1000; ++vy)
			{
				if (hits(vx, vy))
				{
					valids.insert({ vx,vy });
				}
			}
		}

		part2 = valids.size();

		answer(1, part1);
		answer(2, part2);
	}
);
