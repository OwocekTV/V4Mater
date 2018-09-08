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
    t_logo.setColor(sf::Color::Black);

    t_newfile.setFont(font);
    t_newfile.setString("New file");
    t_newfile.setCharacterSize(40);
    t_newfile.setColor(sf::Color::Black);

    t_loadfile.setFont(font);
    t_loadfile.setString("Load file");
    t_loadfile.setCharacterSize(40);
    t_loadfile.setColor(sf::Color::Black);

    shape.setRadius(40);
    shape.setFillColor(sf::Color::Black);
    shape.setOrigin(shape.getGlobalBounds().width/2,shape.getGlobalBounds().height/2);
    shape.setPosition(500,500);

    t_curframes.setFont(font);
    t_curframes.setCharacterSize(40);
    t_curframes.setColor(sf::Color::Black);

    r_outline.setOutlineThickness(2);
    r_outline.setFillColor(sf::Color(0,0,0,0));
    r_outline.setOutlineColor(sf::Color::Black);
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
            case CDERR_DIALOGFAILURE   : std::cout << "CDERR_DIALOGFAILURE\n";   break;
            case CDERR_FINDRESFAILURE  : std::cout << "CDERR_FINDRESFAILURE\n";  break;
            case CDERR_INITIALIZATION  : std::cout << "CDERR_INITIALIZATION\n";  break;
            case CDERR_LOADRESFAILURE  : std::cout << "CDERR_LOADRESFAILURE\n";  break;
            case CDERR_LOADSTRFAILURE  : std::cout << "CDERR_LOADSTRFAILURE\n";  break;
            case CDERR_LOCKRESFAILURE  : std::cout << "CDERR_LOCKRESFAILURE\n";  break;
            case CDERR_MEMALLOCFAILURE : std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
            case CDERR_MEMLOCKFAILURE  : std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
            case CDERR_NOHINSTANCE     : std::cout << "CDERR_NOHINSTANCE\n";     break;
            case CDERR_NOHOOK          : std::cout << "CDERR_NOHOOK\n";          break;
            case CDERR_NOTEMPLATE      : std::cout << "CDERR_NOTEMPLATE\n";      break;
            case CDERR_STRUCTSIZE      : std::cout << "CDERR_STRUCTSIZE\n";      break;
            case FNERR_BUFFERTOOSMALL  : std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
            case FNERR_INVALIDFILENAME : std::cout << "FNERR_INVALIDFILENAME\n"; break;
            case FNERR_SUBCLASSFAILURE : std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
            default                    : std::cout << "You cancelled.\n";
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
            case CDERR_DIALOGFAILURE   : std::cout << "CDERR_DIALOGFAILURE\n";   break;
            case CDERR_FINDRESFAILURE  : std::cout << "CDERR_FINDRESFAILURE\n";  break;
            case CDERR_INITIALIZATION  : std::cout << "CDERR_INITIALIZATION\n";  break;
            case CDERR_LOADRESFAILURE  : std::cout << "CDERR_LOADRESFAILURE\n";  break;
            case CDERR_LOADSTRFAILURE  : std::cout << "CDERR_LOADSTRFAILURE\n";  break;
            case CDERR_LOCKRESFAILURE  : std::cout << "CDERR_LOCKRESFAILURE\n";  break;
            case CDERR_MEMALLOCFAILURE : std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
            case CDERR_MEMLOCKFAILURE  : std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
            case CDERR_NOHINSTANCE     : std::cout << "CDERR_NOHINSTANCE\n";     break;
            case CDERR_NOHOOK          : std::cout << "CDERR_NOHOOK\n";          break;
            case CDERR_NOTEMPLATE      : std::cout << "CDERR_NOTEMPLATE\n";      break;
            case CDERR_STRUCTSIZE      : std::cout << "CDERR_STRUCTSIZE\n";      break;
            case FNERR_BUFFERTOOSMALL  : std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
            case FNERR_INVALIDFILENAME : std::cout << "FNERR_INVALIDFILENAME\n"; break;
            case FNERR_SUBCLASSFAILURE : std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
            default                    : std::cout << "You cancelled.\n";
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

        t_newfile.setColor(sf::Color::Black);

        if(mouseX > t_newfile.getPosition().x-t_newfile.getGlobalBounds().width/2)
        {
            if(mouseX < t_newfile.getPosition().x+t_newfile.getGlobalBounds().width/2)
            {
                if(mouseY > t_newfile.getPosition().y-t_newfile.getGlobalBounds().height/2+10)
                {
                    if(mouseY < t_newfile.getPosition().y+t_newfile.getGlobalBounds().height/2+10)
                    {
                        t_newfile.setColor(sf::Color::Green);

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

        t_loadfile.setColor(sf::Color::Black);

        if(mouseX > t_loadfile.getPosition().x-t_loadfile.getGlobalBounds().width/2)
        {
            if(mouseX < t_loadfile.getPosition().x+t_loadfile.getGlobalBounds().width/2)
            {
                if(mouseY > t_loadfile.getPosition().y-t_loadfile.getGlobalBounds().height/2+10)
                {
                    if(mouseY < t_loadfile.getPosition().y+t_loadfile.getGlobalBounds().height/2+10)
                    {
                        t_loadfile.setColor(sf::Color::Green);

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
        if(mouseRightClick == true)
        {
            if(isAlreadyClicked == false)
            {
                RMB_x = mouseX;
                RMB_y = mouseY;

                isAlreadyClicked = true;
            }
        }

        if(isAlreadyClicked == true)
        {
            x_distance = RMB_x - mouseX;
            y_distance = RMB_y - mouseY;

            shape.setPosition(shape_x-x_distance+shape_ax,shape_y-y_distance+shape_ay);

            cout << "Distance moved: " << x_distance << " x " << y_distance << endl;
        }

        if(mouseRightClick == false)
        {
            shape_x = shape_x - x_distance;
            shape_y = shape_y - y_distance;

            x_distance = 0;
            y_distance = 0;

            isAlreadyClicked = false;
        }

        if(mouseLeftClick == true)
        {
            if(mouseX >= shape_x-shape.getGlobalBounds().width/2)
            {
                if(mouseX <= shape_x+shape.getGlobalBounds().width/2)
                {
                    if(mouseY >= shape_y-shape.getGlobalBounds().height/2)
                    {
                        if(mouseY <= shape_y+shape.getGlobalBounds().height/2)
                        {
                            cout << "Shape is clicked" << endl;
                            r_outline.setSize(sf::Vector2f(shape.getGlobalBounds().width,shape.getGlobalBounds().height));
                            r_outline.setOrigin(r_outline.getGlobalBounds().width/2,r_outline.getGlobalBounds().height/2);
                            r_outline.setPosition(shape_x+2,shape_y+2);

                            if(moveObject == false)
                            {
                                //shape.setOrigin(mouseX,mouseY);
                            }

                            moveObject = true;
                            selected = true;
                        }
                    }
                }
            }
        }

        if(selected == true)
        {
            r_outline.setSize(sf::Vector2f(shape.getGlobalBounds().width,shape.getGlobalBounds().height));
            r_outline.setOrigin(r_outline.getGlobalBounds().width/2,r_outline.getGlobalBounds().height/2);
            r_outline.setPosition(shape_x+2,shape_y+2);
        }

        if(moveObject == true)
        {
            shape_x = mouseX;
            shape_y = mouseY;

            shape.setPosition(shape_x-x_distance+shape_ax,shape_y-y_distance+shape_ay);

            if(mouseLeftClick == false)
            {
                shape.setOrigin(shape.getGlobalBounds().width/2,shape.getGlobalBounds().height/2);
                moveObject = false;
            }
        }

        window.draw(shape);
        window.draw(r_outline);

        if(keyMap[sf::Keyboard::Space] == true)
        {
            if(play == true)
            {
                play = false;
            }
            else
            {
                play = true;
            }
        }

        if(keyMap[sf::Keyboard::Left] == true)
        {
            frames -= 1;

            if(frames < 0)
            {
                frames = max_frames;
            }
        }

        if(keyMap[sf::Keyboard::Right] == true)
        {
            frames += 1;

            if(frames > max_frames)
            frames = 0;
        }

        if(play == true)
        {
            f_frames += float(60) / fps;

            if(f_frames > max_frames)
            {
                f_frames = 0;
            }

            frames = floor(f_frames);
        }

        t_curframes.setString("Frame "+to_string(int(frames)));
        window.draw(t_curframes);
    }
}
