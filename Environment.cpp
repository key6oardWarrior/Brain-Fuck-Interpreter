#include "pch.h"
#include "..\BrainFuckInterpreter\Headers\Environment.hpp"

unsigned short Environment::getMemIdx(void) const {
	return memoryIndex;
}

unsigned short Environment::getCopyMemory(void) {
	return memory[memoryIndex];
}

unsigned short& Environment::getRefMemory(void) {
	return memory[memoryIndex];
}

unsigned short const& Environment::getConstMemory(void) {
	return memory[memoryIndex];
}
