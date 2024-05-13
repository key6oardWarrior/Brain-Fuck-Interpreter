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
			if(mem->getMemIdx() < mem->end) {
				mem->incMemIdx();
			} else {
				errorDescription(codeLine[ii], ii);
				return ErrorMessage::stackOverFlow;
			}
			break;

		case '<': // backward pointer
			if(mem->getMemIdx() > 0) {
				mem->decMemIdx();
			} else {
				errorDescription(codeLine[ii], ii);
				return ErrorMessage::stackOverFlow;
			}
			break;

		case '+': // increment
		{
			Block* block = mem->getMemoryAtCurrentIdx();

			if(block->isMaxPositive) {
				errorDescription(codeLine[ii], ii);
				return ErrorMessage::integerOverFlow;
			}

			block->isMaxNegative = 0;
			mem->increment();

			if(block->value >= maxInt)
				block->isMaxPositive = 1;

			block = nullptr;
			break;
		}

		case '-': // decrement
		{
			Block* block = mem->getMemoryAtCurrentIdx();

			if(block->isMaxNegative) {
				errorDescription(codeLine[ii], ii);
				return ErrorMessage::integerOverFlow;
			}

			block->isMaxPositive = 0;
			mem->decrement();

			if(block->value <= minInt)
				block->isMaxNegative = 1;

			block = nullptr;
			break;
		}

		case '.': // print
		{
			const char mp = mem->getMemoryAtCurrentIdx()->value;
			printedValues.emplace_back(mp);

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
					mem->userInputString(i);
				}
			} else {
				mem->userInputChar(userLetters[0]);
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

			if(mem->getMemoryAtCurrentIdx()->value == 0x0) {
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

			if(mem->getMemoryAtCurrentIdx()->value != 0x0) {
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

ErrorMessage Interpreter::startInterpreting() {
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

	return message;
}
