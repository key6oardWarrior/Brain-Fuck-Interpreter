#include "pch.h"
#include "Results.hpp"
#include "MeasureResults.hpp"

void setUpResults(std::map<std::string, double>& results) {
	results["avg time"] = 0.0;
	results["fastest time"] = -1.0;
	results["slowest time"] = -1.0;

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
		if(itr->second->isSuccessful) {
			if(itr->second->isSuccessful) {
				measuredResults["avg amount of memory blocks used"] += itr->second->memoryBlocksUsed;
				measuredResults["avg amount of total memory used"] += itr->second->totalDataUsed;
				measuredResults["avg time"] += itr->second->timeInSeconds;
			}

			if(measuredResults["fastest time"] < itr->second->timeInSeconds)
				measuredResults["fastest time"] = itr->second->timeInSeconds;
			else if(measuredResults["fastest time"] == -1.0)
				measuredResults["fastest time"] = itr->second->timeInSeconds;

			if(measuredResults["slowest time"] > itr->second->timeInSeconds)
				measuredResults["slowest time"] = itr->second->timeInSeconds;
			else if(measuredResults["slowest time"] == -1.0)
				measuredResults["slowest time"] = itr->second->timeInSeconds;

			if((measuredResults["most amount of memory blocks used"] < itr->second->memoryBlocksUsed) || (measuredResults["most amount of memory blocks used"] == 0.0))
				measuredResults["most amount of memory blocks used"] = itr->second->memoryBlocksUsed;

			if((measuredResults["least amount of memory blocks used"] >= itr->second->memoryBlocksUsed) || (measuredResults["least amount of memory blocks used"] == 0.0))
				measuredResults["least amount of memory blocks used"] = itr->second->memoryBlocksUsed;

			if((measuredResults["most amount of total memory used"] < itr->second->totalDataUsed) || (measuredResults["most amount of total memory used"] == 0.0))
				measuredResults["most amount of total memory used"] = itr->second->totalDataUsed;

			if((measuredResults["least amount of total memory used"] >= itr->second->totalDataUsed) || (measuredResults["least amount of total memory used"] == 0.0))
				measuredResults["least amount of total memory used"] = itr->second->totalDataUsed;
		}

		++itr;
	}

	if(measuredResults["avg amount of memory blocks used"] > 0)
		measuredResults["avg amount of memory blocks used"] /= end;

	if(measuredResults["avg amount of total memory used"] > 0)
		measuredResults["avg amount of total memory used"] /= end;

	if(measuredResults["avg time"])
		measuredResults["avg time"] /= end;
}

void displayResults(std::map<std::string, double>& results) {
	for(auto itr = results.begin(); itr != results.end(); ++itr)
		std::cout << " " << itr->first << ": " << itr->second << std::endl;
}

void checkFactorialResults(size_t start, const size_t end, const std::map<std::string, Results*>& tests, const int expectedResult) {
	auto itr = tests.begin();

	size_t ii = 0;
	while(ii++ != start)
		++itr;

	while(start++ != end) {
		itr->second->isSuccessful = ((*itr->second->printedValues)[0] == expectedResult);
		++itr;
	}
}

void checkStringResults(size_t start, const size_t end, const std::map<std::string, Results*>& tests, const std::vector<std::string>& expectedResults) {
	auto itr = tests.begin();

	size_t ii = 0;
	while(ii++ != start)
		++itr;

	std::string allChars;
	size_t expectedResultsIdx = 0;
	while(ii++ != end) {
		for(int jj = 0; jj < (*itr->second->printedValues).size(); ++jj) {
			itr->second->isSuccessful = expectedResults[expectedResultsIdx].substr(jj, jj + 1) == std::to_string((*itr->second->printedValues)[jj]);

			if(itr->second->isSuccessful == 0)
				break;
		}

		++itr;
	}
}