#include "scanner.h"

// putback() puts its argument back into the Token_stream's buffer
void Token_stream::putback(Token t) {
    if (full) throw runtime_error("putback into a full buffer");
    buffer = t;   // copy t to buffer
    full = true;  // buffer is now full
}

Token Token_stream::get() {
    if (full) {        // do we already have a Token ready?
        full = false;  // remove token from buffer
        return buffer;
    }
    char ch;
    cin.get(ch);  // cin.get() does NOT skip whitespace
    while (isspace(ch)) {
        if (ch == '\n') return Token(EOL);
        cin.get(ch);
    }

    switch (ch) {
        case '=':
        case '&':
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
        case '*':
        case '%':
        case '^':
        case '?':
        case '/':
            return Token(ch);  // let each character represent itself
        default:
            //Checks whether a character is numeric character (0-9) or not
            if (isdigit(ch)) {
                string s;
                s += ch;
                while (cin.get(ch) && isdigit(ch)) s += ch;
                cin.unget();
                //	return Token(number, stoi(s));
                return Token(NUM, stoi(s));
            }
            //Checks whether a character is an alphabet (a to z and A-Z) or not.
            if (isalpha(ch) || ch == '_') {
                string s;
                s += ch;
                while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
                cin.unget();
                if (s == "else") return Token(ELSE, s);
                if (s == "if") return Token(BOOL);
                if (s == "int") return Token(INT);
                if (regex_match(s, regex("[A-Za-z][A-Za-z0-9]*")))
                    return Token(ID, s);
                else
                    throw runtime_error("Illegal name");
            }
            throw runtime_error("Bad token");
    }
}
