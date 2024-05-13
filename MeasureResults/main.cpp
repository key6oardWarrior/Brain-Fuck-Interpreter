#include "pch.h"

int main(size_t argc, char* argv[]) {
	if(argc < 1)
		throw std::runtime_error("Expected more than 1 command line argument");

	std::map<std::string, Results*> resultsOfTest;
	std::vector<std::thread> threads;

	for(int ii = 1; ii < argc-1; ++ii) {
		if(std::filesystem::exists(std::filesystem::path(argv[ii])) == 0) {
			std::string msg = "File, ";
			msg += argv[ii];
			msg += ", not found";
			throw std::filesystem::filesystem_error(msg, std::error_code());
		}

		std::vector<char> printedValues;
		resultsOfTest.insert(std::pair<std::string, Results*>(argv[ii], new Results(argv[ii], printedValues)));
		threads.emplace_back(std::thread(&Results::run, resultsOfTest[argv[ii]]));
	}

	// wait for all threads to stop
	for(int ii = 0; ii < threads.size(); ++ii)
		threads[ii].join();

	std::map<std::string, double> humanResults;
	std::map<std::string, double> llmResults;

	setUpResults(humanResults);
	setUpResults(llmResults);

	// check human results
	constexpr size_t humanFacts = 3;
	constexpr size_t humanFixStr = humanFacts + 1;
	constexpr size_t humanWoteName = humanFixStr + 3;
	constexpr size_t totalHumanCode = 7;
	std::vector<std::string> expectedNames = {"AMIT NAIK", "Micheal Sergio!", "xazonbi"};
	std::vector<std::string> expectedSpelling = {"good bye world"};
	checkFactorialResults(0, humanFacts, resultsOfTest, 5);
	checkStringResults(humanFacts, humanFixStr, resultsOfTest, expectedSpelling);
	checkStringResults(humanFixStr, humanWoteName, resultsOfTest, expectedNames);

	// check llm results
	constexpr size_t llmFactEnd = totalHumanCode + 2;
	constexpr size_t llmFixStrEnd = llmFactEnd + 2;
	checkFactorialResults(totalHumanCode, llmFactEnd, resultsOfTest, 5);
	checkStringResults(llmFactEnd, llmFixStrEnd, resultsOfTest, expectedSpelling);
	checkStringResults(llmFixStrEnd, argc-1, resultsOfTest, expectedNames);

	measureResults(0, totalHumanCode, humanResults, resultsOfTest);
	measureResults(totalHumanCode, resultsOfTest.size(), llmResults, resultsOfTest);
	
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
