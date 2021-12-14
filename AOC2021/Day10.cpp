#include "Common.h"

using namespace std;

static auto stoi_transform = [](string const& s) { return stoi(s); };

char opens(char c)
{
	switch (c)
	{
	case '<': return '>';
	case '(': return ')';
	case '[': return ']';
	case '{': return '}';
	}

	return 0;
}

int score1(char c)
{
	switch (c)
	{
	case '>': return 25137;
	case ')': return 3;
	case ']': return 57;
	case '}': return 1197;
	}

	return 0;
}

int score2(char c)
{
	switch (c)
	{
	case '>': return 4;
	case ')': return 1;
	case ']': return 2;
	case '}': return 3;
	}

	return 0;
}

static auto day = setDay(10, "Syntax Scoring",
	[&](auto answer)
	{
		uint64_t part1 = 0;
		vector<uint64_t> scores;

		for (auto& line : lines_in_file("input/10.txt"))
		{
			vector<char> closers;
			bool discarded = false;
			for (char c : line)
			{
				if (char t = opens(c))
				{
					closers.push_back(t);
				}
				else
				{
					if (closers.back() != c)
					{
						part1 += score1(c);
						discarded = true;
						break;
					}

					closers.pop_back();
				}
			}

			if (!discarded && closers.size())
			{
				uint64_t score = 0;

				for (auto it = closers.rbegin(); it != closers.rend(); ++it)
				{
					score = score * 5 + score2(*it);
				}

				scores.push_back(score);
			}
		}

		sort(scores.begin(), scores.end());
		uint64_t part2 = scores[scores.size() / 2];

		answer(1, part1);
		answer(2, part2);
	}
);
