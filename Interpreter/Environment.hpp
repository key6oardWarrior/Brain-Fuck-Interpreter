#pragma once
#include "pch.h"

class Environment {
private:
	unsigned short memory[0x752f];
	unsigned short memoryIndex = 0;

public:
	const unsigned short end = 0x752f;

	Environment(void) { std::fill_n(memory, end, 0); }
	~Environment() = default;

	/// <summary>
	/// </summary>
	/// <returns>The current memoryIndex</returns>
	unsigned short getMemIdx(void) const {
		return memoryIndex;
	}

	/// <summary>
	/// </summary>
	/// <returns>The memory stored at memoryIndex</returns>
	unsigned short getMemoryAtCurrentIdx(void) const {
		return memory[memoryIndex];
	}

	/// <summary>
	/// Increment the memoryPointer pointer
	/// </summary>
	void incMemPtr(void) { ++memoryIndex; }

	/// <summary>
	/// ecrement the memoryPointer pointer
	/// </summary>
	void decMemPtr(void) { --memoryIndex; }

	/// <summary>
	/// </summary>
	/// <param name="userLetter">- set *memoryPointer to user input</param>
	void userInputChar(const char userLetter) {
		memory[memoryIndex] = userLetter;
	}

	/// <summary>
	/// If the user enters a std::string rather than a char then add each char
	/// to a memory block then move the next memory block
	/// </summary>
	/// <param name="userLetter">- set *memoryPointer to user input</param>
	void userInputString(const char userLetter) {
		memory[memoryIndex++] = userLetter;
	}

	/// <summary>
	/// Add 0x1 to *memoryPointer
	/// </summary>
	/// <param name=""></param>
	void increment(void) { ++memory[memoryIndex]; }

	/// <summary>
	/// Subtract 0x1 from *memoryPointer
	/// </summary>
	void decrement(void) { --memory[memoryIndex]; }
};