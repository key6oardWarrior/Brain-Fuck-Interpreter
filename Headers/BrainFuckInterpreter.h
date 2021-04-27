#pragma once
#ifndef BrainFuckInterpreter_H
#define BrainFuckInterpreter_H

class Interpreter {
private:
    std::fstream code;
    std::string codeLine;
    int lineNum = 1;
    bool isSameLine = false;
    bool isMaxPositive = false;
    bool isMaxNegative = false;

public:
    /*
    * open the users file via std::fstream
    *
    * @param file path 
    */
    Interpreter(const std::string& filePath) { code.open(filePath); }
    ~Interpreter(void) {
        code.close();
        codeLine = "";
    }

private:
    /*
    * ensure all open brackets have an close bracket
    *
    * @param current line that is being read
    * @return true if found the closing bracket
    */
    bool isBalanced(int) const;

    /*
    * print the error message's char, char's index, and what line it is on
    *
    * @param the char that caused the error
    * @param which char on the line caused the error
    * @param the line that caused the error
    */
    void printErrorMessageDescription(const char&, const int&) const;

    /*
    * determin if the symbol in the bf file is legal
    * if it is then carry out instructions
    * else return int that correlates to enum class ErrorMessage
    *
    * @param memory for the bf program
    * @param keep track of the bf code's line number
    * @return the error code to be displayed
    */
    ErrorMessage isSymbolLegal(Environment&);

    /*
    * interpret code in a bf file
    *
    * @return ErrorMessage
    */
    ErrorMessage interpret(void);

public:
    /*
    * display error message or display error code 0
    */
    void main(void);
};

#endif // !BrainFuckInterpreter_H
