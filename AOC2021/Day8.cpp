#include "Common.h"

using namespace std;

static auto sort_transform = [](string const& s) { string S = s; std::sort(S.begin(), S.end()); return S;  };

int intersect(string const& A, string const& B)
{
	if (A.length() < B.length())
		return intersect(B, A);

	int count = 0;
	for (auto& a : A)
	{
		count += (B.find(a) != string::npos);
	}

	return count;
};

static auto day = setDay(8, "Seven Segment Search",
	[&](auto answer)
	{
		auto lines = lines_in_file("input/8.txt");

		set<size_t> valid_lengths = { 2, 3, 4, 7 };
		uint64_t part1 = 0;
		uint64_t part2 = 0;
		for (auto& line : lines)
		{
			auto foo = split(line, ' ', sort_transform);

			array<string,10> numbers;
			list<string> group_5;
			list<string> group_6;

			for (int i = 0; i < 10; ++i)
			{
				string& num = foo[i];
				switch (num.length())
				{
				case 2:
					numbers[1] = num;
					break;
				case 3:
					numbers[7] = num;
					break;
				case 4:
					numbers[4] = num;
					break;
				case 5:
					group_5.push_back(num);
					break;
				case 6:
					group_6.push_back(num);
					break;
				case 7:
					numbers[8] = num;
					break;
				default:
					println("ERROR! ", i, ": ", line);
					break;
				}
			}

			for (auto it = group_5.begin(); it != group_5.end(); ++it)
			{
				if (intersect(*it, numbers[1]) == 2)
				{
					numbers[3] = *it;
					group_5.erase(it);
					break;
				}
			}
			for (auto it = group_5.begin(); it != group_5.end(); ++it)
			{
				if (intersect(*it, numbers[4]) == 2)
				{
					numbers[2] = *it;
				}
				else
				{
					numbers[5] = *it;
				}
			}

			for (auto it = group_6.begin(); it != group_6.end(); ++it)
			{
				if (intersect(*it, numbers[1]) == 1)
				{
					numbers[6] = *it;
					group_6.erase(it);
					break;
				}
			}
			for (auto it = group_6.begin(); it != group_6.end(); ++it)
			{
				if (intersect(*it, numbers[4]) == 3)
				{
					numbers[0] = *it;
				}
				else
				{
					numbers[9] = *it;
				}
			}

			int display = 0;
			for (int i = 11; i < 15; ++i)
			{
				part1 += valid_lengths.count(foo[i].length());

				display *= 10;
				for (int j = 0; j < 10; ++j)
				{
					if (foo[i] == numbers[j])
					{
						display += j;
						break;
					}
				}
			}

			part2 += display;
		}

		answer(1, part1);
		answer(2, part2);
	}
);

/*
 6   2   5   5   4   5   6   3   7   6
(0) [1] (2) (3) [4] (5) (6) [7] [8] (9)

2: 1, 3: 7, 4: 4
5: 2 3 5
6: 0 6 9
7: 8

    2   3   5
1   1   2   1 -> 3/1 = 2
4   2   -   3 -> 2/4 = 2, 5/4 = 3

    0   6   9
 1  2   1   2 -> 6/1 = 1
 4  3   -   4 -> 0/4 = 3, 9/4 = 4
*/