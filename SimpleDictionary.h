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

    bool checkIfWordExists(string word);

    // finds the words with three or more occurences of the given character (eg- z) - task 2
    std::set<string> findWordsWithThreeOrMoreOccurencesOf(char c);

    // finds the words ending with the given string (eg - "ion") with the given minimum length (eg - 6) -  task 3
    std::set<string> findWordsEndingWith(long unsigned int minLength, string str);

    // PART 2
    // find words that are both a noun and a verb (n_and_v)
    std::set<string> findWordsBothNounAndVerb();

    // find words that start and end with the same two letters (eg. “Photograph”)
    std::set<string> findWordsStartingAndEndingWithSameTwoLetters();

    // display all words that are anagrams of the given (non-null) word
    std::set<string> findAnagrams(string word);

    Word* getRandomWord();
};

#endif
