#pragma once

class Results : private Interpreter {
public:
	size_t timeInSeconds = 0;
	size_t memoryBlocksUsed;
	size_t totalDataUsed;

	Results(const std::string& filePath) : Interpreter(filePath) {}
	~Results() = default;

	void run();
};