#pragma once
#include "pch.h"

struct Block {
	short value = 0;
	bool isMaxPositive = 0;
	bool isMaxNegative = 0;

	Block(void) = default;
	~Block() = default;
};

class Memory {
private:
	Block memory[30'000];
	unsigned short memoryIndex = 0;

public:
	const unsigned short end = 29'999;

	Memory(void) = default;
	~Memory() = default;

	/// <summary>
	/// </summary>
	/// <returns>The current memoryIndex</returns>
	unsigned short getMemIdx(void) const {
		return memoryIndex;
	}

	/// <summary>
	/// </summary>
	/// <returns>The memory stored at memoryIndex</returns>
	Block* getMemoryAtCurrentIdx(void) {
		return &memory[memoryIndex];
	}

	/// <summary>
	/// Increment the memoryIndex
	/// </summary>
	void incMemIdx(void) { ++memoryIndex; }

	/// <summary>
	/// decrement the memoryIndex
	/// </summary>
	void decMemIdx(void) { --memoryIndex; }

	/// <summary>
	/// </summary>
	/// <param name="userLetter">- set *memoryPointer to user input</param>
	void userInputChar(const char userLetter) {
		memory[memoryIndex].value = userLetter;
		memory[memoryIndex].isMaxPositive = (userLetter >= 127);
	}

	/// <summary>
	/// If the user enters a std::string rather than a char then add each char
	/// to a memory block then move the next memory block
	/// </summary>
	/// <param name="userLetter">- set *memoryPointer to user input</param>
	void userInputString(const char userLetter) {
		memory[memoryIndex].value = userLetter;
		memory[memoryIndex++].isMaxPositive = (userLetter >= 127);
	}

	/// <summary>
	/// Add 0x1 to *memoryPointer
	/// </summary>
	/// <param name=""></param>
	void increment(void) { ++memory[memoryIndex].value; }

	/// <summary>
	/// Subtract 0x1 from *memoryPointer
	/// </summary>
	void decrement(void) { --memory[memoryIndex].value; }

	friend class Results;
};