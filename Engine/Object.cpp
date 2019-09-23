#include "Object.h"
#include <iostream>

using namespace std;

Object::Object()
{

}

void Object::Load(string filename, int xpos, int ypos)
{
    cout << "Loading object" << endl;
    texture_path = filename.substr(filename.find_last_of("\\/")+1);
    cout << "Texture path: " << texture_path << endl;

    if(tex_obj.loadFromFile(filename))
    {
        s_obj.setTexture(tex_obj);

        or_x = s_obj.getGlobalBounds().width/2;
        or_y = s_obj.getGlobalBounds().height/2;

        x = xpos;
        y = ypos;

        cout << "Object loaded successfully" << endl;
    }
}

void Object::SetFrame(float time)
{
    Frame tmp;
    tmp.time = time;
    tmp.pos_x = x;
    tmp.pos_y = y;
    tmp.or_x = or_x;
    tmp.or_y = or_y;
    tmp.rotation = r + (rs*360);
    tmp.scale_x = s_x;
    tmp.scale_y = s_y;

    frames.push_back(tmp);

    std::sort(frames.begin(), frames.end(), [](auto const &a, auto const &b) { return a.time < b.time; });
}

void Object::SetCustomFrame(float in_time, float in_pos_x, float in_pos_y, float in_or_x, float in_or_y, float in_rotation, float in_scale_x, float in_scale_y)
{
    Frame tmp;
    tmp.time = in_time;
    tmp.pos_x = in_pos_x;
    tmp.pos_y = in_pos_y;
    tmp.or_x = in_or_x;
    tmp.or_y = in_or_y;
    tmp.rotation = in_rotation;
    tmp.scale_x = in_scale_x;
    tmp.scale_y = in_scale_y;

    frames.push_back(tmp);

    std::sort(frames.begin(), frames.end(), [](auto const &a, auto const &b) { return a.time < b.time; });
}

void Object::SetPos(float time)
{
    if(debug)
    cout << "[OBJ] SETPOS called" << endl;

    for(int i=0; i<frames.size(); i++)
    {
        if(debug)
        cout << "[OBJ] Check frame " << i << ", ftime " << frames[i].time << " vs " << time << " sz: " << frames.size()-1 << " >= " << i+1 << endl;

        if(frames[i].time < time)
        {
            if(frames.size()-1 >= i+1)
            {
                ///another frame exists

                if(frames[i+1].time > time)
                {
                    if(debug)
                    cout << "[OBJ] HANDLER 1: another frame, calc inbetween" << endl;

                    ///Calculate in-between positions
                    float time_diff = frames[i+1].time - frames[i].time;
                    float time_pos = time - frames[i].time;
                    float time_percentage = time_pos / time_diff;

                    x = frames[i].pos_x + ((frames[i+1].pos_x - frames[i].pos_x) * time_percentage);
                    y = frames[i].pos_y + ((frames[i+1].pos_y - frames[i].pos_y) * time_percentage);
                    r = frames[i].rotation + ((frames[i+1].rotation - frames[i].rotation) * time_percentage);
                    or_x = frames[i].or_x + ((frames[i+1].or_x - frames[i].or_x) * time_percentage);
                    or_y = frames[i].or_y + ((frames[i+1].or_y - frames[i].or_y) * time_percentage);
                    s_x = frames[i].scale_x + ((frames[i+1].scale_x - frames[i].scale_x) * time_percentage);
                    s_y = frames[i].scale_y + ((frames[i+1].scale_y - frames[i].scale_y) * time_percentage);

                    break;
                }
                else
                {
                    if(debug)
                    cout << "[OBJ] HANDLER 4: skip or get last pos" << endl;

                    x = frames[frames.size()-1].pos_x;
                    y = frames[frames.size()-1].pos_y;
                    r = frames[frames.size()-1].rotation;
                    or_x = frames[frames.size()-1].or_x;
                    or_y = frames[frames.size()-1].or_y;
                    s_x = frames[frames.size()-1].scale_x;
                    s_y = frames[frames.size()-1].scale_y;
                }
            }
            else
            {
                if(debug)
                cout << "[OBJ] HANDLER 2: last frame, get last pos" << endl;

                x = frames[i].pos_x;
                y = frames[i].pos_y;
                r = frames[i].rotation;
                or_x = frames[i].or_x;
                or_y = frames[i].or_y;
                s_x = frames[i].scale_x;
                s_y = frames[i].scale_y;

                break;
            }
        }
        else
        {
            if(debug)
            cout << "[OBJ] HANDLER 3: first frame/before first frame, get first pos" << endl;

            x = frames[i].pos_x;
            y = frames[i].pos_y;
            r = frames[i].rotation;
            or_x = frames[i].or_x;
            or_y = frames[i].or_y;
            s_x = frames[i].scale_x;
            s_y = frames[i].scale_y;

            break;
        }
    }
}

void Object::Draw(sf::RenderWindow& window)
{
    s_obj.setTexture(tex_obj);
    s_obj.setOrigin(or_x,or_y);
    s_obj.setPosition(x,y);
    s_obj.setRotation(r);
    window.draw(s_obj);
}
