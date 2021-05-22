#include <fstream>
#include <algorithm>
#include <vector>
#include "TrigramHandler.h"
#include "Types.h"

TrigramHandler::~TrigramHandler() {
    std::unordered_map<string, Trigram*>::iterator it = this->trigrams.begin();
    while(it != this->trigrams.end()) {
        delete it->second;
        ++it;
    }
}

bool TrigramHandler::load(string fileName) {
    bool ret = true;
    std::ifstream readFile;
    readFile.open(fileName);

    if (readFile.good()) {
        string non_separator{"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"};
        string line;
        string word;
        Trigram* trigram = nullptr;
        while (std::getline(readFile, line) && ret) {
            size_t e,s=0;  
            do {
                s = line.find_first_of(non_separator,s);  // skip leading separators
                if (s==string::npos)                  // stop if no word left
                    break;
                e=line.find_first_not_of(non_separator, s);   // find next separator 
                string word(line.substr(s,e-s));      // construct the word
                s=e+1;                                // position after the separator
                
                int wordLength = word.length();
                // std::cout<<word<<std::endl;
                if (word.length() >= 2) {
                    // convert word to lower case
                    std::for_each(word.begin(), word.end(), [](char & c) {
                        c = ::tolower(c);
                    });
                    for (int i = 0; i < wordLength - 1; ++i) {
                        if (i == 0) {
                            // when the first character is a space (i.e. the start of a word)
                            string temp = " " + word[i];
                            trigram = this->trigrams[temp];
                            if (trigram == nullptr) {
                                trigram = new Trigram();
                                trigram->addToMap(word[i+1]);
                                this->trigrams[temp] = trigram;
                            } else {
                                trigram->addToMap(word[i+1]);
                            }
                            // std::cout << '_' << word[i] << word[i+1] << std::endl;
                        } 
                        if (i == wordLength - 2) {
                            // when the last character is a 'space' i.e. the end of the words
                            // this is used to generate the random word
                            trigram = this->trigrams[word.substr(i, 2)];
                            if (trigram == nullptr) {
                                trigram = new Trigram();
                                trigram->addToMap(' ');
                                this->trigrams[word.substr(i, 2)] = trigram;
                            } else {
                                trigram->addToMap(' ');
                            }
                            // std::cout << word.substr(i, 2) << '_' << std::endl;
                        } else {
                            trigram = this->trigrams[word.substr(i, 2)];
                            if (trigram == nullptr) {
                                trigram = new Trigram();
                                trigram->addToMap(word[i+2]);
                                this->trigrams[word.substr(i, 2)] = trigram;
                            } else {
                                trigram->addToMap(word[i+2]);
                            }
                            // std::cout << word.substr(i, 2) << word[i+2] << std::endl;
                        }
                    }
                } else {
                    // disregard words with length less than 3
                }
            } while (e!=string::npos);   
        }

    } else {
        // error loading file
        ret = false;
    }
    return ret;
}

bool TrigramHandler::getTopThreeChars(string twoChars, char* topThree) {
    bool result = false;
    if (this->trigrams[twoChars] != nullptr) {
        this->trigrams[twoChars]->getTopThreeChars(topThree);
        result = true;
    } else {
        // no matches found for the two characters, the combination is a rare one
    }
    return result;
}

void TrigramHandler::getEnglishSoundingWordsReucursive(string word, std::vector<string>* wordList, SimpleDictionary* dictionary) {
    char topThree[3];
    this->getTopThreeChars(word.substr(word.length()-2), topThree);

    for (int i = 0; i < 3 && wordList->size() < NUM_ENGLISH_SOUNDING_WORDS; ++i) {
        if (wordList->size() >= NUM_ENGLISH_SOUNDING_WORDS) {
            // end of word (i.e. after a space)
            return;
        } else if (topThree[i] == ' ') {
            // end of word (i.e. after a space)
            // go to next most probable character
            continue;
        } else {
            // add probable letter to the word
            string temp = word;
            // add the word if it doesn't already exist in the dictionary
            temp += topThree[i];
            if (!dictionary->checkIfWordExists(temp)) {
                wordList->push_back(temp);
                // this is done to cap the size of the words
                // if not, the same set of characters will be extended
                if (temp.length() > ENGLISH_SOUNDING_WORD_LENGTH_CAP) {
                    continue;
                }
            }
            // get next most probable letter
            this->getEnglishSoundingWordsReucursive(temp, wordList, dictionary);
        }
    }
}
