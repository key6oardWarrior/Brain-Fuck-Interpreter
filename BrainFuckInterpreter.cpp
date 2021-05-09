#include "pch.h"
#include <stack>

void Interpreter::printErrorMessageDescription(const char& userChar, const int& charIndex) const {
    std::cout << std::endl << "Error:" << std::endl;
    std::cout << "char: " << userChar << std::endl;
    std::cout << "line number: " << lineNum << std::endl;
    std::cout << "char index: " << charIndex << std::endl;
}

bool Interpreter::isBalanced(int i) const {
    int balance = 1;

    do {
        i++;
        if(codeLine[i] == '[') {
            balance++;
        } else if(codeLine[i] == ']') {
            balance--;

			if(balance < 0) {
            	return 0;
        	}
        }
    } while(i < codeLine.length());

    return balance == 0;
}

void Interpreter::goToEnd(int& charIndex) const {
    int cnt = 1;

    while(cnt > 0) {
        charIndex++;
        if(codeLine[charIndex] == '[') {
            cnt++;
        } else if (codeLine[charIndex] == ']') {
            cnt--;
        }
    }
}

ErrorMessage Interpreter::isSymbolLegal(Environment& env) {
    std::stack<int> loopIndexes;

    for(int i = 0; i < codeLine.length(); i++) {
        switch(codeLine[i]) {
            case '\n': // ignore whitespace
                return ErrorMessage::noError;
            case '\t': // ignore whitespace
                continue;
            case ' ': // ignore whitespace
                continue;

            case '>': // forward pointer
                if(env.getMP() != env.endMemPtr()) {
                    env.incMP();
                } else {
                    printErrorMessageDescription(codeLine[i], i);
                    return ErrorMessage::stackOverFlow;
                }
                break;

            case '<': // backward pointer
                if(env.getMP() != env.beginMemPtr()) {
                    env.decMP();
                } else {
                    printErrorMessageDescription(codeLine[i], i);
                    return ErrorMessage::stackOverFlow;
                }
                break;

            case '+': // increment
                if(isMaxPositive) {
                    printErrorMessageDescription(codeLine[i], i);
                    return ErrorMessage::integerOverFlow;
                }
                isMaxNegative = 0;
                env.increment();

                if(*env.getMP() == maxInt) {
                    isMaxPositive = 1;
                }
                break;

            case '-': // decrement
                if(isMaxNegative) {
                    printErrorMessageDescription(codeLine[i], i);
                    return ErrorMessage::integerOverFlow;
                }
                isMaxPositive = 0;
                env.decrement();

                if(*env.getMP() == minInt) {
                    isMaxNegative = 1;
                }
                break;

            case '.': // print
                {
                    const char mp = *env.getMP();

                    if(isprint(mp)) {
                        std::cout << mp;
                    } else {
                        std::string prefix = (mp < 0) ? "-0x" : "0x";
                        std::cout << prefix << std::hex << abs(mp) << std::endl;
                    }
                }
                break;

            case ',': // user input
                char userLetter;
                
                std::cin >> userLetter;
                env.userInput(userLetter);
                break;

            case '[': // start loop
                if(isSameLine == 0) {
                    if(isBalanced(i) == 0) {
                        printErrorMessageDescription(codeLine[i], i);
                        return ErrorMessage::unmatchedBrackets;
                    }
                    isSameLine = 1;
                }

                if(*env.getMP() == 0x0) {
                    goToEnd(i);
                    break;
                }

                loopIndexes.push(i);
                break;

            case ']': // end loop
                if(isSameLine == 0) {
                    printErrorMessageDescription(codeLine[i], i);
                    return ErrorMessage::unmatchedBrackets;
                }

                if(*env.getMP() != 0x0) {
                    i = loopIndexes.top();
                } else if(loopIndexes.size() > 0) {
                    loopIndexes.pop();
                }
                break;

            default:
                printErrorMessageDescription(codeLine[i], i);
                return ErrorMessage::invalidSymbol;
        }
    }
    return ErrorMessage::noError;
}

ErrorMessage Interpreter::interpret() {
    Environment env;
    ErrorMessage errorMsg;

    if(code.is_open()) {
        do {
            std::getline(code, codeLine);
            errorMsg = isSymbolLegal(env);
            isSameLine = 0;
            lineNum++;
        } while((code.eof() == 0) && (errorMsg == ErrorMessage::noError));
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
            std::cout << "code exited with error code 1: Either file could not be opened or it does not exist." << std::endl;
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
        default:
            std::cout << "code exited with error code 5: Integer overflow occurred.";
    }
}