#pragma once

class Results : private Interpreter {
public:
	double timeInSeconds;
	double memoryBlocksUsed;
	double totalDataUsed;
	bool isSuccessful;
	std::vector<char>* printedValues;

	Results(const std::string& filePath) : Interpreter(filePath, printedValues) {}
	~Results() = default;

	/// <summary>
	/// Start interpreting code and store the relevant data.
	/// </summary>
	void run();
};
