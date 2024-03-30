#pragma once
#include "Errors.hpp"
#include "Environment.hpp"

class Interpreter {
protected:
	std::fstream code;
	std::string codeLine;

	Environment* env = new Environment();

	const size_t maxInt = 0x7f;
	const signed int minInt = -0x80;
	int lineNum = 1;
	bool isSameLine = 0;
	bool isMaxPositive = 0;
	bool isMaxNegative = 0;

	/// <summary>
	/// Ensure all open brackets have an close bracket
	/// </summary>
	/// <param name="ii">- Current line that is being read</param>
	/// <returns>True if found the closing bracket</returns>
	bool isBalanced(size_t) const;

	/// <summary>
	/// Go to the end of loop
	/// </summary>
	/// <param name="charIndex">- Starting char index</param>
	void goToEnd(size_t&) const;

	/// <summary>
	/// Print the error message's char, char's index, and what line it is on
	/// </summary>
	/// <param name="userChar">- The char that caused the error</param>
	/// <param name="charIndex">- Which char on the line caused the error</param>
	void errorDescription(const char userChar, const size_t charIndex) const {
		std::cout << std::endl << "Error:" << std::endl;
		std::cout << "char: " << userChar << std::endl;
		std::cout << "line number: " << lineNum << std::endl;
		std::cout << "char index: " << charIndex << std::endl;
	}

	/// <summary>
	/// Determin if the symbol in the bf file is legal if it is then carry out
	/// instructions else return int that correlates to enum class ErrorMessage
	/// </summary>
	/// <returns>The error code to be displayed</returns>
	ErrorMessage isSymbolLegal(void);

	/// <summary>
	/// Interpret all code in the file
	/// </summary>
	/// <returns></returns>
	ErrorMessage interpret(void);

public:
	/// <summary>
	/// Open the users file via std::fstream
	/// </summary>
	/// <param name="filePath">- file path</param>
	Interpreter(const std::string& filePath) { code.open(filePath); }

	~Interpreter() { code.close(); }

	void main(void);
};