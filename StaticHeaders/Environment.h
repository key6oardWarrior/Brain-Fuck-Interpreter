#pragma once
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

class Environment {
private:
    std::vector<char> memoryPointer;
    std::vector<char>::iterator mp;

public:
    Environment() : memoryPointer(3000) {
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
    inline void incMP(void) { this->mp++; }

    /*
    * decrement the mp pointer
    */
    inline void decMP(void) { this->mp--; }

    /*
    * @param userLetter - set user input to *mp
    */
    inline void userInput(const char& userLetter) { *(this->mp) = userLetter; }

    /*
    * add 0x1 to *mp
    */
    inline void increment(void) { *(this->mp) += 0x1; }

    /*
    * subtract 0x1 from *mp
    */
    inline void decrement(void) { *(this->mp) -= 0x1; }
};

#endif // !ENVIRONMENT_H
