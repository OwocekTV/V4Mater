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

    t_curframes.setFont(font);
    t_curframes.setCharacterSize(40);
    t_curframes.setColor(sf::Color::Black);

    r_outline.setOutlineThickness(2);
    r_outline.setFillColor(sf::Color(0,0,0,0));
    r_outline.setOutlineColor(sf::Color::Black);

    obj_test.Load("head_1.png",max_frames);
    obj_test.setFrame(0);

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
        view.setCenter(camera_x,camera_y);
        window.setView(view);

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

            obj_test.setPos(frames);
        }

        if(keyMap[sf::Keyboard::Right] == true)
        {
            frames += 1;

            if(frames > max_frames)
            frames = 0;

            obj_test.setPos(frames);
        }

        if(play == true)
        {
            f_frames += float(60) / fps;

            if(f_frames > max_frames)
            {
                f_frames = 0;
            }

            frames = floor(f_frames);

            obj_test.setPos(frames);
        }

        if(keyMap[sf::Keyboard::R] == true)
        {
            obj_test.setFrame(frames);
        }

        if(mouseRightClick)
        {
            distance_x = RMB_x - mouseX;
            distance_y = RMB_y - mouseY;

            camera_x = oldcamera_x + distance_x;
            camera_y = oldcamera_y + distance_y;

            if(isRightClicked == false)
            {
                RMB_x = mouseX;
                RMB_y = mouseY;
                isRightClicked = true;
            }
        }
        else
        {
            camera_x = oldcamera_x + distance_x;
            camera_y = oldcamera_y + distance_y;

            distance_x = 0;
            distance_y = 0;

            oldcamera_x = camera_x;
            oldcamera_y = camera_y;

            isRightClicked = false;
        }

        int realMouseX = round(window.mapPixelToCoords(sf::Vector2i(mouseX,mouseY)).x);
        int realMouseY = round(window.mapPixelToCoords(sf::Vector2i(mouseX,mouseY)).y);

        if(realMouseX >= obj_test.x)
        {
            if(realMouseX <= obj_test.x+obj_test.s_object.getGlobalBounds().width)
            {
                if(realMouseY >= obj_test.y)
                {
                    if(realMouseY <= obj_test.y+obj_test.s_object.getGlobalBounds().height)
                    {
                        if(mouseLeftClick)
                        {
                            obj_test.selected = true;
                            obj_test.outline = true;
                        }
                    }
                }
            }
        }

        if(obj_test.selected == true)
        {
            if(mouseLeftClick)
            {
                Ldistance_x = realMouseX - LMB_x;
                Ldistance_y = realMouseY - LMB_y;

                //cout << "L: " << Ldistance_x << " " << Ldistance_y << endl;

                obj_test.x = obj_test.oldx + Ldistance_x;
                obj_test.y = obj_test.oldy + Ldistance_y;

                if(isLeftClicked == false)
                {
                    LMB_x = realMouseX;
                    LMB_y = realMouseY;

                    isLeftClicked = true;
                }
            }
            else
            {
                obj_test.x = obj_test.oldx + Ldistance_x;
                obj_test.y = obj_test.oldy + Ldistance_y;

                Ldistance_x = 0;
                Ldistance_y = 0;

                obj_test.oldx = obj_test.x;
                obj_test.oldy = obj_test.y;

                obj_test.selected = false;
                isLeftClicked = false;
            }
        }

        /*sf::Vector2f curPos = obj_test.s_object.getPosition();
        sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        const float PI = 3.14159265;

        float dx = curPos.x - position.x;
        float dy = curPos.y - position.y;

        float rotation = (atan2(dy, dx)) * 180 / PI;

        float rotation2 = rotation;
        if(rotation < 0)
        rotation2 = 180+(180+rotation);
        cout << rotation2 << endl;

        obj_test.s_object.setRotation(rotation);*/

        obj_test.Draw(window);

        auto def = window.getDefaultView();
        window.setView(def);

        t_curframes.setString("Frame "+to_string(int(frames)));
        window.draw(t_curframes);
    }
}
