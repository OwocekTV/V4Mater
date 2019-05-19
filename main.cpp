#include <iostream>

#include "Engine/V4Creator.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "V4 Creator Initialize" << endl;
    cout << "Working directory: " << argv[0] << endl;

    string dir = argv[0];
    dir = dir.substr(0, dir.find_last_of("\\")+1);

    V4Creator V4;
    V4.editor.directory = dir;
    V4.Init();

    return 0;
}
