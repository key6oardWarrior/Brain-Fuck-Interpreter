#include "pch.h"
#include "Headers\BrainfuckInterpreter.h"

#include <stack>

inline void Interpreter::errorDescription(const char& userChar, const size_t& charIndex) const {
    std::cout << std::endl << "Error:" << std::endl;
    std::cout << "char: " << userChar << std::endl;
    std::cout << "line number: " << lineNum << std::endl;
    std::cout << "char index: " << charIndex + 1 << std::endl;
}

bool Interpreter::isBalanced(size_t i) const {
    const size_t lineLength = codeLine.length();
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
    } while(i < lineLength);

    return balance == 0;
}

void Interpreter::goToEnd(size_t& charIndex) const {
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

ErrorMessage Interpreter::isSymbolLegal(void) {
    std::stack<size_t> loopIndexes;

    for(size_t i = 0; i < codeLine.length(); i++) {
        switch(codeLine[i]) {
            // ignore whitespace
            case '\n':
                return ErrorMessage::noError;
            case '\t':
                continue;
            case ' ':
                continue;

            case '>': // forward pointer
                if(env->getMemPtr() != end) {
                    env->incMemPtr();
                } else {
                    errorDescription(codeLine[i], i);
                    return ErrorMessage::stackOverFlow;
                }
                break;

            case '<': // backward pointer
                if(env->getMemPtr() != begining) {
                    env->decMemPtr();
                } else {
                    errorDescription(codeLine[i], i);
                    return ErrorMessage::stackOverFlow;
                }
                break;

            case '+': // increment
                if(isMaxPositive) {
                    errorDescription(codeLine[i], i);
                    return ErrorMessage::integerOverFlow;
                }
                isMaxNegative = 0;
                env->increment();

                if(*env->getMemPtr() == maxInt) {
                    isMaxPositive = 1;
                }
                break;

            case '-': // decrement
                if(isMaxNegative) {
                    errorDescription(codeLine[i], i);
                    return ErrorMessage::integerOverFlow;
                }
                isMaxPositive = 0;
                env->decrement();

                if(*env->getMemPtr() == minInt) {
                    isMaxNegative = 1;
                }
                break;

            case '.': // print
                {
                    const char mp = *env->getMemPtr();

                    if(isprint(mp)) {
                        std::cout << mp;
                    } else {
                        const std::string prefix = (mp < 0) ? "-0x" : "0x";
                        std::cout << prefix << std::hex << abs(mp) << std::endl;
                    }
                }
                break;

            case ',': // user input
                char userLetter;
                
                std::cin >> userLetter;
                env->userInput(userLetter);
                break;

            case '[': // start loop
                if(isSameLine == 0) {
                    if(isBalanced(i) == 0) {
                        errorDescription(codeLine[i], i);
                        return ErrorMessage::unmatchedBrackets;
                    }
                    isSameLine = 1;
                }

                if(*env->getMemPtr() == 0x0) {
                    goToEnd(i);
                    break;
                }

                loopIndexes.push(i);
                break;

            case ']': // end loop
                if(isSameLine == 0) {
                    errorDescription(codeLine[i], i);
                    return ErrorMessage::unmatchedBrackets;
                }

                if(*env->getMemPtr() != 0x0) {
                    i = loopIndexes.top();
                } else if(loopIndexes.size() > 0) {
                    loopIndexes.pop();
                }
                break;

            default:
                errorDescription(codeLine[i], i);
                return ErrorMessage::invalidSymbol;
        }
    }
    return ErrorMessage::noError;
}

ErrorMessage Interpreter::interpret() {
    ErrorMessage errorMsg = ErrorMessage::noError;

    if(code.is_open()) {
        while((code.eof() == 0) && (errorMsg == ErrorMessage::noError)) {
            std::getline(code, codeLine);
            errorMsg = isSymbolLegal();
            isSameLine = 0;
            lineNum++;
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
            std::cout << "code exited with error code 5: Integer overflow occurred." << std::endl;
    }
}
