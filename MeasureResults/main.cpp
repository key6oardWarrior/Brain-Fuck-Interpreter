#include "pch.h"
#include "Results.hpp"

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

void messureResults(size_t start, const size_t end, std::map<std::string, double>& measuredResults, const std::map<std::string, Results*>& tests) {
	auto itr = tests.begin();

	for(start; start < end; ++start) {
		measuredResults.at("avg amount of memory blocks used") += itr->second->memoryBlocksUsed;
		measuredResults.at("avg amount of total memory used") += itr->second->totalDataUsed;
		measuredResults.at("avg time") += itr->second->timeInSeconds;

		if(measuredResults.at("fastest time") < itr->second->timeInSeconds)
			measuredResults.at("fastest time") = itr->second->timeInSeconds;
		else if(measuredResults.at("fastest time") == -1.0)
			measuredResults.at("fastest time") = itr->second->timeInSeconds;

		if(measuredResults.at("slowest time") > itr->second->timeInSeconds)
			measuredResults.at("slowest time") = itr->second->timeInSeconds;
		else if(measuredResults.at("slowest time") == -1.0)
			measuredResults.at("slowest time") = itr->second->timeInSeconds;

		if(measuredResults.at("most amount of memory blocks used") < itr->second->memoryBlocksUsed)
			measuredResults.at("most amount of memory blocks used") = itr->second->memoryBlocksUsed;

		if(measuredResults.at("least amount of memory blocks used") > itr->second->memoryBlocksUsed)
			measuredResults.at("least amount of memory blocks used") = itr->second->memoryBlocksUsed;

		if(measuredResults.at("most amount of total memory used") < itr->second->totalDataUsed)
			measuredResults.at("most amount of total memory used") = itr->second->totalDataUsed;

		if(measuredResults.at("least amount of total memory used") > itr->second->totalDataUsed)
			measuredResults.at("least amount of total memory used") = itr->second->totalDataUsed;

		++itr;
	}

	measuredResults.at("avg amount of memory blocks used") /= end;
	measuredResults.at("avg amount of total memory used") /= end;
	measuredResults.at("avg time") /= end;
}

void displayResults(std::map<std::string, double>& results) {
	for(auto itr = results.begin(); itr != results.end(); ++itr)
		std::cout << itr->first << ": " << itr->second;
}

int main(size_t argc, char* argv[]) {
	if(argc < 6)
		throw std::runtime_error("Expected at least 6 command line arguments, but got " + std::to_string(argc));

	std::map<std::string, Results*> resultsOfTest;
	std::vector<std::thread> threads;

	for(int ii = 1; ii < argc; ++ii) {
		if(std::filesystem::exists(std::filesystem::path(argv[ii])) == 0) {
			std::string msg = "File, ";
			msg += argv[ii];
			msg += ", not found";
			throw std::filesystem::filesystem_error(msg, std::error_code());
		}

		resultsOfTest.emplace((argv[ii], new Results(argv[ii])));
		threads.emplace_back(std::thread(&Results::run, resultsOfTest.at(argv[ii])));
	}

	// wait for all threads to stop
	for(int ii = 0; ii < threads.size(); ++ii)
		threads[ii].join();

	std::map<std::string, double> humanResults;
	std::map<std::string, double> llmResults;

	setUpResults(humanResults);
	setUpResults(llmResults);

	const size_t end = resultsOfTest.size()-2;
	messureResults(0, end, humanResults, resultsOfTest);
	messureResults(end, resultsOfTest.size(), llmResults, resultsOfTest);
	
	// clean up memory
	for(auto itr = resultsOfTest.begin(); itr != resultsOfTest.end(); ++itr) {
		delete itr->second;
		itr->second = nullptr;
	}

	std::cout << "Human results:\n";
	displayResults(humanResults);
	std::cout << "LLM results:\n";
	displayResults(llmResults);

	return EXIT_SUCCESS;
}