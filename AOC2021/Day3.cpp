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

		println("1: ", gamma * epsilon);


		auto oxlines = lines;
		decltype(lines) oxnext;

		auto bitsum = [](auto lines, int i)
		{
			int bitsum = 0;
			for (auto line : lines)
			{
				bitsum += (line[i] - '0');
			}

			return bitsum;
		};

		for (int i = 0; i < 12; ++i)
		{
			if (oxlines.size() > 1)
			{
				int half = oxlines.size() / 2;
				int bs = bitsum(oxlines, i);
				char keep = bs >= half ? '1' : '0';

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

		for (int i = 0; i < 12; ++i)
		{
			if (colines.size() > 1)
			{
				int half = colines.size() / 2;
				int bs = bitsum(colines, i);
				char keep = bs >= half ? '0' : '1';

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

		println("2: ", ox*co);
	}
);
