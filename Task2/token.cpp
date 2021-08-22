#include "token.h"

#include "iostream"
using namespace std;

void Token::printToken() {
    cout << type << "\t" << text << endl;
}