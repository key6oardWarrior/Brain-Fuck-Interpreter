#include "pch.h"
#include "Interperter.hpp"

void Interpreter::errorDescription(const char userChar, const size_t charIndex) const {
	std::cout << std::endl << "Error:" << std::endl;
	std::cout << "char: " << userChar << std::endl;
	std::cout << "line number: " << lineNum << std::endl;
	std::cout << "char index: " << charIndex << std::endl;
}

bool Interpreter::isBalanced(size_t ii) const {
	const size_t lineLength = codeLine.length();
	unsigned long long balance = 1;

	while(++ii < lineLength) {
		if(codeLine[ii] == '[') {
			++balance;
		} else if(codeLine[ii] == ']') {
			--balance;

			if(balance < 0)
				return 0;
		}
	}

	return balance == 0;
}

void Interpreter::goToEnd(size_t& charIndex) const {
	int cnt = 1;

	while(cnt > 0) {
		++charIndex;

		if(codeLine[charIndex] == '[')
			++cnt;
		else if(codeLine[charIndex] == ']')
			--cnt;
	}
}

ErrorMessage Interpreter::isSymbolLegal(void) {
	std::stack<size_t> loopIndexes;

	for(size_t ii = 0; ii < codeLine.length(); ++ii) {
		switch(codeLine[ii]) {
		// ignore whitespace
		case '\n':
			return ErrorMessage::noError;
		case '\t':
			continue;
		case ' ':
			continue;

		case '>': // forward pointer
			if(env->getMemIdx() != env->end) {
				env->incMemPtr();
			} else {
				errorDescription(codeLine[ii], ii);
				return ErrorMessage::stackOverFlow;
			}
			break;

		case '<': // backward pointer
			if(env->getMemIdx() != 0) {
				env->decMemPtr();
			} else {
				errorDescription(codeLine[ii], ii);
				return ErrorMessage::stackOverFlow;
			}
			break;

		case '+': // increment
			if(isMaxPositive) {
				errorDescription(codeLine[ii], ii);
				return ErrorMessage::integerOverFlow;
			}

			isMaxNegative = 0;
			env->increment();

			if(env->getMemIdx() == maxInt)
				isMaxPositive = 1;
			break;

		case '-': // decrement
			if(isMaxNegative) {
				errorDescription(codeLine[ii], ii);
				return ErrorMessage::integerOverFlow;
			}

			isMaxPositive = 0;
			env->decrement();

			if(env->getMemIdx() == minInt) 
				isMaxNegative = 1;
			break;

		case '.': // print
		{
			const char mp = env->getMemoryAtCurrentIdx();

			if(isprint(mp))
				std::cout << mp;
			else
				std::cout << "0x" << std::hex << abs(mp) << std::endl;
			break;
		}

		case ',': // user input
		{
			std::string userLetters;
			std::getline(std::cin, userLetters);

			if(userLetters.length() > 1) {
				for(char i : userLetters) {
					env->userInputString(i);
				}
			} else {
				env->userInputChar(userLetters[0]);
			}
			break;
		}

		case '[': // start loop
			if(isSameLine == 0) {
				if(isBalanced(ii) == 0) {
					errorDescription(codeLine[ii], ii);
					return ErrorMessage::unmatchedBrackets;
				}

				isSameLine = 1;
			}

			if(env->getMemoryAtCurrentIdx() == 0x0) {
				goToEnd(ii);
				break;
			}

			loopIndexes.push(ii);
			break;

		case ']': // end loop
			if(isSameLine == 0) {
				errorDescription(codeLine[ii], ii);
				return ErrorMessage::unmatchedBrackets;
			}

			if(env->getMemoryAtCurrentIdx() != 0x0) {
				ii = loopIndexes.top();
			} else if(loopIndexes.size() > 0) {
				loopIndexes.pop();
			}
			break;

		default: // any other char
			errorDescription(codeLine[ii], ii);
			return ErrorMessage::invalidSymbol;
		}
	}
	return ErrorMessage::noError;
}

ErrorMessage Interpreter::interpret(void) {
	ErrorMessage errorMsg = ErrorMessage::noError;

	if(code.is_open()) {
		while((code.eof() == 0) && (errorMsg == ErrorMessage::noError)) {
			std::getline(code, codeLine);
			errorMsg = isSymbolLegal();
			isSameLine = 0;
			++lineNum;
		}
	} else {
		return ErrorMessage::codeNotOpen;
	}

	return errorMsg;
}

void Interpreter::main(void) {
	ErrorMessage message = Interpreter::interpret();
	std::cout << std::endl;

	switch(message) { // display error message
	case ErrorMessage::noError:
		std::cout << "code exited with error code 0." << std::endl;
		break;
	case ErrorMessage::codeNotOpen:
		std::cout << "code exited with error code 1: file could not be opened." << std::endl;
		break;
	case ErrorMessage::invalidSymbol:
		std::cout << "code exited with error code 2: invalid symbol." << std::endl;
		break;
	case ErrorMessage::unmatchedBrackets:
		std::cout << "code exited with error code 3: unmatched brackets." << std::endl;
		break;
	case ErrorMessage::stackOverFlow:
		std::cout << "code exited with error code 4: Stack overflow occurred." << std::endl;
		break;
	case ErrorMessage::integerOverFlow:
		std::cout << "code exited with error code 5: Integer overflow occurred." << std::endl;
	}
}