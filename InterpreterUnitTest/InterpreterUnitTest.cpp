#include "pch.h"
#include "InterpreterUnitTest.hpp"

void InterpreterUnitTest::isBalanced(void) {
	const std::string errMsg = "isBalanced is not working correctly";
	const std::string unBalancedCodeLine = "[[[][]";
	const std::string unBalancedCodeLine2 = "[";
	
	__super::codeLine = balancedCodeLine;
	assert((void(errMsg), __super::isBalanced(0)));
	__super::codeLine = balancedCodeLine2;
	assert((void(errMsg), __super::isBalanced(0)));

	__super::codeLine = unBalancedCodeLine;
	assert((void(errMsg), __super::isBalanced(0) == 0));
	__super::codeLine = unBalancedCodeLine2;
	assert((void(errMsg), __super::isBalanced(0) == 0));
}

void InterpreterUnitTest::goToEnd(void) {
	const std::string errMsg = "goToEnd is not working correctly";

	size_t charIdx = 0;
	__super::codeLine = balancedCodeLine;
	__super::goToEnd(charIdx);
	assert((void(errMsg), charIdx == 12));

	charIdx = 0;
	__super::codeLine = balancedCodeLine2;
	__super::goToEnd(charIdx);
	assert((void(errMsg), charIdx == balancedCodeLine2.length()-1));
}

void InterpreterUnitTest::isSymbolLegal(void) {
	const std::string errMsg = "isSymbolLegal is not working correctly";
	const std::string retErrMsg = "Did not return the right error message";

	__super::codeLine = balancedCodeLine;
	assert((void(errMsg), __super::isSymbolLegal() == ErrorMessage::noError));
	resetMemory();

	__super::codeLine = "";
	assert((void(errMsg), __super::isSymbolLegal() == ErrorMessage::noError));
	resetMemory();

	const std::string stackOverFlow = "<>+[]--";
	const std::string stackOverFlow2 = "+[>+].";
	const std::string unmatchedBrackets = ">>+[--]]+";
	const std::string unmatchedBrackets2 = ">>+[--][+";
	const std::string integerOverFlow = "+[--]";
	const std::string integerOverFlow2 = "+[+]";
	const std::string invalidSymbol = "++-[-1]++.";

	__super::codeLine = stackOverFlow;
	assert((void(retErrMsg), __super::isSymbolLegal() == ErrorMessage::stackOverFlow));
	assert((void("memoryIndex is not 0"), __super::mem->getMemIdx() == 0));
	resetMemory();

	__super::codeLine = stackOverFlow2;
	assert((void(retErrMsg), __super::isSymbolLegal() == ErrorMessage::stackOverFlow));
	assert((void("memoryIndex is not mem->end"), __super::mem->getMemIdx() == __super::mem->end));
	resetMemory();

	__super::codeLine = unmatchedBrackets;
	assert((void(retErrMsg), __super::isSymbolLegal() == ErrorMessage::unmatchedBrackets));
	resetMemory();

	__super::codeLine = unmatchedBrackets2;
	assert((void(retErrMsg), __super::isSymbolLegal() == ErrorMessage::unmatchedBrackets));
	resetMemory();

	__super::codeLine = integerOverFlow;
	assert((void(retErrMsg), __super::isSymbolLegal() == ErrorMessage::integerOverFlow));
	resetMemory();

	__super::codeLine = integerOverFlow2;
	assert((void(retErrMsg), __super::isSymbolLegal() == ErrorMessage::integerOverFlow));
	resetMemory();

	__super::codeLine = invalidSymbol;
	assert((void(retErrMsg), __super::isSymbolLegal() == ErrorMessage::invalidSymbol));
}