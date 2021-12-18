#include "Common.h"

int main(int, char**)
{
	Stopwatch globalExecutionTimer;

	setActiveDay(17);
	//setNumRuns(1000);

	if (g_active_day)
	{
		runDay(getDay(g_active_day));
	}
	else
	{
		println("Running all ", getDayMap().size(), " days...");
		for (auto& it : getDayMap())
		{
			runDay(it.second);
		}
	}

	print("\nTotal time: ");
}

int g_num_runs = 1; // Single run by default, no benchmarking.
int g_active_day = 0; // Run all days by default.

DayMap& getDayMap()
{
	static DayMap dayMap;
	return dayMap;
}