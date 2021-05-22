#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include "SimpleDictionary.h"
#include "Word.h"
#include "Types.h"

SimpleDictionary::~SimpleDictionary() {
    // Get an iterator pointing to begining of the hashmap of words
    std::unordered_map<string, Word*>::iterator it = this->words.begin();
    // Iterate over the map using iterator
    while(it != this->words.end()) {
        delete it->second;
        ++it;
    }
}

bool SimpleDictionary::loadDictionary(string fileName) {
    bool ret = true;
    std::ifstream readFile;
    string line;
    readFile.open(fileName);

    if (readFile.good()) {
        while (std::getline(readFile, line) && ret) {
            // Used to split string around spaces.
            std::istringstream ss(line);
            string word;
            string type;
            ss >> word;
            ss >> type;

            if (type.length() > 2) {
                // remove first and last characters from the string i.e. the square brackets
                type = type.substr(1, type.size() - 2);

                // loading the defintion for the word
                string definition;
                if (std::getline(readFile, definition)) {
                    // add the loaded word to the hash map
                    Word *newWord = new Word(word, type, "");
                    newWord->setDefinition(definition);
                    this->words[word] = newWord;
                }
                else {
                    // definition not found
                    ret = false;
                }
            }
        }
    } else {
        // error loading file
        ret = false;
    }
    return ret;
}

Word* SimpleDictionary::findWord(string word){ 
    return this->words.at(word);
}

bool SimpleDictionary::checkIfWordExists(string word) {
    return (this->words.find(word) != this->words.end());
}

std::set<string> SimpleDictionary::findWordsWithThreeOrMoreOccurencesOf(char c){
    // a set is chosen here so that the words will be sorted
    std::set<string> ret;
    // Get an iterator pointing to begining of the hashmap of words
    std::unordered_map<string, Word*>::iterator it = this->words.begin();
    // Iterate over the map using iterator
    while(it != this->words.end()) {
        // count occurences of the given character
        int count = 0;
        for (long unsigned int i = 0; i < it->first.length(); ++i) {
            if (it->first[i] == std::tolower(c) || it->first[i] == std::toupper(c)) {
                ++count;
            }
        }
        // if three or more occurences of the given character found insert into set
        if (count >= 3) {
            ret.insert(it->first);
        }
        ++it;
    }
    return ret;
}

std::set<string> SimpleDictionary::findWordsEndingWith(long unsigned int minLength, string str){
    // a set is chosen here so that the words will be sorted
    std::set<string> ret;
    // Get an iterator pointing to begining of the hashmap of words
    std::unordered_map<string, Word*>::iterator it = this->words.begin();
    // Iterate over the map using iterator
    while(it != this->words.end()) {
        // check if word has the minimum length and is longer than the given string
        if (it->first.length() >= minLength && str.length() <= it->first.length()) { 
            // check if the given string matches the ending of the word
            if (it->first.substr(it->first.length() - str.length()) == str) {
                ret.insert(it->first);
            }
        }
        ++it;
    }
    return ret;
}

std::set<string> SimpleDictionary::findWordsBothNounAndVerb() {
    // a set is chosen here so that the words will be sorted
    std::set<string> ret;
    // Get an iterator pointing to begining of the hashmap of words
    std::unordered_map<string, Word*>::iterator it = this->words.begin();
    // Iterate over the map using iterator
    while(it != this->words.end()) {
        if(it->second->getType() == NOUN_AND_VERB) {
            ret.insert(it->first);
        }
        ++it;
    }
    return ret;
}

std::set<string> SimpleDictionary::findWordsStartingAndEndingWithSameTwoLetters() {
    // a set is chosen here so that the words will be sorted
    std::set<string> ret;
    // Get an iterator pointing to begining of the hashmap of words
    std::unordered_map<string, Word*>::iterator it = this->words.begin();
    // the length of the equal letters we are checking for
    int len = 2;
    // Iterate over the map using iterator
    while(it != this->words.end()) {
        string str = it->first;
        int strLength = str.length();
        if(strLength >= len*2 && str.substr(0, len).compare(str.substr(strLength-len, len)) == 0) {
            ret.insert(it->first);
        }
        ++it;
    }
    return ret;
}

std::set<string> SimpleDictionary::findAnagrams(string originalWord) {
    string sortedWord = originalWord;
    // sort the given word for comparison
    std::sort(sortedWord.begin(), sortedWord.end());
    // a set is chosen here so that the words will be sorted
    std::set<string> ret;
    // Get an iterator pointing to begining of the hashmap of words
    std::unordered_map<string, Word*>::iterator it = this->words.begin();
    // Iterate over the map using iterator
    string str = "";
    while(it != this->words.end()) {
        str = it->first;
        if(str.length() == sortedWord.length() && originalWord.compare(str) != 0) {
            std::sort(str.begin(), str.end());
            if (sortedWord.compare(str) == 0) {
                ret.insert(it->first);
            }
        }
        ++it;
    }
    return ret;
}

Word* SimpleDictionary::getRandomWord() {
    // Get an iterator pointing to begining of the hashmap of words
    std::unordered_map<string, Word*>::iterator it = this->words.begin();
    // initialize random seed
    srand (time(NULL));
    // Get a random number between 0 and the length of the map
    int randomNumber = rand() % this->words.size();
    // advance iterator to index of generated random number
    std::advance(it, randomNumber);
    return it->second;
}

