#ifndef TRIGRAM_HANDLER
#define TRIGRAM_HANDLER

#include <string>
#include <unordered_map>
#include "Trigram.h"
#include "SimpleDictionary.h"

using std::string;

class TrigramHandler {
private:
    // store a key-value pair corresponding to two characters and possible preceding characters
    std::unordered_map<string, Trigram*> trigrams;

public:
    ~TrigramHandler();

    // load trigrams from a text document
    bool load(string fileName);

    // get the three suceeding characters that have the highest probability of occuring
    bool getTopThreeChars(string twoChars, char* topThree);

    // return 10 random words that sound like english words
    void getTenRandomWords(string twoChars, char* topThree, SimpleDictionary* dictionary, std::vector<string>* wordList);

    // recursively add random word to a list
    void getEnglishSoundingWordsReucursive(string word, std::vector<string>* wordList, SimpleDictionary* dictionary);
};

#endif