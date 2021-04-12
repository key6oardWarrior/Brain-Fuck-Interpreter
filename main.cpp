#include "pch.h"

int main(void) {
    std::string fileName = "";

    std::cout << "What is the location and name of your file? ";
    std::getline(std::cin, fileName);

    Interpreter* bF = new Interpreter(fileName);
    bF->main();

    delete bF;
    bF = nullptr;

    system("pause");
    return 0;
}
