#include "pch.h"
#include "Headers\BrainfuckInterpreter.hpp"

int main(int argc, char** argv) {
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
