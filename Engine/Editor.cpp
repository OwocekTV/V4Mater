#include "Editor.h"

#include <windows.h>
#include <iostream>
#include <cmath>
#include "Button.h"

using namespace std;

Editor::Editor()
{
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
    if(buttons_loaded == false)
    {
        buttons[0].Load(1, directory);
        buttons[1].Load(2, directory);
        buttons[2].Load(3, directory);
        buttons[3].Load(4, directory);
        buttons[4].Load(5, directory);
        buttons[5].Load(6, directory);
        buttons[6].Load(7, directory);
        buttons[7].Load(8, directory);
        buttons[8].Load(9, directory);
        buttons[9].Load(10, directory);
        buttons[10].Load(12, directory);

        buttons_loaded = true;
    }

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
        /// /////////////////////////// ///
        /// ///////// Objects ///////// ///
        /// /////////////////////////// ///

        if(objects.size() > 0)
        {
            vector<int> objects_clicked;

            for(int i=0; i<objects.size(); i++)
            {
                if(mouseX > objects[i].x - objects[i].or_x)
                {
                    if(mouseX < objects[i].x + objects[i].or_x)
                    {
                        if(mouseY > objects[i].y - objects[i].or_y)
                        {
                            if(mouseY < objects[i].y + objects[i].or_y)
                            {
                                if(mouseLeftClick == true)
                                {
                                    objects_clicked.push_back(i);
                                }
                            }
                        }
                    }
                }

                ///Calculate object's position based on the timeline
                if(timeline_old != timeline.cur_pos)
                {
                    objects[i].SetPos(timeline.cur_pos);
                }

                objects[i].Draw(window);
            }

            timeline_old = timeline.cur_pos;

            //cout << "object_s: " << object_selected << endl;

            if(object_selected >= 0)
            {
                r_selected.setSize(sf::Vector2f(objects[object_selected].s_obj.getGlobalBounds().width,objects[object_selected].s_obj.getGlobalBounds().height));
                r_selected.setOrigin(sf::Vector2f(objects[object_selected].s_obj.getGlobalBounds().width/2,objects[object_selected].s_obj.getGlobalBounds().height/2));
                r_selected.setPosition(objects[object_selected].x,objects[object_selected].y);
                r_selected.setFillColor(sf::Color(0,0,0,0));
                r_selected.setOutlineColor(sf::Color::Black);
                r_selected.setOutlineThickness(2);

                window.draw(r_selected);
            }

            if((mouseLeftClick == true) && (object_clicked == false))
            {
                if(mouseX < window.getSize().x - 48)
                {
                    for(int i=0; i<objects_clicked.size(); i++)
                    {
                        if(highestLayer < objects[objects_clicked[i]].layer)
                        {
                            highestLayer = objects[objects_clicked[i]].layer;
                            highestIndex = objects_clicked[i];
                        }
                    }

                    cout << "Highest layer: " << highestLayer << " highest index: " << highestIndex << endl;

                    object_selected = highestIndex;
                    object_clicked = true;
                }
            }


            if((highestLayer >= 0) && (highestIndex >= 0))
            {
                if(object_clicked)
                {
                    if(object_selected >= 0)
                    {
                        if(allowMove)
                        {
                            if(!object_offset)
                            {
                                mX = objects[object_selected].x - mouseX;
                                mY = objects[object_selected].y - mouseY;

                                object_offset = true;
                            }

                            //cout << "mX: " << mX << " mY: " << mY << endl;

                            objects[object_selected].x = mouseX + mX;
                            objects[object_selected].y = mouseY + mY;

                            //cout << "X: " << objects[object_selected].x-640 << " Y: " << objects[object_selected].y-360 << endl;
                        }

                        if(allowRotate)
                        {
                            if(!object_offset)
                            {
                                mX = mouseX;
                                mY = mouseY;

                                object_offset = true;
                            }

                            ///Need to calculate rotation based on mouse position
                            float diff_x = mX - mouseX;
                            float diff_y = mY - mouseY;

                            if((abs(diff_x) >= 8) || (abs(diff_y) >= 8))
                            {
                                float PI = 3.14159265;
                                float n_rot = atan2(diff_y,diff_x) * 180 / PI;
                                float diff_rot = abs(oldrot) - abs(n_rot - 180);

                                cout << "dx: " << diff_x << " dy: " << diff_y << endl;

                                ///If a difference is too high (359 -> 0 or 0 -> 359) then detect it as an additional rotation ?????
                                ///Rotation anti-clockwise: diff is positive
                                ///Rotation clockwise: diff is negative

                                ///Unreliable solution for now!!!
                                if(diff_rot > 350)
                                {
                                    objects[object_selected].rs -= 1;
                                    cout << "Added -1 rotation" << endl;
                                }

                                if(diff_rot < -350)
                                {
                                    objects[object_selected].rs += 1;
                                    cout << "Added +1 rotation" << endl;
                                }

                                objects[object_selected].r = n_rot-180-mR;

                                oldrot = objects[object_selected].r;
                            }
                        }
                    }
                }
            }

            if((mouseX < window.getSize().x-48) && (mouseLeftClick == false))
            {
                object_clicked = false;
                object_offset = false;
                highestIndex = -1;
                highestLayer = -1;
            }
        }

        /// /////////////////////////// ///
        /// ///////// Resize ////////// ///
        /// /////////////////////////// ///

        if(isResized == true)
        {
            timeline.Create(max_time,window);

            for(int i=0; i<11; i++)
            {
                int add = 0;

                if(i > 4)
                add = 46;

                buttons[i].setPosition(window.getSize().x - 48, 46*i+add);
            }

            isResized = false;
        }

        /// /////////////////////////// ///
        /// ///////// Buttons ///////// ///
        /// /////////////////////////// ///

        for(int i=0; i<11; i++)
        {
            if(clickedOn == -1)
            {
                if(buttons[i].isClicked(mouseX,mouseY,mouseLeftClick))
                {
                    buttons[i].clickedOn = true;
                    clickedOn = i;
                }
                else
                {
                    buttons[i].clickedOn = false;
                }
            }

            if(clickedOn == i)
            {
                if(buttons[i].isHovered(mouseX,mouseY))
                {
                    if(mouseLeftClick == false)
                    {
                        cout << "Execute button " << i << endl;
                        switch(i)
                        {
                            case 5: ///Selection Tool
                            {
                                if(buttons[i].selected)
                                {
                                    buttons[i].setSelected(false);
                                    allowMove = false;
                                }
                                else
                                {
                                    buttons[i].setSelected(true);
                                    allowMove = true;
                                }

                                buttons[6].setSelected(false);

                                allowRotate = false;

                                break;
                            }

                            case 6: ///Rotation Tool
                            {
                                if(buttons[i].selected)
                                {
                                    buttons[i].setSelected(false);
                                    allowRotate = false;
                                }
                                else
                                {
                                    buttons[i].setSelected(true);
                                    allowRotate = true;
                                }

                                buttons[5].setSelected(false);

                                allowMove = false;

                                break;
                            }

                            case 7: ///Add object button
                            {
                                string tex_file = OpenFile();
                                Object tmp;
                                tmp.Load(tex_file, window.getSize().x/2,window.getSize().y/2);
                                tmp.layer = objects.size();
                                objects.push_back(tmp);

                                cout << "Added new object from " << tex_file << endl;

                                break;
                            }

                            case 9: ///Play/Stop button
                            {
                                if(playing)
                                {
                                    playing = false;

                                    buttons[5].setEnabled(true);
                                    buttons[6].setEnabled(true);
                                    buttons[7].setEnabled(true);
                                    buttons[8].setEnabled(true);
                                    buttons[10].setEnabled(true);

                                    buttons[i].Load(10, directory);
                                }
                                else
                                {
                                    playing = true;

                                    buttons[5].setEnabled(false);
                                    buttons[6].setEnabled(false);
                                    buttons[7].setEnabled(false);
                                    buttons[8].setEnabled(false);
                                    buttons[10].setEnabled(false);

                                    buttons[5].setSelected(false);
                                    buttons[6].setSelected(false);
                                    buttons[7].setSelected(false);
                                    buttons[8].setSelected(false);
                                    buttons[10].setSelected(false);

                                    allowMove = false;
                                    allowRotate = false;

                                    buttons[i].Load(11, directory);
                                }

                                break;
                            }

                            case 10:
                            {
                                cout << "Record frame at " << timeline.cur_pos << " object " << object_selected << endl;
                                objects[object_selected].SetFrame(timeline.cur_pos);
                                break;
                            }
                        }

                        clickedOn = -1;
                    }
                }

            }

            buttons[i].Draw(window);

        }

        /// /////////////////////////// ///
        /// ///////// Actions ///////// ///
        /// /////////////////////////// ///

        if(mouseLeftClick == false)
        {
            clickedOn = -1;
        }

        if(playing)
        {
            timeline.cur_pos += 1 / float(fps);

            if(timeline.cur_pos > max_time)
            {
                timeline.cur_pos = 0;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            max_time -= 0.01;

            if(max_time <= 0)
            max_time = 0.01;

            if(timeline.cur_pos >= max_time)
            timeline.cur_pos = max_time;

            timeline.Create(max_time,window);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            max_time += 0.01;

            timeline.Create(max_time,window);
        }

        timeline.max_time = max_time;
        timeline.mouseX = mouseX;
        timeline.mouseY = mouseY;
        timeline.mouseLeftClick = mouseLeftClick;
        timeline.Draw(window);
    }
}
