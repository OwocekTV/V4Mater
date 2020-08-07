#include "Editor.h"

#include <windows.h>
#include <iostream>
#include <math.h>
#include <sstream>
#include "Button.h"
#include "P4A.h"
#include "Binary.hpp"

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

void Editor::saveAnim()
{
    animatedObject.SaveConfig();
}

void Editor::loadAnim()
{
    animatedObject.LoadConfig(OpenFile());
    max_time = animatedObject.max_time;
    isResized = true;
    ao_loaded = true;
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
        if(ao_loaded)
        {
            animatedObject.fps = fps;
            animatedObject.local_x = 500;
            animatedObject.local_y = 300;
            animatedObject.Draw(window);
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
                            case 1:
                            {
                                loadAnim();

                                break;
                            }

                            case 2:
                            {
                                saveAnim();
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
                        }
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

        animatedObject.cur_pos = timeline.cur_pos;

        timeline.max_time = max_time;
        timeline.mouseX = mouseX;
        timeline.mouseY = mouseY;
        timeline.mouseLeftClick = mouseLeftClick;
        timeline.Draw(window);

        /// ///////////////////////////// ///
        /// ///////// GUI Menus ///////// ///
        /// ///////////////////////////// ///
    }
}
