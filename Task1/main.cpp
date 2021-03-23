#include <iostream>

#include "Editor.h"
using namespace std;

int main(int argc, char const *argv[]) {
    // Editor editor;
    // editor.loop();
    switch (argc) {
        case 1: {
            cout << "here" << endl;

            Editor editor;
            editor.loop();
            break;
        }

        //opening existing file
        case 2: {
            cout << "hered" << endl;
            Editor editor(argv[1]);
            editor.loop();
            break;
        }
    }

    return 0;
}
