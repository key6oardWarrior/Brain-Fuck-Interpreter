#include "pch.h"
#include "..\BrainFuckInterpreter\Headers\Environment.hpp"

unsigned short Environment::getMemIdx(void) const {
	return memoryIndex;
}

unsigned short const& Environment::getConstMemory(void) {
	return memory[memoryIndex];
}
