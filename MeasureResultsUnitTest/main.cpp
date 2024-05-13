#include "pch.h"

int main(void) {
	std::map<std::string, Results*> tests;
	const std::string errMsg = "measured results contains wrong value";

	std::vector<char> printedValues;
	tests["fileName"] = new Results("", printedValues);
	tests["fileName1"] = new Results("", printedValues);
	tests["fileName2"] = new Results("", printedValues);

	tests["fileName"]->memoryBlocksUsed = 5;
	tests["fileName"]->timeInSeconds = 10;
	tests["fileName"]->totalDataUsed = 20;
	tests["fileName"]->isSuccessful = 1;

	tests["fileName1"]->memoryBlocksUsed = 5;
	tests["fileName1"]->timeInSeconds = 10;
	tests["fileName1"]->totalDataUsed = 20;
	tests["fileName1"]->isSuccessful = 1;

	tests["fileName2"]->memoryBlocksUsed = 5;
	tests["fileName2"]->timeInSeconds = 10;
	tests["fileName2"]->totalDataUsed = 20;
	tests["fileName2"]->isSuccessful = 1;

	std::map<std::string, double> measuredResults;

	setUpResults(measuredResults);
	measureResults(0, 3, measuredResults, tests);

	assert((void(errMsg), measuredResults["avg amount of memory blocks used"] == 5.0));
	assert((void(errMsg), measuredResults["avg amount of total memory used"] == 20));
	assert((void(errMsg), measuredResults["avg time"] == 10));

	return EXIT_SUCCESS;
}
