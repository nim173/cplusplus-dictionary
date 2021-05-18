#ifndef SIMPLE_DICTIONARY
#define SIMPLE_DICTIONARY

#include <unordered_map>
#include <string>
#include <set>
#include "Word.h"

using std::string;

class SimpleDictionary {
private:
    // a hash map or a unordere_map as it is called in the STL is used because it
    // has insert and search complexities of O(1) which is ideal for this use case
    std::unordered_map<string, Word*> words;
public:
    ~SimpleDictionary();

    bool loadDictionary(string fileName);

    // find the given word - task 1
    Word* findWord(string word);

    // finds the words with three or more occurences of the given character (eg- z) - task 2
    std::set<string> findWordsWithThreeOrMoreOccurencesOf(char c);

    // finds the words ending with the given string (eg - "ion") with the given minimum length (eg - 6) -  task 3
    std::set<string> findWordEndingWith(long unsigned int minLength, string str);
};

#endif
