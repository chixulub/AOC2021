#define _CRT_SECURE_NO_WARNINGS
#include "Common.h"

using namespace std;

struct pathfinder
{
	vector<string> lines;
	int N;
	Grid2D<int> risk;
	Grid2D<int> minrisk;

	pathfinder(vector<string> input)
		: lines(input)
		, N((int)lines.size())
		, risk(N,N)
		, minrisk(N,N, numeric_limits<int>::max())
	{
		minrisk.at(0, 0) = 0;
		for (int y = 0; y < N; ++y)
		{
			for (int x = 0; x < N; ++x)
			{
				risk.at(x, y) = lines[y][x] - '0';
			}
		}
	}

	bool find_min()
	{
		auto get_minrisk = [this](int x, int y)
		{
			if (minrisk.valid(x, y))
			{
				return minrisk.at(x, y);
			}

			return numeric_limits<int>::max();
		};

		bool hot = false;

		minrisk.at(0, 0) = 0;
		for (int y = 0; y < N; ++y)
		{
			for (int x = 0; x < N; ++x)
			{
				if (x == 0 && y == 0) continue;

				int a = get_minrisk(x - 1, y);
				int b = get_minrisk(x + 1, y);
				int c = get_minrisk(x, y - 1);
				int d = get_minrisk(x, y + 1);
				int candidate = risk.at(x, y) + min(min(a, b), min(c, d));
				int current = minrisk.at(x, y);

				if (candidate < current)
				{
					minrisk.at(x, y) = candidate;
					hot = true;
				}
			}
		}

		return hot;
	}

	int result()
	{
		return minrisk.at(N - 1, N - 1);
	}
};

static auto day = setDay(15, "Chiton",
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
					for (auto c : lines[i])
					{
						int n = (c - '0' + x + y);
						if (n > 9)
						{
							n = n % 9;
						}

						newlines[y * M + i].push_back('0' + n);
					}
				}
			}
		}

		pathfinder p1(lines);
		pathfinder p2(newlines);

		while (p1.find_min());
		while (p2.find_min());

		uint64_t part1 = p1.result();
		uint64_t part2 = p2.result();

		answer(1, part1);
		answer(2, part2);
	}
);
