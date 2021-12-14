#include "Common.h"

using namespace std;

static auto day = setDay(11, "Dumbo Octopus",
	[&](auto answer)
	{
		Grid2D<int> grid(10,10);

		int index = 0;
		for (auto& line : lines_in_file("input/11.txt"))
		{
			for (char c : line)
			{
				grid[index++] = c - '0';
			}
		}


		uint64_t part1 = 0;

		int step = 0;
		for (;; ++step)
		{
			// 1) Increase energy
			for (auto i : grid.indexRange())
			{
				grid[i] += 1;
			}

			Grid2D<int> flashed(10, 10, 0);


			// 2) Flash!
			bool did_flash = true;
			while (did_flash)
			{
				did_flash = false;

				for (int y = 0; y < 10; ++y)
				{
					for (int x = 0; x < 10; ++x)
					{
						if (flashed.at(x, y) == 0 && grid.at(x,y) > 9)
						{
							if (step < 100)
							{
								++part1;
							}

							flashed.at(x, y) = (did_flash = true);

							for (int j = -1; j <= 1; ++j)
							{
								for (int i = -1; i <= 1; ++i)
								{
									if (i != 0 || j != 0)
									{
										if (grid.valid(x + i, y + j))
										{
											grid.at(x + i, y + j) += 1;
										}
									}
								}
							}
						}
					}
				}
			}

			// 3) Reset flashers energies to 0.
			int step_flashes = 0;
			for (auto i : flashed.indexRange())
			{
				if (flashed[i])
				{
					grid[i] = 0;
					++step_flashes;
				}
			}

			if (step_flashes == 100)
			{
				break;
			}
		}

		uint64_t part2 = step + 1;

		answer(1, part1);
		answer(2, part2);
	}
);
