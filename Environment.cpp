#include "pch.h"

std::vector<char>::iterator Environment::getMemPtr(void) const {
				return memoryPointer;
}

std::vector<char>::const_iterator Environment::getEnd(void) const {
				return memory.end();
}

std::vector<char>::const_iterator Environment::getBegining(void) const {
				return memory.begin();
}