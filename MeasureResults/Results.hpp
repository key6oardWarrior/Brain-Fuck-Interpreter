#pragma once

class Results : private Interpreter {
public:
	double timeInSeconds = 0;
	double memoryBlocksUsed;
	double totalDataUsed;

	Results(const std::string& filePath) : Interpreter(filePath) {}
	~Results() = default;

	void run();
};
