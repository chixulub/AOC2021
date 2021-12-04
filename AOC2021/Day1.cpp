#include "Common.h"

using namespace std;

static auto day = setDay(1, "Sonar Sweep",
	[&](auto answer)
	{
		auto nums = numbers_in_file<int>("input/1.txt");
		int previous = numeric_limits<int>::max();
		int deeper1 = 0;
		int deeper2 = 0;

		foreach_pair(nums,
			[&](auto a, auto b) {
				deeper1 += b > a;
			}
		);

		foreach_triplet(nums,
			[&](auto a, auto b, auto c) {
				int current = a + b + c;
				deeper2 += current > previous;
				previous = current;
			}
		);

		answer(1, deeper1);
		answer(2, deeper2);
	}
);
