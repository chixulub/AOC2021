#include "Common.h"

using namespace std;

static auto day = setDay(3, "Binary Diagnostic",
	[&]()
	{
		auto lines = lines_in_file("input/3.txt");

		array<int, 12> bitsums = { 0 };
		for (auto line : lines)
		{
			for (int i = 0; i < 12; ++i)
			{
				bitsums[i] += (line[i] - '0');
			}
		}

		int half = lines.size() / 2;

		int gamma = 0;
		int epsilon = 0;
		for (int i = 0; i < 12; ++i)
		{
			if (bitsums[11-i] > half)
			{
				gamma += (1 << i);
			}
			else
			{
				epsilon += (1 << i);
			}
		}



		auto oxlines = lines;
		decltype(lines) oxnext;

		auto most_common = [](auto lines, int i)
		{
			int one = 0;
			int zero = 0;
			for (auto line : lines)
			{
				if (line[i] == '0')
				{
					zero++;
				}
				else
				{
					one++;
				}
			}

			return one >= zero ? '1' : '0';
		};

		for (int i = 0; i < 12; ++i)
		{
			if (oxlines.size() > 1)
			{
				char keep = most_common(oxlines, i);

				for (auto& line : oxlines)
				{
					if (line[i] == keep)
					{
						oxnext.push_back(line);
					}
				}
			}
			else
			{
				break;
			}

			swap(oxlines, oxnext);
			oxnext.clear();
		}

		auto colines = lines;
		decltype(lines) conext;
		auto least_common = [](auto lines, int i)
		{
			int bitsum = 0;
			int one = 0;
			int zero = 0;
			for (auto line : lines)
			{
				if (line[i] == '0')
				{
					zero++;
				}
				else
				{
					one++;
				}
			}

			return one < zero ? '1' : '0';
		};

		for (int i = 0; i < 12; ++i)
		{
			if (colines.size() > 1)
			{
				char keep = least_common(colines, i);

				for (auto& line : colines)
				{
					if (line[i] == keep)
					{
						conext.push_back(line);
					}
				}
			}
			else
			{
				break;
			}

			swap(colines, conext);
			conext.clear();
		}

		uint64_t ox = 0;
		uint64_t co = 0;

		for (int i = 0; i < 12; ++i)
		{
			ox += (1 << i) * (oxlines[0][11-i] == '1');
			co += (1 << i) * (colines[0][11-i] == '1');
		}

		println("1: ", gamma * epsilon);
		println("2: ", ox*co);
	}
);
