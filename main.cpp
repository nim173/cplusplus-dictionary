#include <iostream>
#include <string>
#include "SimpleDictionary.h"
#include "Types.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

void show_menu();

int main(void) {
    SimpleDictionary dictionary;
    dictionary.loadDictionary(DICTIONARY_FILE_NAME);
    bool loop = true;
    string input;
    do {
        show_menu();
        cout << "> ";
        if (std::getline(cin, input)) {
            if (input == INPUT_ONE) {
                cout << endl
                     << "Enter word : ";
                string word;
                if (std::getline(cin, word)) {
                    try {
                        dictionary.findWord(word)->printDefinition();
                    } catch(const std::out_of_range &e) {
                        cout << "No result found for " << word << endl;
                    } 
                } else {
                    // return
                }
            } else if (input == INPUT_TWO) {
                std::set<string> ret = dictionary.findWordsWithThreeOrMoreOccurencesOf(TASK_2_CHARACTER);
                if (ret.size() == 0) {
                    cout << "0 results found" << endl;
                } else {
                    for (std::set<string>::iterator s = ret.begin(); s != ret.end(); s++) {                                                        
                        cout << endl << *s << endl;
                    }
                }
            } else if (input == INPUT_THREE) {
                std::set<string> ret = dictionary.findWordsEndingWith(TASK_3_MIN_LETTERS, TASK_3_SUFFIX);
                if (ret.size() == 0) {
                    cout << "0 results found" << endl;
                } else {
                    cout << endl;
                    for (std::set<string>::iterator s = ret.begin(); s != ret.end(); s++) {                                                        
                        cout << *s << ", ";
                    }
                    cout << endl;
                }
            } else if (input == INPUT_FOUR) {
                std::set<string> ret = dictionary.findWordsBothNounAndVerb();
                if (ret.size() == 0) {
                    cout << "0 results found" << endl;
                } else {
                    cout << endl;
                    for (std::set<string>::iterator s = ret.begin(); s != ret.end(); s++) {                                                        
                        cout << *s << ", ";
                    }
                    cout << endl;
                }
            } else if (input == INPUT_FIVE) {
                std::set<string> ret = dictionary.findWordsStartingAndEndingWithSameTwoLetters();
                if (ret.size() == 0) {
                    cout << "0 results found" << endl;
                } else {
                    cout << endl;
                    for (std::set<string>::iterator s = ret.begin(); s != ret.end(); s++) {                                                        
                        cout << *s << ", ";
                    }
                    cout << endl;
                }
            } else if (input == INPUT_SIX) {
                cout << endl
                     << "Enter word : ";
                string word;
                if (std::getline(cin, word) && word.compare("") != 0) {
                    std::set<string> ret = dictionary.findAnagrams(word);
                    if (ret.size() == 0) {
                        cout << "0 results found" << endl;
                    } else {
                        cout << endl;
                        for (std::set<string>::iterator s = ret.begin(); s != ret.end(); s++) {                                                        
                            cout << *s << ", ";
                        }
                        cout << endl;
                    }
                } else {
                    // return
                }
            } else if (input == INPUT_SEVEN) {
                // get random word
                Word* randomWord = dictionary.getRandomWord();
                int wordLength = randomWord->getWord().length();
        
                cout << "Definition: " << randomWord->getDefinition() << endl
                     << "Length: " << wordLength << endl;

                int repetitions = 0;
                if (wordLength <= NO_OF_TRIES_GUESSING_GAME) {
                    repetitions = wordLength;
                } else {
                    repetitions = NO_OF_TRIES_GUESSING_GAME;
                }

                bool loop = true;
                for (int i = 0; i < repetitions && loop; ++i) {
                    cout << endl
                         << "Guess the word : ";
                    string word;
                    if (loop && std::getline(cin, word)) {
                        if (word.compare(randomWord->getWord()) == 0) {
                            cout << endl << "You guessed correctly :)" << endl;
                            loop = false;
                        } else {
                            cout << "You guessed wrong" << endl << endl;
                            if (repetitions > i + 1) {
                                cout << "Hint: It starts with \"" << randomWord->getWord().substr(0, i + 1) << "\"" << endl
                                     << "You have " << repetitions - (i + 1) << " tries left" << endl;
                            } else {
                                cout << "Out of tries :(" << endl
                                     << "The word was: " << randomWord->getWord() << endl;
                                loop = false;
                            }
                        }
                    } else {
                        loop = false;
                    }
                }
            } else if (input == INPUT_EIGHT) {
                // quit
                cout << endl;
                loop = false;
            } else {
                cout << "Invalid input" << endl;
            }
        }  // if not EOF
        if (cin.eof()) {
            cout << endl
                 << "Goodbye" << endl
                 << endl;
            loop = false;
        }  // if EOF
    } while (loop);
    return EXIT_SUCCESS;
}

void show_menu() {
    cout << endl
         << "Menu" << endl
         << "----" << endl
         << "1. Find Word" << endl
         << "2. Display word(s) with more than three ‘z’s" << endl
         << "3. Display word(s) ending in ‘ion’ and contain at least six letters" << endl
         << "4. Display all words that are both a noun and a verb" << endl
         << "5. Display words that start and end with the same two letters" << endl
         << "6. Find anagrams of a word" << endl
         << "7. Guess the word" << endl
         << "8. Quit" << endl
         << endl;    
}
