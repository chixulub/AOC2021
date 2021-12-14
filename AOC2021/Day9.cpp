#include "Common.h"

using namespace std;

static auto h = lines_in_file("input/9.txt");

static auto day = setDay(9, "",
	[&](auto answer)
	{

		vector<ivec2> lowpoints;

		uint64_t part1 = 0;
		for (int i = 0; i < 100; ++i)
		{
			for (int j = 0; j < 100; ++j)
			{
				bool low = true;
				char c = h[i][j];
				if (i > 0)  low = low && c < h[i - 1][j];
				if (i < 99) low = low && c < h[i + 1][j];
				if (j > 0)  low = low && c < h[i][j-1];
				if (j < 99) low = low && c < h[i][j+1];

				if (low)
				{
					part1  += (c - '0') + 1;

					if (c == '0')
					{
						lowpoints.push_back(ivec2{ i,j });
					}
				}
			}
		}

		int area[100][100] = { 0 };
		int idcount[100] = { 0 };
		int id = 1;
		for (auto p : lowpoints)
		{
			area[p.x][p.y] = id;
			++idcount[id];
			++id;
		}

		for (int k = 0; k < 9; ++k)
		{

			for (int i = 0; i < 100; ++i)
			{
				for (int j = 0; j < 100; ++j)
				{
					if (area[i][j] == 0 && h[i][j] != '9')
					{
						if (i > 0 && area[i - 1][j] != 0)
						{
							id = area[i - 1][j];
							area[i][j] = id;
							++idcount[id];
							continue;
						}

						if (i < 99 && area[i + 1][j] != 0)
						{
							id = area[i + 1][j];
							area[i][j] = id;
							++idcount[id];
							continue;
						}

						if (j > 0 && area[i][j - 1] != 0)
						{
							id = area[i][j - 1];
							area[i][j] = id;
							++idcount[id];
							continue;
						}

						if (j < 99 && area[i][j + 1] != 0)
						{
							id = area[i][j + 1];
							area[i][j] = id;
							++idcount[id];
							continue;
						}
					}
				}
			}
		}

		sort(begin(idcount), end(idcount), std::greater());

		uint64_t part2 = idcount[0] * idcount[1] * idcount[2];
		answer(1, part1);
		answer(2, part2);
	}
);
