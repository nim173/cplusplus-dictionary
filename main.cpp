#include <iostream>
#include <string>
#include "SimpleDictionary.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

#define TASK_2_CHARACTER 'z'
#define TASK_3_MIN_LETTERS 6
#define TASK_3_SUFFIX "ion"
#define INPUT_ONE   "1"
#define INPUT_TWO   "2"
#define INPUT_THREE "3"
#define INPUT_FOUR  "4"
#define DICTIONARY_FILE_NAME "dictionary2021.txt"

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
                std::set<string> ret = dictionary.findWordEndingWith(TASK_3_MIN_LETTERS, TASK_3_SUFFIX);
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
         << "4. Quit" << endl
         << endl;    
}
