#include "Common.h"

using namespace std;

auto stoi_transform = [](string const& s) { return stoi(s); };

struct Board
{

	std::vector<int> rows[5];
	std::vector<int> cols[5];
	int row_matches[5] = {0};
	int col_matches[5] = {0};
	int active_row = 0;
	int board_sum = 0;
	int latest_number = -1;

	void add_row(string const& line)
	{
		rows[active_row] = split(line, ' ', stoi_transform);

		for (int i = 0; i < 5; ++i)
		{
			cols[i].push_back(rows[active_row][i]);
			board_sum += rows[active_row][i];
		}

		++active_row;
	}

	bool mark(int num)
	{
		latest_number = num;

		bool bingo = false;
		bool match = false;
		for (int i = 0; i < 5; ++i)
		{
			auto& row = rows[i];
			if (std::find(begin(row), end(row), num) != end(row))
			{
				match = true;
				if (++row_matches[i] == 5)
				{
					bingo = true;
				}
			}

			auto& col = cols[i];
			if (std::find(begin(col), end(col), num) != end(col))
			{
				match = true;
				if (++col_matches[i] == 5)
				{
					bingo = true;
				}
			}
		}
		if (match)
		{
			board_sum -= num;
		}

		return bingo;
	}

	int score()
	{
		return board_sum * latest_number;
	}

	void print()
	{
		println("Rows:"); for (int i = 0; i < 5; ++i) { for (auto i : rows[i])::print(i, " "); println(""); }
		println("Cols:"); for (int i = 0; i < 5; ++i) { for (auto i : cols[i])::print(i, " "); println(""); }
	}
};

static auto day = setDay(4, "Giant Squid",
	[&]()
	{
		auto lines = lines_in_file("input/4.txt");
		auto it = lines.begin();
		auto end = lines.end();
		auto numbers = split(*(it++), ',', stoi_transform);

		list<Board> boards;
		list<Board> completed_boards;
		Board current;

		while (++it != end)
		{
			if (it->empty())
			{
				boards.push_back(current);
				current = Board();
			}
			else
			{
				current.add_row(*it);
			}
		}

		boards.push_back(current);

		int score = 0;
		for (auto num : numbers)
		{
			for (auto board = begin(boards); board != ::end(boards);)
			{
				if (board->mark(num))
				{
					completed_boards.push_back(*board);
					board = boards.erase(board);
				}
				else
				{
					++board;
				}
			}
		}

		println("1: ", completed_boards.front().score());
		println("2: ", completed_boards.back().score());
	}
);
