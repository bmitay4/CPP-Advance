#include "Editor.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

Editor::Editor() : document() {
    // cout << "Editor created" << endl;
    dot_typed = false;
}
Editor::Editor(string file) : document() {
    // cout << "Editor created" << endl;
    dot_typed = false;
    document.open_file(file);
}
Editor::~Editor() {
    // cout << "Editor Destructor Called" << endl;
}

//We'll using getline() to read a line from the CLI, and will act according to the token received
void Editor::loop() {
    // cout << "loop called" << endl;

    string currentline;
    while (true) {
        getline(cin, currentline);
        if (currentline == "q") {
            // cout << "exit" << endl;
            break;
        } else if (is_row_jump(currentline)) {
            // print("row wump");
            row_jump(currentline);
        } else if (is_write_file(currentline)) {
            // print("write to file");
            document.write_to_file(currentline);
        } else
            // print("editor");
            editor(currentline);
    }
}
void Editor::editor(string line) {
    // cout << "Current string: " << line << endl;
    // cout << "Current dot flag: " << dot_typed << endl;
    cout << "Current line index: " << document.get_currentline() << endl;

    if (dot_typed) {
        // cout << "Expect dot" << endl;
        document.text_parser(line);
        if (document.get_direction() == 0) {
            document.set_multi_values(1);
        }
        if (line == ".") {
            dot_typed = false;
            document.set_multi_values(0);
            if (document.get_direction() == 0)
                document.set_currentline(document.get_currentline() + 1);
        }
        return;
    }
    if (line == "a") {
        dot_typed = true;
        document.def_a();
        cout << document.get_currentline() << endl;
    } else if (line == "i") {
        dot_typed = true;
        document.def_i();
    } else if (line == "c") {
        dot_typed = true;
        document.def_c();
    } else if (line == "j") {
        document.def_j(document.get_currentline());
    } else if (line == "d")
        document.def_d();
    else if (line == ".") {
        dot_typed = false;
    } else if (is_row_jump(line)) {
        row_jump(line);
    } else if (is_search(line)) {
        cout << "search mode" << endl;
        document.def_search_text(line);
        cout << "current line after search: " << document.get_currentline() << endl;
    } else if (is_replace_old_new(line)) {
        cout << "replace mode" << endl;
        document.def_replace(line);
    }
}
bool Editor::is_search(string line) {
    return (line.at(0) == '/' && line.at(line.length() - 1) == '/');
}
bool Editor::is_replace_old_new(string line) {
    return line.at(0) == 's' && line.at(line.length() - 1) == '/' && (count(line.begin(), line.end(), '/') == 3);
}
void Editor::set_dot_flag(bool v) {
    dot_typed = v;
}
void Editor::row_jump(string line) {
    int givenline;
    if (is_digit(line)) {
        givenline = stoi(line);
        document.set_currentline(givenline);
        cout << "Current line is: " << line << endl;
    } else if (line[0] == '+') {
        givenline = document.get_currentline() + stoi(line.substr(1));
        document.set_currentline(givenline);
        cout << "Current line is: " << givenline << endl;
    } else if (line[0] == '-') {
        givenline = document.get_currentline() - stoi(line.substr(1));
        document.set_currentline(givenline);
        cout << "Current line is: " << givenline << endl;
    } else if (line == "$") {
        document.set_EOF();
        cout << "Current line is: " << document.get_currentline() << endl;
    }
}
bool Editor::is_row_jump(string line) {
    return (line.at(0) == '+' || line.at(0) == '-' || line.at(0) == '$' || is_digit(line.substr(0)));
}
bool Editor::is_write_file(string line) {
    return (line.at(0) == 'w' && line.at(1) == ' ');
}
bool Editor::is_digit(string line) {
    return line.find_first_not_of("0123456789") == std::string::npos;
}
void Editor::print(string str) {
    cout << str << endl;
}
bool Editor::is_editor(string line) {
    return (line == "\n" || line == "a" || line == "i" || line == "c" || line == "d" || line == "." || is_replace_old_new(line) || is_search(line));
}