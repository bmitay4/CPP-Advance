
#include "symtab.h"

//Optional USE
size_t get_next_t(string s) {
    return s.find('\t');
}
string subs(int begin, int end, string s) {
    if (begin == -1)
        return s.substr(get_next_t(s) + end);
    else
        return s.substr(begin, get_next_t(s) + end);
}

void SymbolTable::initReserved() {
    string line;
    ifstream file("reserved.txt");
    while (getline(file, line)) {
        if (line != "") {
            string text = line.substr(0, line.find('\t'));

            int num_t = stoi(line.substr(line.find('\t') + 1));
            tokenType type = static_cast<tokenType>(num_t);
            shared_ptr<Token> token = make_shared<Token>(type, text);
            insertToken(text, token);
        }
    }
    file.close();
}

shared_ptr<Token> SymbolTable::lookupToken(string text) {
    return symMap[text];
}

void SymbolTable::insertToken(string text, shared_ptr<Token> tokenp) {
    symMap.insert(pair<string, shared_ptr<Token>>(text, tokenp));
}

void SymbolTable::xref() {
    for (auto& i : symMap) {
        shared_ptr<Token> token = i.second;
        if (token->getType() == IDENTIFIER) {
            cout << i.first << "\t";

            shared_ptr<set<int>> lines = token->getLines();
            set<int>::iterator it;
            for (it = lines->begin(); it != lines->end(); ++it) cout << *it << " ";
            cout << endl;
        }
    }
}