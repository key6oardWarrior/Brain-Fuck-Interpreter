#include "pch.h"

int main(void) {
    std::string fileName = "";

    std::cout << "What is the location and name of your file? ";
    std::getline(std::cin, fileName);

    if(fileName.substr(fileName.length()-3) != ".bf") {
        std::cout << "Error:" << std::endl;
        std::cout << "code exited with error code 6: File must be a Brainfuck (.bf) file." << std::endl;
        return 0;
    }

    Interpreter* bF = new Interpreter(fileName);
    bF->main();

    delete bF;
    bF = nullptr;

    system("pause");
    return 0;
}
