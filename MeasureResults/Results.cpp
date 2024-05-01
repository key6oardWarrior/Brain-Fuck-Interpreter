#include "pch.h"
#include "Results.hpp"

void Results::run() {
	// track how long it takes to run the code
	const std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
	__super::startInterpreting();
	const std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();

	// store all relevant metrics
	const std::chrono::duration<double, std::milli> elapsed = end - start;

	// how much time passed in seconds
	timeInSeconds = elapsed.count() / 1000;

	// count the amout of memory blocks used and total data used
	for(int ii = 0; ii < 30'000; ++ii) {
		if(__super::mem->memory[ii].value) {
			++memoryBlocksUsed;
			totalDataUsed += __super::mem->memory[ii].value;
		}
	}
}