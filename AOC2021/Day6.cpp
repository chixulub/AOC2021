#include "Common.h"

using namespace std;

static auto stoi_transform = [](string const& s) { return stoi(s); };

static auto day = setDay(6, "",
	[&](auto answer)
	{
		vector<uint64_t> fishes(264, 0);

		for (uint64_t i : split(lines_in_file("input/6.txt").front(), ',', stoi_transform))
		{
			++fishes[i];
		}

		uint64_t *f = &fishes[0], *end = &fishes[256], *sample = &fishes[81];

		uint64_t part1 = 0;
		for (; f < end ; ++f)
		{
			if (f == sample)
			{
				for (int j = 0; j < 8; ++j)
				{
					part1 += f[j];
				}
			}

			f[7] += f[0];
			f[9]  = f[0];
		}

		uint64_t part2 = 0;
		for (int j = 0; j < 9; ++j)
		{
			part2 += f[j];
		}

		answer(1, part1);
		answer(2, part2);
	}
);
