#include "Editor.h"

#include <windows.h>
#include <iostream>

using namespace std;

Editor::Editor()
{
    font.loadFromFile("resources/Lato-Regular.ttf");

    t_logo.setFont(font);
    t_logo.setString("Patafour Creator");
    t_logo.setCharacterSize(60);
    t_logo.setFillColor(sf::Color::Black);

    t_newfile.setFont(font);
    t_newfile.setString("New file");
    t_newfile.setCharacterSize(40);
    t_newfile.setFillColor(sf::Color::Black);

    t_loadfile.setFont(font);
    t_loadfile.setString("Load file");
    t_loadfile.setCharacterSize(40);
    t_loadfile.setFillColor(sf::Color::Black);

    t_curframes.setFont(font);
    t_curframes.setCharacterSize(40);
    t_curframes.setFillColor(sf::Color::Black);

    r_outline.setOutlineThickness(2);
    r_outline.setFillColor(sf::Color(0,0,0,0));
    r_outline.setOutlineColor(sf::Color::Black);

    view.setSize(1280,720);
}

string Editor::OpenArchiveFile()
{
    char filename[MAX_PATH];

    OPENFILENAME ofn;
    ZeroMemory(&filename, sizeof(filename));
    ZeroMemory(&ofn,      sizeof(ofn));
    ofn.lStructSize  = sizeof( ofn );
    ofn.hwndOwner    = NULL;  // If you have a window to center over, put its HANDLE here
    ofn.lpstrFilter  = "Patafour Archive Format\0*.P4A\0";
    ofn.lpstrFile    = filename;
    ofn.nMaxFile     = MAX_PATH;
    ofn.lpstrTitle   = "Select a file";
    ofn.Flags        = OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA( &ofn ))
    {
        std::cout << "You chose the file \"" << filename << "\"\n";
    }
    else
    {
        switch (CommDlgExtendedError())
        {
            default                    : std::cout << "You cancelled.\n";
            return "";
        }
    }

    return string(filename);
}


string Editor::OpenFile()
{
    char filename[MAX_PATH];

    OPENFILENAME ofn;
    ZeroMemory(&filename, sizeof(filename));
    ZeroMemory(&ofn,      sizeof(ofn));
    ofn.lStructSize  = sizeof( ofn );
    ofn.hwndOwner    = NULL;  // If you have a window to center over, put its HANDLE here
    ofn.lpstrFilter  = "All files\0*.*\0";
    ofn.lpstrFile    = filename;
    ofn.nMaxFile     = MAX_PATH;
    ofn.lpstrTitle   = "Select a file";
    ofn.Flags        = OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA( &ofn ))
    {
        std::cout << "You chose the file \"" << filename << "\"\n";
    }
    else
    {
        switch (CommDlgExtendedError())
        {
            default                    : std::cout << "You cancelled.\n";
            return "";
        }
    }

    return string(filename);
}

void Editor::Draw(sf::RenderWindow& window)
{
    if(state == 0)
    {
        t_logo.setOrigin(t_logo.getGlobalBounds().width/2,t_logo.getGlobalBounds().height/2);
        t_logo.setPosition(window.getSize().x/2,25);

        window.draw(t_logo);

        t_newfile.setOrigin(t_newfile.getGlobalBounds().width/2,t_newfile.getGlobalBounds().height/2);
        t_newfile.setPosition(window.getSize().x/2,120);

        t_newfile.setFillColor(sf::Color::Black);

        if(mouseX > t_newfile.getPosition().x-t_newfile.getGlobalBounds().width/2)
        {
            if(mouseX < t_newfile.getPosition().x+t_newfile.getGlobalBounds().width/2)
            {
                if(mouseY > t_newfile.getPosition().y-t_newfile.getGlobalBounds().height/2+10)
                {
                    if(mouseY < t_newfile.getPosition().y+t_newfile.getGlobalBounds().height/2+10)
                    {
                        t_newfile.setFillColor(sf::Color::Green);

                        if(mouseLeftClick == true)
                        {
                            state = 1;
                        }
                    }
                }
            }
        }

        t_loadfile.setOrigin(t_loadfile.getGlobalBounds().width/2,t_loadfile.getGlobalBounds().height/2);
        t_loadfile.setPosition(window.getSize().x/2,200);

        t_loadfile.setFillColor(sf::Color::Black);

        if(mouseX > t_loadfile.getPosition().x-t_loadfile.getGlobalBounds().width/2)
        {
            if(mouseX < t_loadfile.getPosition().x+t_loadfile.getGlobalBounds().width/2)
            {
                if(mouseY > t_loadfile.getPosition().y-t_loadfile.getGlobalBounds().height/2+10)
                {
                    if(mouseY < t_loadfile.getPosition().y+t_loadfile.getGlobalBounds().height/2+10)
                    {
                        t_loadfile.setFillColor(sf::Color::Green);

                        if(mouseLeftClick == true)
                        {
                            archiveFile = OpenArchiveFile();

                            if(archiveFile != "")
                            {
                                state = 1;
                            }
                        }
                    }
                }
            }
        }

        window.draw(t_newfile);
        window.draw(t_loadfile);
    }

    if(state == 1)
    {
        p4a.ReadDictionary(archiveFile);
        state = 3;
    }

    if(state == 2)
    {
        string file1 = OpenFile();
        string file2 = OpenFile();
        string file3 = OpenFile();

        if(file1 != "")
        {
            p4a.LoadFile(file1);
            p4a.LoadFile(file2);
            p4a.LoadFile(file3);
            p4a.CreateDictionary();
            p4a.Debug_SaveDictionary("DebugArchive.P4A");
        }

        state = 0;
    }

    if(state == 3)
    {
        Button button_1;
        Button button_2;
        Button button_3;
        Button button_4;
        Button button_5;
        Button button_6;
    }
}
