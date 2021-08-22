#include "scanner.h"

#include <regex>

/*
Sources:
https://stackoverflow.com/questions/39606576/
https://www.programcreek.com/cpp/?CodeExample=next+token
https://cpp.hotexamples.com/examples/-/-/getNextToken/cpp-getnexttoken-function-examples.html
https://stackoverflow.com/questions/57944133/

Many thanks to my dear wife for the assistance
*/

//Addon check if given char is a letter
static bool isLetter(char ch) {
    if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_')
        return true;

    return false;
}

shared_ptr<Token> Scanner::nextToken() {
    bool nxt_c = this->nextChar();
go_again:
    while (nxt_c && (ch == 13 || ch == ' ' || ch == '\n' || ch == '\t' || ch == '/')) {
        if (ch == '/') nxt_c = this->nextChar();
        if (ch == '*') {
            char prev = 0;
            while (this->nextChar()) {
                if (ch == '/' && prev == '*') break;
                prev = ch;
            }
            goto go_again;
        }

        if (ch == '/') {
            int curr = lineno;
            while (this->nextChar())
                if (curr != lineno) break;
            goto go_again;
        }
        nxt_c = this->nextChar();
    }

    string s = string(1, ch);
    this->nextChar();
    s = s + ch;
    if (s == "++")
        return make_shared<Token>(INC_OP, s);
    else if (s == "--")
        return make_shared<Token>(DEC_OP, s);
    else if (s == "->")
        return make_shared<Token>(PTR_OP, s);
    else if (s == "&&")
        return make_shared<Token>(AND_OP, s);
    else if (s == "||")
        return make_shared<Token>(OR_OP, s);
    else if (s == "<=")
        return make_shared<Token>(LE_OP, s);
    else if (s == ">=")
        return make_shared<Token>(GE_OP, s);
    else if (s == "==")
        return make_shared<Token>(EQ_OP, s);
    else if (s == "!=")
        return make_shared<Token>(NE_OP, s);

    //No need for next character
    inputFile.unget();
    inputFile.unget();
    this->nextChar();

    switch (ch) {
        case ';':
        case '{':
        case '}':
        case ',':
        case ':':
        case '(':
        case ')':
        case '[':
        case ']':
        case '~':
        case '&':
        case '*':
        case '%':
        case '^':
        case '?':
        case '/':
        case '=':
            return shared_ptr<Token>(new Token(static_cast<tokenType>(ch), string(1, ch)));
            break;
    }

    if (isdigit(ch) || ch == '-' || ch == '+' || ch == '.') {
        string num = string(1, ch);
        while (this->nextChar()) {
            if (isdigit(ch) || ch == 'e' || ch == 'E' || ch == '.')
                num = num + ch;
            else
                break;
        }
        inputFile.unget();
        if (num == ".") return shared_ptr<Token>(new Token(static_cast<tokenType>('.'), num));

        char* check_nxt_c;
        double d = strtod(num.c_str(), &check_nxt_c);
        if (*check_nxt_c)
            return make_shared<Token>(ERROR, num);
        else
            return make_shared<Token>(CONSTANT, num);
    }

    if (isLetter(ch)) {
        string word = string(1, ch);
        regex reg("^[_a-zA-Z]\\w*$");
        while (this->nextChar()) {
            if (!regex_match(word + ch, reg)) {
                shared_ptr<Token> new_token;
                new_token = symTab.lookupToken(word);
                if (new_token == nullptr) {
                    new_token = make_shared<varToken>(word);
                    symTab.insertToken(word, new_token);
                }
                new_token->add_line(lineno);

                inputFile.unget();
                return new_token;
            }
            word = word + ch;
        }
    }

    if (ch == '\'') {
        string s = string(1, ch);
        regex reg("\'[^\']\'");
        while (this->nextChar()) {
            s = s + ch;
            if (ch == '\'') break;
        }
        if (regex_match(s, reg))
            return make_shared<Token>(CONSTANT, s.substr(1, s.length() - 2));
        else
            return make_shared<Token>(ERROR, s.substr(1, s.length() - 2));
    }

    if (ch == '"') {
        string s = string(1, ch);
        regex reg("\"[^\"]*\"");
        while (this->nextChar()) {
            s = s + ch;
            if (ch == '"') break;
        }

        if (regex_match(s, reg))
            return make_shared<Token>(STRING_LITERAL, s.substr(1, s.length() - 2));
        else
            return make_shared<Token>(ERROR, s.substr(1, s.length() - 2));
    }
    //useless
    return nullptr;
}