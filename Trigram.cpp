#include "Trigram.h"

Trigram::Trigram() {
    // add a-z
    for (char i = 'a'; i <= 'z'; ++i) {        
        suceedingCharFreq[i] = 0;
    }
    // add space (i.e. end of word)
    suceedingCharFreq[' '] = 0;
}

void Trigram::addToMap(char ch) {
    int count = suceedingCharFreq[ch];
    suceedingCharFreq[ch] = ++count;
}

void Trigram::getTopThreeChars(char* topThree) {
    int first, second, third;
    char firstChar = ' ', secondChar = ' ', thirdChar = ' ';
 
    third = first = second = -1;
    std::unordered_map<char, int>::iterator it = this->suceedingCharFreq.begin();
    while(it != this->suceedingCharFreq.end()) {
        // If current element is greater than first
        if (it->second > first) {
            third = second;
            thirdChar = secondChar;

            second = first;
            secondChar = firstChar;

            first = it->second;
            firstChar = it->first;
        }

        // If arr[i] is in between first and second then update second
        else if (it->second > second) {
            third = second;
            thirdChar = secondChar;

            second = it->second;
            secondChar = it->first;
        }
 
        else if (it->second > third) {
            third = it->second;
            thirdChar = it->first;
        }
            
        ++it;
    };

    topThree[0] = firstChar;
    topThree[1] = secondChar;
    topThree[2] = thirdChar;
}