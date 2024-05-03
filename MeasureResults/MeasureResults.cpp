#include "pch.h"
#include "Results.hpp"
#include "MeasureResults.hpp"

void setUpResults(std::map<std::string, double>& results) {
	results["avg time"] = 0.0;
	results["fastest time"] = -1.0;
	results["slowest time"] = -1.0;
	results["is successful"] = 0.0; // can be either 0.0 or 1.0

	results["avg amount of memory blocks used"] = 0.0;
	results["most amount of memory blocks used"] = 0.0;
	results["least amount of memory blocks used"] = 0.0;

	results["least amount of total memory used"] = 0.0;
	results["most amount of total memory used"] = 0.0;
	results["avg amount of total memory used"] = 0.0;
}

void measureResults(size_t start, const size_t end, std::map<std::string, double>& measuredResults, const std::map<std::string, Results*>& tests) {
	auto itr = tests.begin();
	
	size_t ii = 0;
	while(ii++ < start)
		++itr;

	for(start; start < end; ++start) {
		measuredResults["avg amount of memory blocks used"] += itr->second->memoryBlocksUsed;
		measuredResults["avg amount of total memory used"] += itr->second->totalDataUsed;
		measuredResults["avg time"] += itr->second->timeInSeconds;

		if(measuredResults["fastest time"] < itr->second->timeInSeconds)
			measuredResults["fastest time"] = itr->second->timeInSeconds;
		else if(measuredResults["fastest time"] == -1.0)
			measuredResults["fastest time"] = itr->second->timeInSeconds;

		if(measuredResults["slowest time"] > itr->second->timeInSeconds)
			measuredResults["slowest time"] = itr->second->timeInSeconds;
		else if(measuredResults["slowest time"] == -1.0)
			measuredResults["slowest time"] = itr->second->timeInSeconds;

		if(measuredResults["most amount of memory blocks used"] < itr->second->memoryBlocksUsed)
			measuredResults["most amount of memory blocks used"] = itr->second->memoryBlocksUsed;

		if(measuredResults["least amount of memory blocks used"] > itr->second->memoryBlocksUsed)
			measuredResults["least amount of memory blocks used"] = itr->second->memoryBlocksUsed;

		if(measuredResults["most amount of total memory used"] < itr->second->totalDataUsed)
			measuredResults["most amount of total memory used"] = itr->second->totalDataUsed;

		if(measuredResults["least amount of total memory used"] > itr->second->totalDataUsed)
			measuredResults["least amount of total memory used"] = itr->second->totalDataUsed;

		++itr;
	}

	measuredResults["avg amount of memory blocks used"] /= end;
	measuredResults["avg amount of total memory used"] /= end;
	measuredResults["avg time"] /= end;
	measuredResults["is successful"] = itr->second->isSuccessful;
}

void displayResults(std::map<std::string, double>& results) {
	int cnt = 0;
	for(auto itr = results.begin(); itr != results.end(); ++itr)
		std::cout << "Test #" << cnt++ << " " << itr->first << ": " << itr->second;
}
