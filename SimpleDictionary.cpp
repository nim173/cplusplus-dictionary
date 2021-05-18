#include <fstream>
#include <sstream>
#include <set>
#include "SimpleDictionary.h"
#include "Word.h"

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

std::set<string> SimpleDictionary::findWordEndingWith(long unsigned int minLength, string str){
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
