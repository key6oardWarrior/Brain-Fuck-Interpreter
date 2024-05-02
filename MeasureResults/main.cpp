#include "pch.h"
#include "Results.hpp"
#include "MeasureResults.hpp"

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

		resultsOfTest.insert(std::pair<std::string, Results*>(argv[ii], new Results(argv[ii])));
		threads.emplace_back(std::thread(&Results::run, resultsOfTest[argv[ii]]));
	}

	// wait for all threads to stop
	for(int ii = 0; ii < threads.size(); ++ii)
		threads[ii].join();

	std::map<std::string, double> humanResults;
	std::map<std::string, double> llmResults;

	setUpResults(humanResults);
	setUpResults(llmResults);

	const size_t end = resultsOfTest.size()-2;
	measureResults(0, end, humanResults, resultsOfTest);
	measureResults(end, resultsOfTest.size(), llmResults, resultsOfTest);
	
	// clean up memory
	for(auto itr = resultsOfTest.begin(); itr != resultsOfTest.end(); ++itr) {
		delete itr->second;
		itr->second = nullptr;
	}

	std::cout << "Human results:\n";
	displayResults(humanResults);
	std::cout << "\nLLM results:\n";
	displayResults(llmResults);

	return EXIT_SUCCESS;
}
