#ifndef WORD
#define WORD

#include <iostream>
#include <string>

using std::string;

class Word {
private:
    string word;
    string type;
    string definition;

public:
    Word();
    Word(string word, string type, string defintion);
    string getWord();
    string getType();
    string getDefinition();
    void setDefinition(string defintion);
    void printDefinition();
};

#endif 