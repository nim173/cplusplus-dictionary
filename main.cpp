#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "SimpleDictionary.h"
#include "Types.h"
#include "TrigramHandler.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

void show_menu();

int main(void) {
    SimpleDictionary* dictionary = new SimpleDictionary();
    dictionary->loadDictionary(DICTIONARY_FILE_NAME);
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
                        dictionary->findWord(word)->printDefinition();
                    } catch(const std::out_of_range &e) {
                        cout << "No result found for " << word << endl;
                    } 
                } else {
                    // return
                }
            } else if (input == INPUT_TWO) {
                std::set<string> ret = dictionary->findWordsWithThreeOrMoreOccurencesOf(TASK_2_CHARACTER);
                if (ret.size() == 0) {
                    cout << "0 results found" << endl;
                } else {
                    for (std::set<string>::iterator s = ret.begin(); s != ret.end(); s++) {                                                        
                        cout << endl << *s << endl;
                    }
                }
            } else if (input == INPUT_THREE) {
                std::set<string> ret = dictionary->findWordsEndingWith(TASK_3_MIN_LETTERS, TASK_3_SUFFIX);
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
                std::set<string> ret = dictionary->findWordsBothNounAndVerb();
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
                std::set<string> ret = dictionary->findWordsStartingAndEndingWithSameTwoLetters();
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
                    std::set<string> ret = dictionary->findAnagrams(word);
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
                Word* randomWord = dictionary->getRandomWord();
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
                bool innerLoop = true;
                do {
                    cout << endl
                        << "Enter two characters (Enter 0 to exit): ";
                    string word;
                    if (std::getline(cin, word)) {
                        if (word.length() > 2) {
                            cout << "Too many characters. Try Again or enter 0 to exit." << endl;
                        } else if (word.length() < 2){
                            cout << "Invalid input. Try Again or enter 0 to exit." << endl;
                        } else if (word.compare("0") == 0){
                            innerLoop = false;
                        } else if (word.find_first_of("0123456789") != string::npos) {
                            cout << "Please enter only letters. Try Again or enter 0 to exit." << endl;
                        }
                        else {
                            // convert string to lower case
                            std::for_each(word.begin(), word.end(), [](char & c){
                                c = ::tolower(c);
                            });

                            // load trigrams with the dictionary and get top three most probable letters
                            TrigramHandler trigram;
                            trigram.load("dictionary2021.txt");

                            char topThree[3] = "";
                            if (!trigram.getTopThreeChars(word, topThree)) {
                                cout << endl << "No matches found!" << endl;
                            } else {
                                string temp;
                                cout << endl <<"The top three matches are: " << endl;
                                for (int i = 0; i < 3; ++i) {
                                    cout << "\t" << i+1 << ". ";
                                    if (topThree[i] == ' ') {
                                        temp = "_ (space - i.e. end of word)";
                                    } else {
                                        temp = topThree[i];
                                    }
                                    cout << temp << endl;
                                }

                                // get the random english sounding words
                                std::vector<string> *wordList = new std::vector<string>();
                                trigram.getEnglishSoundingWordsReucursive(word, wordList, dictionary);
                                size_t listSize = wordList->size();
                                cout << endl << listSize << " English-like words starting with '" << word << "': " << endl;
                                // print the random english sounding words
                                for (size_t i = 0; i < listSize; ++i) {
                                    cout << "\t" << i+1 << ". ";
                                    if (i != 10 - 1)
                                        cout << " ";
                                    cout << wordList->at(i) << endl;
                                }
                                delete wordList;
                            }
                            innerLoop = false;
                        }
                    } else {
                        loop = false;
                    }
                } while (innerLoop);
            } else if (input == INPUT_NINE) {
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
    delete dictionary;
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
         << "8. (Trigrams) Display the three most likely characters to occur after a given two characters" << endl
         << "   and 10 random english souding words starting with those two characters not in the dictionary" << endl
         << "9. Quit" << endl
         << endl;    
}
