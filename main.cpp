#include "pch.h"
#include "Headers\BrainfuckInterpreter.hpp"

int main(const int argc, const char** argv) {
	if(argc != 2) {
		std::cout << "Error:\n";
		std::cout << "code exited with code 7: Expected 1 command line argument, but got " << argc-1;
		return 0;
	}

	const std::string fileName = argv[1];

	if(fileName.substr(fileName.length() - 3) != ".bf") {
		std::cout << "Error:" << std::endl;
		std::cout << "code exited with error code 6: File must be a brain fuck (.bf) file." << std::endl;
		return 0;
	}

	Interpreter* bf = new Interpreter(fileName);
	bf->main();

	delete bf;
	bf = nullptr;

	system("pause");
	return 0;
}
