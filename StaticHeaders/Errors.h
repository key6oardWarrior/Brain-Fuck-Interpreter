#pragma once
#ifndef ERRORS_H
#define ERRORS_H

/**
* determin what error message to display
*/
enum class ErrorMessage {
    noError = 0,
    codeNotOpen = 1,
    invalidSymbol = 2,
    unmatchedBrackets = 3,
    stackOverFlow = 4,
    integerOverFlow = 5
};

#endif // !ERRORS_H
