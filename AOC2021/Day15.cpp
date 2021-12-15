#define _CRT_SECURE_NO_WARNINGS
#include "Common.h"

using namespace std;

int find_min(vector<string> lines)
{
	int N = (int)lines.size();

	Grid2D<int> risk(N, N);
	Grid2D<int> minrisk(N, N);

	lines[0][0] = '0';
	for (int y = 0; y < N; ++y)
	{
		for (int x = 0; x < N; ++x)
		{
			risk.at(x, y) = lines[y][x] - '0';

			if (x == 0 && y > 0)
			{
				minrisk.at(x, y) = minrisk.at(x, y - 1) + risk.at(x, y);
			}
			else if (x > 0 && y == 0)
			{
				minrisk.at(x, y) = minrisk.at(x - 1, y) + risk.at(x, y);
			}
			else
			{
				minrisk.at(x, y) = risk.at(x, y) + min(minrisk.at(x - 1, y), minrisk.at(x, y - 1));
			}
		}
	}

	return minrisk.at(N - 1, N - 1);
}

static auto day = setDay(15, "",
	[&](auto answer) 
	{
		auto lines = lines_in_file("input/15.txt");

		int M = (int)lines.size();
		vector<string> newlines(M*5);

		for (int y = 0; y < 5; ++y)
		{
			for (int x = 0; x < 5; ++x)
			{
				for (int i = 0; i < M; ++i)
				{
					auto line = lines[i];
					auto& nline = newlines[y * M + i];

					for (auto c : line)
					{
						int n = (c - '0' + x + y);
						if (n > 9)
						{
							n = n % 9;
						}

						nline.push_back('0' + n);
					}
				}
			}
		}

		uint64_t part2 = find_min(newlines);
		uint64_t part1 = find_min(lines);

		answer(1, part1);
		answer(2, part2);
	}
);
