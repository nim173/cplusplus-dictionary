#include <iostream>
#include "Word.h"
#include "Types.h"

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
    return this->type;
}

string Word::getFormattedType() {
    string type;
    if (this->type == NOUN) {
        type = "Noun (n.)";
    } else if (this->type == VERB) {
        type = "Verb (v.)";
    } else if (this->type == ADVERB) {
        type = "Adverb (adv.)";
    } else if (this->type == ADJECTIVE) {
        type = "Adjective (adj.)";
    } else if (this->type == PREPOSITION) {
        type = "Preposition (prep.)";
    } else if (this->type == MISC_WORDS) {
        type = "MiscWords (misc.)";
    } else if (this->type == PROPER_NOUNS) {
        type = "ProperNouns (pn.)";
    } else if (this->type == NOUN_AND_VERB) {
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
    std::cout << getFormattedType() << std::endl
              << getDefinition() << std::endl;
}

void Word::setDefinition(string defintion) {
    this->definition = defintion;
}