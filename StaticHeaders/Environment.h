#pragma once
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

class Environment {
private:
    std::vector<char> memoryPointer;
    std::vector<char>::iterator mp;

public:
    Environment(void) : memoryPointer(0x752f) {
        mp = memoryPointer.begin();
    }

public:
    /*
    * @return mp
    */
    std::vector<char>::iterator getMP(void) const;

    /*
    * @return the end of memoryPointer
    */
    std::vector<char>::const_iterator endMemPtr(void) const;

    /*
    * @return the begining of memoryPointer
    */
    std::vector<char>::const_iterator beginMemPtr(void) const;

    /*
    * increment the mp pointer
    */
    void incMP(void) { mp++; }

    /*
    * decrement the mp pointer
    */
    void decMP(void) { mp--; }

    /*
    * @param userLetter - set user input to *mp
    */
    void userInput(const char& userLetter) { *mp = userLetter; }

    /*
    * add 0x1 to *mp
    */
    void increment(void) { ++*mp; }

    /*
    * subtract 0x1 from *mp
    */
    void decrement(void) { --*mp; }
};

#endif // !ENVIRONMENT_H