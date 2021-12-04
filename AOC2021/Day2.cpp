#define _CRT_SECURE_NO_WARNINGS
#include "Common.h"

using namespace std;


static auto day = setDay(2, "Dive!",
	[&](auto answer)
	{
		auto lines = lines_in_file("input/2.txt");

		char command[8] = { 0 }; // "forward\0"
		int param;

		int x = 0;
		int y1 = 0;
		int y2 = 0;
		int dy = 0;

		for (auto& line : lines)
		{
			(void)sscanf(line.c_str(), "%s %d", command, &param);

			switch (command[0])
			{
			case 'f':
				x += param;
				y2 += dy * param;
				break;
			case 'u': 
				y1 -= param;
				dy -= param;
				break;
			case 'd':
				y1 += param;
				dy += param;
				break;
			default:
				break;
			}
		}


		answer(1, x * y1);
		answer(2, x * y2);
	}
);
