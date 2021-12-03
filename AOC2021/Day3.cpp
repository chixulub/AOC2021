#include "Common.h"

using namespace std;

static auto day = setDay(3, "Binary Diagnostic",
	[&]()
	{
		int const N = 12;
		auto lines = lines_in_file("input/3.txt");

		array<int, 12> bitsums = { 0 };
		for (auto line : lines)
		{
			for (int i = 0; i < 12; ++i)
			{
				bitsums[i] += (line[i] - '0');
			}
		}

		string gamma, epsilon;

		int half = lines.size() / 2;
		for (auto sum : bitsums)
		{
			gamma.push_back('0' + (sum > half));
			epsilon.push_back('0' + (sum <= half));
		}

		auto life_support_rating = [N](decltype(lines) lines, auto compare)
		{
			auto find_value_to_keep = [](auto& lines, int bit, auto compare)
			{
				int one = 0, zero = 0;
				for (auto line : lines)
				{
					one += (line[bit] == '1');
					zero += (line[bit] == '0');
				}

				return compare(one, zero) ? '1' : '0';
			};

			decltype(lines) next;

			for (int i = 0; i < N; ++i)
			{
				if (lines.size() > 1)
				{
					next.clear();
					char keep = find_value_to_keep(lines, i, compare);

					for (auto& line : lines)
					{
						if (line[i] == keep)
						{
							next.push_back(line);
						}
					}
					swap(lines, next);
				}
			}

			return lines[0];
		};

		auto oxygen = life_support_rating(lines, std::greater_equal());
		auto co2 = life_support_rating(lines, std::less());

		println("1: ", stoi(gamma, nullptr, 2) * stoi(epsilon, nullptr, 2));
		println("2: ", stoi(oxygen, nullptr, 2) * stoi(co2, nullptr, 2));
	}
);
