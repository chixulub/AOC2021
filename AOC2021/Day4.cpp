#include "Common.h"

using namespace std;

static auto stoi_transform = [](string const& s) { return stoi(s); };

struct Board
{
	std::vector<int> rows[5];
	std::vector<int> cols[5];
	int row_matches[5] = {0};
	int col_matches[5] = {0};
	int active_row = 0;
	int board_sum = 0;
	int score = 0;

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
		for (int r = 0; r < 5; ++r)
		{
			auto& row = rows[r];
			for (int c = 0; c < 5; ++c)
			{
				if (row[c] == num)
				{
					board_sum -= num;
					if (++row_matches[r] == 5 || ++col_matches[c] == 5)
					{
						score = board_sum * num;
						return true;
					}
				}
			}
		}

		return false;
	}
};

static auto day = setDay(4, "Giant Squid",
		[&](auto answer)
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

			answer(1, completed_boards.front().score);
			answer(2, completed_boards.back().score);
		}
);
