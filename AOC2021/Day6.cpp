#include "Common.h"

using namespace std;

static auto stoi_transform = [](string const& s) { return stoi(s); };

static auto day = setDay(6, "",
	[&](auto answer)
	{
		auto initial = split(lines_in_file("input/6.txt").front(), ',', stoi_transform);

		map<uint64_t, uint64_t> fishes{ {0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0} };

		for (uint64_t i : initial)
		{
			fishes[i] += 1;
		}

		map<uint64_t, uint64_t> day80;
		for (int i = 0; i < 256; ++i)
		{
			map<uint64_t, uint64_t> next;

			next[0] = fishes[1];
			next[1] = fishes[2];
			next[2] = fishes[3];
			next[3] = fishes[4];
			next[4] = fishes[5];
			next[5] = fishes[6];
			next[6] = fishes[7] + fishes[0];
			next[7] = fishes[8];
			next[8] = fishes[0];

			swap(fishes, next);

			if (i == 79)
			{
				day80 = fishes;
			}
		}

		uint64_t part1 = 0;
		for (auto& it : day80)
		{
			part1 += it.second;
		}

		uint64_t part2 = 0;
		for (auto& it : fishes)
		{
			part2 += it.second;
		}

		answer(1, part1);
		answer(2, part2);
	}
);
