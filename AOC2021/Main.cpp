#include "Common.h"

DayMap& getDayMap()
{
	static DayMap dayMap;
	return dayMap;
}

int main(int, char**)
{
	Stopwatch globalExecutionTimer;

	uint32_t activeDay = 0;

	if (activeDay)
	{
		println("\n>>> Day ", activeDay, ": \"", getDayMap().at(activeDay).first, "\"");
		getDayMap().at(activeDay).second();
		print("<<< Day ", activeDay, " took ");
	}
	else
	{
		println("Running all ", getDayMap().size(), " days...");
		for (auto& it : getDayMap())
		{
			Stopwatch localExecutionTimer;
			println("\n>>> Day ", it.first, ": \"", it.second.first, "\"");
			it.second.second();
			print("<<< Day ", it.first, " took ");
		}

		print("\nTotal time: ");
	}
}
