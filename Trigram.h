#ifndef TRIGRAM
#define TRIGRAM

#include <unordered_map>

class Trigram {
private:
    // store a key-value pair corresponding of the succeding character (a-z) to its count of occurence
    std::unordered_map<char, int> suceedingCharFreq;

public:
    Trigram();

    // increment the conrresponding count of the given char
    void addToMap(char ch);

    // get the three suceeding characters that have the highest probability of occuring
    void getTopThreeChars(char* topThree);
};

#endif