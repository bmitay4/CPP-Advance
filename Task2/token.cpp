#include "token.h"

#include "tokenstrings.h"

tokenType Token::getType() {
    return this->type;
}
string Token::getText() {
    return this->text;
}
//Note that shared_ptr is virtual
shared_ptr<set<int>> varToken::getLines() {
    return this->lines;
}
void varToken::add_line(int l) {
    this->lines.get()->insert(l);
}
//If the word type value is less than 258, it will be printed as a character, otherwise the value name will be printed in enum
void Token::printToken() {
    if (type > 258) {
        int enum_idx = type - 258;
        cout << tokenStrings[enum_idx] << '\t' << text << endl;
    } else
        cout << (char)type << '\t' << text << endl;
}