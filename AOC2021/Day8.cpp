#include "Common.h"

using namespace std;

static auto no_transform = [](string const& s) { return s; };

static auto day = setDay(8, "Seven Segment Search",
	[&](auto answer)
	{
		auto lines = lines_in_file("input/8.txt");

		uint64_t part1 = 0;
		set<size_t> valid_lengths = {2, 3, 4, 7};
		for (auto& line : lines)
		{
			auto foo = split(line, ' ', no_transform);
			for (int i = 11; i < 15; ++i)
			{
				part1 += valid_lengths.count(foo[i].length());
			}
		}

		answer(1, part1);
		answer(2, 0);
	}
);
