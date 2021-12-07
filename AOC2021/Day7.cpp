#include "Common.h"

using namespace std;

static auto stoi_transform = [](string const& s) { return stoi(s); };

static auto day = setDay(7, "The Treachery of Whales",
	[&](auto answer)
	{
		auto positions = split(lines_in_file("input/7.txt").front(), ',', stoi_transform);

		int fuel1[1000] = { 0 };
		int fuel2[1000] = { 0 };
		for (int i = 0; i < 1000; ++i)
		{
			for (auto p : positions)
			{
				int n = abs(p - i);
				fuel1[i] += n;
				fuel2[i] += (n*(n+1))/2;

			}
		}

		answer(1, std::ranges::min(fuel1));
		answer(2, std::ranges::min(fuel2));
	}
);
