#pragma once

class InterpreterUnitTest : private Interpreter {
private:
	const std::string balancedCodeLine = "[[++]-- <<+-][[++--,.]][[<<<[+++][]]]";
	const std::string balancedCodeLine2 = "[[[][[][][]]]]";

	void resetMemory(void) {
		delete __super::mem;
		__super::mem = new Memory();
		__super::isSameLine = 0;
	}

public:
	InterpreterUnitTest(const std::string& filePath) : Interpreter(filePath) {}
	~InterpreterUnitTest() = default;

	/// <summary>
	/// Mock __super::isBalanced
	/// </summary>
	void isBalanced(void);

	/// <summary>
	/// Mock __super::goToEnd
	/// </summary>
	/// <param name="charIndex">- Starting char index</param>
	void goToEnd(void);

	/// <summary>
	/// Mock __super::isSymbolLegal
	/// </summary>
	void isSymbolLegal(void);
};