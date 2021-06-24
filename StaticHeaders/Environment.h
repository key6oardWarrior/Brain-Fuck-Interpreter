#pragma once

class Environment {
private:
    std::vector<char> memory;
    std::vector<char>::iterator memoryPointer;

public:
    Environment(void) : memory(0x752f) {
        memoryPointer = memory.begin();
    }

public:
    /*
    * @return memoryPointer
    */
    std::vector<char>::iterator getMemPtr(void) const;

    /*
    * @return the end of memory
    */
    std::vector<char>::const_iterator getEnd(void) const;

    /*
    * @return the begining of memory
    */
    std::vector<char>::const_iterator getBegining(void) const;

    /*
    * increment the memoryPointer pointer
    */
    void incMemPtr(void) { memoryPointer++; }

    /*
    * decrement the memoryPointer pointer
    */
    void decMemPtr(void) { memoryPointer--; }

    /*
    * @param userLetter - set user input to *memoryPointer
    */
    void userInput(const char& userLetter) { *memoryPointer = userLetter; }
    
    /*
	* If the user enters a std::string rather than a char then add each
	* char to a memory block then move the next memory block
	* 
	* @param userLetter - set *memoryPointer to user input
	*/
	void userInputString(const char& userLetter) {
	    *memoryPointer = userLetter;
		++*memoryPointer;
	}

    /*
    * add 0x1 to *memoryPointer
    */
    void increment(void) { ++*memoryPointer; }

    /*
    * subtract 0x1 from *memoryPointer
    */
    void decrement(void) { --*memoryPointer; }
};
