#include "Editor.h"

#include <windows.h>
#include <iostream>
#include <math.h>
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

    tex_animmgr.loadFromFile("resources/ui/anim_manager.png");
    tex_animnew.loadFromFile("resources/ui/anim_new.png");
    tex_animrmv.loadFromFile("resources/ui/anim_remove.png");
    tex_animrow.loadFromFile("resources/ui/anim_row.png");
    tex_mdlmgr.loadFromFile("resources/ui/model_manager.png");

    s_animmgr.setTexture(tex_animmgr);
    s_animmgr.setOrigin(s_animmgr.getGlobalBounds().width/2,s_animmgr.getGlobalBounds().height/2);

    s_animnew.setTexture(tex_animnew);
    s_animnew.setOrigin(s_animnew.getGlobalBounds().width/2,s_animnew.getGlobalBounds().height/2);

    s_mdlmgr.setTexture(tex_mdlmgr);
    s_mdlmgr.setOrigin(s_mdlmgr.getGlobalBounds().width/2,s_mdlmgr.getGlobalBounds().height/2);

    ///sample, temporary animations
    /*Animation temp;
    temp.a_begin = 0.0;
    temp.a_end = 4.6935;
    temp.a_name = "animation";

    animations.push_back(temp);
    animations.push_back(temp);
    animations.push_back(temp);
    animations.push_back(temp);
    animations.push_back(temp);
    animations.push_back(temp);
    animations.push_back(temp);
    animations.push_back(temp);*/
}

/// /////////////// ///
/// WINDOWS.H START ///
/// /////////////// ///

string Editor::OpenFile()
{
    char filename[MAX_PATH];

    OPENFILENAME ofn;
    ZeroMemory(&filename, sizeof(filename));
    ZeroMemory(&ofn,      sizeof(ofn));
    ofn.lStructSize  = sizeof( ofn );
    ofn.hwndOwner    = NULL;
    ofn.lpstrFilter  = "All files\0*.*\0";
    ofn.lpstrFile    = filename;
    ofn.nMaxFile     = MAX_PATH;
    ofn.lpstrTitle   = "Select a file";
    ofn.Flags        = OFN_FILEMUSTEXIST;

    if(GetOpenFileNameA(&ofn))
    {
        std::cout << filename << endl;
    }
    else
    {
        return "";
    }

    return string(filename);
}

string Editor::SaveFile()
{
    char filename[MAX_PATH];

    OPENFILENAME ofn;
    ZeroMemory(&filename, sizeof(filename));
    ZeroMemory(&ofn,      sizeof(ofn));
    ofn.lStructSize  = sizeof( ofn );
    ofn.hwndOwner    = NULL;
    ofn.lpstrFilter  = "All files\0*.*\0";
    ofn.lpstrFile    = filename;
    ofn.nMaxFile     = MAX_PATH;
    ofn.lpstrTitle   = "Select a file";

    if(GetSaveFileNameA(&ofn))
    {
        std::cout << filename << endl;
    }
    else
    {
        return "";
    }

    return string(filename);
}

/// ///////////// ///
/// WINDOWS.H END ///
/// ///////////// ///

void Editor::setPositions(float time)
{
    for(int i=0; i<objects.size(); i++)
    {
        objects[i].SetPos(timeline.cur_pos);
    }
}

void Editor::saveAnim()
{
    ///S: - animation settings

    ///OI: - create object
    ///F: - object frame

    ///HB: - hitbox object
    ///HBF: - hitbox frame

    ///A: - animation segment

    ofstream anim(directory+"data.anim", ios::binary);

    ///Save header with version
    anim << "V4Mater-ver-1.00\n";

    ///Save initial animation settings
    anim << "S:" << to_string_with_precision2(max_time,6) << "\n";

    ///Save existing animations
    for(int i=0; i<animations.size(); i++)
    {
        anim << "A:" << to_string_with_precision2(animations[i].a_begin,6) << "," << to_string_with_precision2(animations[i].a_end,6) << "," << animations[i].a_name << "\n";
    }

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
    objects.clear();

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
                    string objectdata = line.substr(line.find_first_of(":")+1);
                    vector<string> object = split(objectdata,',');

                    string tex_file = object[0];
                    handle.Extract(tex_file);

                    int parent = -1;

                    if(object.size() > 1)
                    int parent = atoi(object[1].c_str())*2;

                    Object tmp;
                    sf::Image b;
                    b.create(1,1,sf::Color(0,0,0,0));
                    sf::Texture tb;
                    tb.loadFromImage(b);
                    tmp.Load(tex_file,0,0);
                    //tmp.Load(tb,0,0);
                    tmp.layer = objects.size();
                    tmp.parent = parent;
                    objects.push_back(tmp);

                    cout << "Added new object from " << tex_file << endl;

                    /*
                    markings
                    Object red;
                    sf::Image r;
                    r.create(2,2,sf::Color::Red);
                    sf::Texture t;
                    t.loadFromImage(r);
                    red.Load(t,0,0);
                    red.layer = objects.size();
                    red.parent = parent+1;
                    objects.push_back(red);*/

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
                    objects[objectID*2].SetCustomFrame(time,pos_x,pos_y,or_x,or_y,rotation,scale_x,scale_y);
                    objects[objectID*2+1].SetCustomFrame(time,pos_x,pos_y,1,1,rotation,scale_x,scale_y);
                }
            }
        }
    }

    setPositions(0);
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
        buttons[10].Load(11, directory);
        buttons[11].Load(12, directory);
        buttons[12].Load(14, directory);

        buttons_loaded = true;
    }

    if(state == 3)
    {
        /// /////////////////////////// ///
        /// ///////// Objects ///////// ///
        /// /////////////////////////// ///

        if(objects.size() > 0)
        {
            vector<int> objects_clicked;

            ///Calculate object's position based on the timeline
            if(timeline_old != timeline.cur_pos)
            {
                //objects[i].SetPos(timeline.cur_pos);
                setPositions(timeline.cur_pos);
            }

            for(int i=0; i<objects.size(); i++)
            {
                if(mouseX > objects[i].x - objects[i].s_obj.getGlobalBounds().width/2)
                {
                    if(mouseX < objects[i].x + objects[i].s_obj.getGlobalBounds().width/2)
                    {
                        if(mouseY > objects[i].y - objects[i].s_obj.getGlobalBounds().height/2)
                        {
                            if(mouseY < objects[i].y + objects[i].s_obj.getGlobalBounds().height/2)
                            {
                                if(mouseLeftClick == true)
                                {
                                    objects_clicked.push_back(i);
                                }
                            }
                        }
                    }
                }

                objects[i].Draw(window);
            }

            timeline_old = timeline.cur_pos;

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

                            objects[object_selected].x = mouseX + mX;
                            objects[object_selected].y = mouseY + mY;
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

                        if(allowScale)
                        {
                            if(!object_offset)
                            {
                                object_offset = true;
                            }

                            if(keyMap[sf::Keyboard::Up])
                            {
                                objects[object_selected].s_y -= float(1) / fps;
                            }

                            if(keyMap[sf::Keyboard::Down])
                            {
                                objects[object_selected].s_y += float(1) / fps;
                            }

                            if(keyMap[sf::Keyboard::Left])
                            {
                                objects[object_selected].s_x -= float(1) / fps;
                            }

                            if(keyMap[sf::Keyboard::Right])
                            {
                                objects[object_selected].s_x += float(1) / fps;
                            }

                            cout << objects[object_selected].s_x << " " << objects[object_selected].s_y << endl;
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

            for(int i=0; i<13; i++)
            {
                int add = 0;

                if(i > 4)
                add = 34;

                buttons[i].setPosition(window.getSize().x - 36, 34*i+add);
            }

            isResized = false;
        }

        /// /////////////////////////// ///
        /// ///////// Buttons ///////// ///
        /// /////////////////////////// ///

        for(int i=0; i<13; i++)
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
                            ///New file
                            case 0:
                            {
                                objects.clear();
                                max_time = 10;
                                timeline.Create(max_time,window);

                                break;
                            }

                            ///Load file
                            case 1:
                            {
                                string openP4A = OpenFile();

                                if(openP4A != "")
                                {
                                    p4a.ReadDictionary(openP4A);
                                    string animdata = p4a.ReadToMemory("data.anim");

                                    if(animdata == "")
                                    {
                                        cout << "Invalid animation file!" << endl;
                                        state = 0;
                                    }

                                    loadAnim(animdata,p4a);
                                    timeline.Create(max_time,window);
                                }

                                break;
                            }

                            ///Save file
                            case 2:
                            {
                                string sfile = SaveFile();

                                if(sfile != "")
                                {
                                    if(sfile.find(".p4a") == std::string::npos)
                                    {
                                        sfile += ".p4a";
                                    }

                                    saveAnim();

                                    P4A handle;
                                    handle.LoadFile(directory+"data.anim");
                                    for(int i=0; i<objects.size(); i++)
                                    {
                                        handle.LoadFile(objects[i].texture_path);
                                    }

                                    handle.SaveToFile(sfile);
                                }

                                break;
                            }

                            ///Model manager
                            case 3:
                            {
                                if(guiMode != 2)
                                guiMode = 2;
                                else
                                guiMode = 0;

                                break;
                            }

                            ///Animation manager
                            case 4:
                            {
                                if(guiMode != 1)
                                guiMode = 1;
                                else
                                guiMode = 0;

                                break;
                            }

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
                                buttons[7].setSelected(false);
                                buttons[8].setSelected(false);

                                allowRotate = false;
                                allowScale = false;
                                allowOrigin = false;

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
                                buttons[7].setSelected(false);
                                buttons[8].setSelected(false);

                                allowMove = false;
                                allowScale = false;
                                allowOrigin = false;

                                break;
                            }

                            case 7: ///Scale Tool
                            {
                                if(buttons[i].selected)
                                {
                                    buttons[i].setSelected(false);
                                    allowScale = false;
                                }
                                else
                                {
                                    buttons[i].setSelected(true);
                                    allowScale = true;
                                }

                                buttons[5].setSelected(false);
                                buttons[6].setSelected(false);
                                buttons[8].setSelected(false);

                                allowMove = false;
                                allowRotate = false;
                                allowOrigin = false;

                                break;
                            }

                            case 8: ///Origin Tool
                            {
                                if(buttons[i].selected)
                                {
                                    buttons[i].setSelected(false);
                                    allowOrigin = false;
                                }
                                else
                                {
                                    buttons[i].setSelected(true);
                                    allowOrigin = true;
                                }

                                buttons[5].setSelected(false);
                                buttons[6].setSelected(false);
                                buttons[7].setSelected(false);

                                allowMove = false;
                                allowRotate = false;
                                allowScale = false;

                                break;
                            }

                            case 9: ///Add object button
                            {
                                string tex_file = OpenFile();

                                if(tex_file != "")
                                {
                                    Object tmp;
                                    tmp.Load(tex_file, window.getSize().x/2,window.getSize().y/2);
                                    tmp.layer = objects.size();
                                    objects.push_back(tmp);

                                    cout << "Added new object from " << tex_file << endl;
                                }

                                break;
                            }

                            case 11: ///Play/Stop button
                            {
                                if(playing)
                                {
                                    playing = false;

                                    buttons[5].setEnabled(true);
                                    buttons[6].setEnabled(true);
                                    buttons[7].setEnabled(true);
                                    buttons[8].setEnabled(true);
                                    buttons[9].setEnabled(true);
                                    buttons[10].setEnabled(true);
                                    buttons[12].setEnabled(true);

                                    buttons[i].Load(12, directory);
                                }
                                else
                                {
                                    playing = true;

                                    buttons[5].setEnabled(false);
                                    buttons[6].setEnabled(false);
                                    buttons[7].setEnabled(false);
                                    buttons[8].setEnabled(false);
                                    buttons[9].setEnabled(false);
                                    buttons[10].setEnabled(false);
                                    buttons[12].setEnabled(false);

                                    buttons[5].setSelected(false);
                                    buttons[6].setSelected(false);
                                    buttons[7].setSelected(false);
                                    buttons[8].setSelected(false);
                                    buttons[9].setSelected(false);
                                    buttons[10].setSelected(false);
                                    buttons[12].setSelected(false);

                                    allowMove = false;
                                    allowRotate = false;

                                    buttons[i].Load(13, directory);
                                }

                                break;
                            }

                            case 12:
                            {
                                if(object_selected > -1)
                                {
                                    cout << "Record frame at " << timeline.cur_pos << " object " << object_selected << endl;
                                    objects[object_selected].SetFrame(timeline.cur_pos);
                                }

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

        timeline.max_time = max_time;
        timeline.mouseX = mouseX;
        timeline.mouseY = mouseY;
        timeline.mouseLeftClick = mouseLeftClick;
        timeline.Draw(window);

        /// ///////////////////////////// ///
        /// ///////// GUI Menus ///////// ///
        /// ///////////////////////////// ///

        if(guiMode == 1)
        {
            //cout << timeline.cur_pos << endl;

            if(keyMap[sf::Keyboard::C])
            {
                ///TEMPORARY!!
                createAnimMode = true;
                cout << "Creating new animation, waiting for input" << endl;
            }

            if(createAnimMode)
            {
                if(keyMap[sf::Keyboard::S])
                {
                    temp_newAnimStart = timeline.cur_pos;
                    cout << "Animation starts at " << timeline.cur_pos << endl;
                }

                if(keyMap[sf::Keyboard::E])
                {
                    temp_newAnimEnd = timeline.cur_pos;
                    cout << "Animation ends at " << timeline.cur_pos << endl;
                }

                if(keyMap[sf::Keyboard::N])
                {
                    cout << "Put animation name here: ";
                    cin >> temp_newAnimName;
                }

                if(keyMap[sf::Keyboard::Enter])
                {
                    Animation temp;
                    temp.a_begin = temp_newAnimStart;
                    temp.a_end = temp_newAnimEnd;
                    temp.a_name = temp_newAnimName;

                    animations.push_back(temp);

                    createAnimMode = false;
                }
            }


            s_animmgr.setPosition(window.getSize().x/2,window.getSize().y/2-40);
            window.draw(s_animmgr);

            for(int i=0; i<7; i++)
            {
                if(animations.size() > i+animScroll)
                {
                    s_animrow[i].setTexture(tex_animrow);
                    s_animrow[i].setOrigin(s_animrow[i].getGlobalBounds().width/2,s_animrow[i].getGlobalBounds().height/2);
                    s_animrow[i].setPosition(s_animmgr.getPosition().x,s_animmgr.getPosition().y-114 + (51.5*i));

                    s_animrow_nm[i].setFont(font);
                    s_animrow_nm[i].setCharacterSize(30);
                    s_animrow_nm[i].setFillColor(sf::Color::Black);
                    s_animrow_nm[i].setString(animations[i+animScroll].a_name);
                    s_animrow_nm[i].setOrigin(0,s_animrow_nm[i].getGlobalBounds().height/2);
                    s_animrow_nm[i].setPosition(s_animrow[i].getPosition().x-s_animrow[i].getGlobalBounds().width/2+6,s_animrow[i].getPosition().y-7);

                    s_animrow_bg[i].setFont(font);
                    s_animrow_bg[i].setCharacterSize(30);
                    s_animrow_bg[i].setFillColor(sf::Color::Black);
                    s_animrow_bg[i].setString(to_string_with_precision2(animations[i+animScroll].a_begin,6));
                    s_animrow_bg[i].setOrigin(0,s_animrow_bg[i].getGlobalBounds().height/2);
                    s_animrow_bg[i].setPosition(s_animrow[i].getPosition().x-s_animrow[i].getGlobalBounds().width/2+178,s_animrow[i].getPosition().y-7);

                    s_animrow_en[i].setFont(font);
                    s_animrow_en[i].setCharacterSize(30);
                    s_animrow_en[i].setFillColor(sf::Color::Black);
                    s_animrow_en[i].setString(to_string_with_precision2(animations[i+animScroll].a_end,6));
                    s_animrow_en[i].setOrigin(0,s_animrow_en[i].getGlobalBounds().height/2);
                    s_animrow_en[i].setPosition(s_animrow[i].getPosition().x+74,s_animrow[i].getPosition().y-7);

                    s_animrmv[i].setTexture(tex_animrmv);
                    s_animrmv[i].setOrigin(s_animrmv[i].getGlobalBounds().width/2,s_animrmv[i].getGlobalBounds().height/2);
                    s_animrmv[i].setPosition(s_animmgr.getPosition().x+282,s_animmgr.getPosition().y-114 + (51.5*i));

                    s_animrmv[i].setColor(sf::Color::Black);

                    if(mouseX > s_animrmv[i].getPosition().x-s_animrmv[i].getGlobalBounds().width/2)
                    {
                        if(mouseX < s_animrmv[i].getPosition().x+s_animrmv[i].getGlobalBounds().width/2)
                        {
                            if(mouseY > s_animrmv[i].getPosition().y-s_animrmv[i].getGlobalBounds().height/2)
                            {
                                if(mouseY < s_animrmv[i].getPosition().y+s_animrmv[i].getGlobalBounds().height/2)
                                {
                                    s_animrmv[i].setColor(sf::Color(0,255,0,128));
                                    cout << "a" << i << endl;

                                    if(mouseLeftClick)
                                    {
                                        animations[i+animScroll].del = true;
                                        mouseLeftClick = false;
                                    }
                                }
                            }
                        }
                    }

                    window.draw(s_animrow[i]);
                    window.draw(s_animrow_nm[i]);
                    window.draw(s_animrow_bg[i]);
                    window.draw(s_animrow_en[i]);
                    window.draw(s_animrmv[i]);
                }
                else
                {
                    break;
                }
            }

            vector<Animation> new_animations;

            for(int i=0; i<animations.size(); i++)
            {
                if(!animations[i].del)
                new_animations.push_back(animations[i]);
            }

            animations = new_animations;
        }
        else if(guiMode == 2)
        {
            s_mdlmgr.setPosition(window.getSize().x/2,window.getSize().y/2-40);
            window.draw(s_mdlmgr);
        }
    }
}
