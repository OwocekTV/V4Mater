#include "Editor.h"

#include <windows.h>
#include <iostream>
#include <cmath>
#include <sstream>
#include "Button.h"
#include "P4A.h"

using namespace std;

template <typename T>
std::string to_string_with_precision2(const T a_value, const int n = 2)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;

	std::stringstream ss(s);
	std::string item;
	while(std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}

	return elems;
}

Editor::Editor()
{
    view.setSize(1280,720);

    font.loadFromFile("resources/opensans.ttf");

    t_logo.setFont(font);
    t_newfile.setFont(font);
    t_loadfile.setFont(font);
    t_logo.setString("logo");
    t_newfile.setString("newfile");
    t_loadfile.setString("loadfile");
    t_logo.setFillColor(sf::Color::Black);
    t_newfile.setFillColor(sf::Color::Black);
    t_loadfile.setFillColor(sf::Color::Black);
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
        return "";
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

void Editor::saveAnim()
{
    ofstream anim(directory+"data.anim", ios::binary);

    ///Save header with version
    anim << "V4Mater-ver-1.00\n";

    ///Save initial animation settings
    anim << "S:" << to_string_with_precision2(max_time,6) << "\n";

    ///Save object creation
    for(int i=0; i<objects.size(); i++)
    {
        ///Check object type
        anim << "OI:" << objects[i].texture_path << "\n";
    }

    ///Save animation segments

    ///Frames
    for(int i=0; i<objects.size(); i++)
    {
        for(int f=0; f<objects[i].frames.size(); f++)
        {
            anim << "F:" << "animation_name," << to_string_with_precision2(objects[i].frames[f].time,6) << "," << to_string(i) << "," << objects[i].frames[f].pos_x << "," << objects[i].frames[f].pos_y << "," << objects[i].frames[f].rotation << "," << objects[i].frames[f].or_x << "," << objects[i].frames[f].or_y << "," << objects[i].frames[f].scale_x << "," << objects[i].frames[f].scale_y << "\n";
        }
    }

    anim.close();
}

void Editor::loadAnim(std::string data, P4A handle)
{
    bool legit = false;
    string version = "";

    istringstream iss(data);
    string line;
    while(getline(iss, line))
    {
        if(line.find("V4Mater-ver-") != std::string::npos)
        {
            version = line.substr(line.find_last_of("-")+1);
            legit = true;

            cout << "Anim format legit. Version " << version << endl;
        }

        /**
        [READ] V4Mater-ver-1.00
        [READ] S:9.799995
        [READ] OI:button_idle.png
        [READ] F:animation_name,0.000000,0,106,502,0,24,24,1,1
        [READ] F:animation_name,8.003246,0,1055,146,180.875,24,24,1,1
        */

        if(legit)
        {
            if(version == "1.00")
            {
                cout << "[READ " << version << "]: " << line << endl;

                if(line.find("S:") != std::string::npos)
                {
                    max_time = atof(line.substr(line.find_first_of(":")+1).c_str());
                    cout << "Time: " << max_time << endl;
                }

                if(line.find("OI:") != std::string::npos)
                {
                    string tex_file = line.substr(line.find_first_of(":")+1);
                    handle.Extract(tex_file);

                    Object tmp;
                    tmp.Load(tex_file,0,0);
                    tmp.layer = objects.size();
                    objects.push_back(tmp);

                    cout << "Added new object from " << tex_file << endl;
                }

                if(line.find("F:") != std::string::npos)
                {
                    string framedata = line.substr(line.find_first_of(":")+1);
                    vector<string> frame = split(framedata,',');

                    string animation_name = frame[0];

                    float time = atof(frame[1].c_str());
                    int objectID = atoi(frame[2].c_str());

                    float pos_x = atof(frame[3].c_str());
                    float pos_y = atof(frame[4].c_str());
                    float rotation = atof(frame[5].c_str());
                    float or_x = atof(frame[6].c_str());
                    float or_y = atof(frame[7].c_str());
                    float scale_x = atof(frame[8].c_str());
                    float scale_y = atof(frame[9].c_str());
                    objects[objectID].SetCustomFrame(time,pos_x,pos_y,or_x,or_y,rotation,scale_x,scale_y);
                }
            }
        }
    }

    for(int i=0; i<objects.size(); i++)
    {
        objects[i].SetPos(timeline.cur_pos);
    }
}

void Editor::saveFile(std::string path)
{
    saveAnim();

    P4A handle;
    handle.LoadFile(directory+"data.anim");
    for(int i=0; i<objects.size(); i++)
    {
        handle.LoadFile(objects[i].texture_path);
    }

    handle.SaveToFile(directory+"data.p4a");
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
        string animdata = p4a.ReadToMemory("data.anim");

        if(animdata == "")
        {
            cout << "Invalid animation file!" << endl;
            state = 0;
        }

        //cout << animdata << endl;
        loadAnim(animdata,p4a);

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
            p4a.SaveToFile("DebugArchive.P4A");
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
                                object_offset = true;
                            }

                            if(keyMap[sf::Keyboard::Up])
                            {
                                objects[object_selected].r -= float(60) / fps;
                            }

                            if(keyMap[sf::Keyboard::Down])
                            {
                                objects[object_selected].r += float(60) / fps;
                            }

                            cout << objects[object_selected].r << endl;
                        }
                    }
                }
            }

            if((mouseX < window.getSize().x-48) && (mouseLeftClick == false))
            {
                object_clicked = false;
                object_offset = false;
                start_point = 999;
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

    if(keyMap[sf::Keyboard::S])
    {
        cout << "Saving the animation" << endl;
        saveFile("");
    }
}
