#include "pch.h"

std::vector<char>::iterator Environment::getMP(void) const {
	return mp;
}

std::vector<char>::const_iterator Environment::endMemPtr(void) const {
	return memoryPointer.end();
}

std::vector<char>::const_iterator Environment::beginMemPtr(void) const {
	return memoryPointer.begin();
}
