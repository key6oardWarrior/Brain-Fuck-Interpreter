#pragma once

class InterpreterUnitTest : private Interpreter {
private:
	const std::string balancedCodeLine = "[[]][[++--,.]][[<<<[+++][]]]";
	const std::string balancedCodeLine2 = "[[[][[][][]]]]";

public:
	InterpreterUnitTest(const std::string& filePath) : Interpreter(filePath) {}
	~InterpreterUnitTest() = default;

	/// <summary>
	/// Ensure all open brackets have an close bracket
	/// </summary>
	/// <param name="ii">- Current line that is being read</param>
	/// <returns>True if found the closing bracket</returns>
	void isBalanced(void);

	/// <summary>
	/// Go to the end of loop
	/// </summary>
	/// <param name="charIndex">- Starting char index</param>
	void goToEnd();
};