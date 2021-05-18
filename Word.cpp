#include <iostream>
#include "Word.h"

Word::Word() {
    
}

Word::Word(string word, string type, string defintion) {
    this->word = word;
    this->type = type;
    this->definition = definition;
}

string Word::getWord() {
    return this->word;
}

string Word::getType() {
    string type;
    if (this->type == "n") {
        type = "Noun (n.)";
    } else if (this->type == "v") {
        type = "Verb (v.)";
    } else if (this->type == "adv") {
        type = "Adverb (adv.)";
    } else if (this->type == "adj") {
        type = "Adjective (adj.)";
    } else if (this->type == "prep") {
        type = "Preposition (prep.)";
    } else if (this->type == "misc") {
        type = "MiscWords (misc.)";
    } else if (this->type == "pn") {
        type = "ProperNouns (pn.)";
    } else if (this->type == "n.v.") {
        type = "NounAndVerb (n.v.)";
    } else {
        type = "Unknown type";
    }
    return type;
}

string Word::getDefinition() {
    return this->definition;
}

void Word::printDefinition() {
    std::cout << getType() << std::endl
              << getDefinition() << std::endl;
}

void Word::setDefinition(string defintion) {
    this->definition = defintion;
}