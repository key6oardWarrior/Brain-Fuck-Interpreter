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

void InterpreterUnitTest::goToEnd() {
	const std::string errMsg = "goToEnd is not working correctly";

	size_t charIdx = 0;
	__super::codeLine = balancedCodeLine;
	__super::goToEnd(charIdx);
	assert((void(errMsg), charIdx == 3));

	charIdx = 0;
	__super::codeLine = balancedCodeLine2;
	__super::goToEnd(charIdx);
	assert((void(errMsg), charIdx == balancedCodeLine2.length()-1));
}