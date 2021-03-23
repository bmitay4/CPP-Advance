#include "Document.h"

#include <bits/stdc++.h>

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#define FORWARD 1
#define BACKWARD 0
#define TRUE 1
#define FALSE 0

using namespace std;

Document::Document() {
    // cout << "Document created" << endl;
    currentline = 0;
    direction = FORWARD;
    multi_values = FALSE;
}

Document::~Document() {
    // cout << "Document Destructor Called" << endl;
}

//Determines the direction of adding rows after the current row
void Document::def_a() {
    direction = FORWARD;
}
//Determines the direction of adding rows before the current row
void Document::def_i() {
    direction = BACKWARD;
}
//Delete the current line
void Document::def_d() {
    body.erase(body.begin() + (currentline - 1));
    currentline--;
}
//Replaces the current line with another
void Document::def_c() {
    body.erase(body.begin() + (currentline - 1));
    currentline--;
    direction = FORWARD;
}
//Joins the current line to the next line (if it exists)
void Document::def_j(int value) {
    cout << value << endl;

    string first = body.at(currentline);
    cout << first << endl;

    string second = body.at(currentline + 1);
    cout << first << second << endl;
    body.erase(body.begin() + currentline);
    body.erase(body.begin() + currentline);
    body.insert(body.begin() + currentline, first + " " + second);
}
void Document::open_file(string file) {
    cout << currentline << endl;
    string line;
    ifstream myfile(file);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line.empty()) {
                cout << "blank" << endl;
            } else {
                vector<string>::iterator body_iterator = body.begin();
                body.insert(body_iterator + (currentline), line);
                currentline = currentline + 1;
            }
        }
        myfile.close();
    }
}
void Document::def_search_text(string line) {
    const string text = line.substr(1, line.length() - 2);
    cout << "Given word: " << text << endl;
    // cout << "Current vector line: " << body.at(currentline - 1) << endl;
    std::vector<string>::iterator it;
    // print();
    for (size_t i = currentline + 1; i < body.size(); i++) {
        if (body[i].find(text) != -1) {
            cout << "found!: " << body[i] << endl;
            currentline = i;
            return;
        }
    }
    cout << "Try to look again from the start" << endl;
    for (size_t i = 0; i < body.size(); i++) {
        if (body[i].find(text) != -1) {
            cout << "found!: " << body[i] << endl;
            currentline = i;
            return;
        }
    }

    // it = find(body.begin() + currentline, body.end(), text);
    // if (it != body.end()) {
    //     std::cout << "Element found at index: " << it - body.begin() + currentline << '\n';
    //     currentline = it - body.begin() + currentline;
    // } else {
    //     std::cout << "Element --NOT-- found in range:: " << currentline << " to " << body.size() << '\n';

    //     it = find(body.begin() + 1, body.begin() + currentline + 1, text);
    //     if (it != body.end()) {
    //         std::cout << "Element found in myvector second time! at index " << it - body.begin() + 1 << '\n';
    //         cout << body.at(it - body.begin()) << endl;
    //         currentline = it - body.begin() + 1;
    //     } else
    //         std::cout << "Element --NOT-- found in range:: " << 1 << " to " << currentline + 1 << '\n';
    // }
}
void Document::def_replace(string line) {
    std::stringstream test(line.substr(2));
    string segment;
    vector<string> seglist;

    while (std::getline(test, segment, '/')) {
        seglist.push_back(segment);
        // cout << segment << endl;
    }

    cout << body.at(currentline) << endl;
    cout << body.at(currentline).find(seglist.at(0)) << endl;
    if (body.at(currentline).find(seglist.at(0)) >= 0) {
        // cout << "i'm in" << endl;
        int length = seglist.at(0).length();
        body.at(currentline).replace(body.at(currentline).find(seglist.at(0)), length, seglist.at(1));
    }
    print();

    // cout << body.at(currentline) << endl;
}
void Document::set_currentline(int num) {
    while (num > body.size()) {
        body.push_back("");
    }
    currentline = num;
}
int Document::get_currentline() {
    return currentline;
}
void Document::set_EOF() {
    currentline = body.size();
}
void Document::text_parser(string line) {
    if (line.at(0) == '.') return;
    cout << "direction: " << direction << endl;
    vector<string>::iterator body_iterator = body.begin();
    if (direction == FORWARD) {
        // body.push_back(line);
        body.insert(body_iterator + (currentline), line);

        currentline = currentline + 1;
        cout << "currentline: " << currentline << endl;
    } else {
        if (multi_values == TRUE) {
            try {
                cout << 111 << endl;
                body.insert(body_iterator + (currentline), line);
                cout << 111 << endl;

            } catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
            }
        } else
            body.insert(body_iterator + (currentline - 1), line);
    }
    print();
}
//Save vector and contents to txt file on disk
void Document::write_to_file(string line) {
    string file_name = line.substr(2);
    ofstream output_file("./" + file_name);
    ostream_iterator<string> output_iterator(output_file, "\n");
    copy(body.begin(), body.end(), output_iterator);
    // cout << "File saved as: " << file_name << ".txt" << endl;
}
//Print function for debug purposes
void Document::print() {
    cout << "==print start==" << endl;
    for (std::vector<string>::const_iterator i = body.begin(); i != body.end(); ++i)
        std::cout << *i << '\n';
    cout << "==print end==" << endl;
}
void Document::set_multi_values(int num) {
    multi_values = num;
}
int Document::get_direction() {
    return direction;
}