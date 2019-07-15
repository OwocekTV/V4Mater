#include "Object.h"
#include <iostream>

using namespace std;

Object::Object()
{

}

void Object::Load(string filename, int xpos, int ypos)
{
    cout << "Loading object" << endl;

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
    tmp.rotation = r;
    tmp.scale_x = s_x;
    tmp.scale_y = s_y;

    frames.push_back(tmp);

    std::sort(frames.begin(), frames.end(), [](auto const &a, auto const &b) { return a.time < b.time; });
}

void Object::SetPos(float time)
{
    for(int i=0; i<frames.size(); i++)
    {
        if(frames[i].time < time)
        {
            if(frames.size()-1 >= i+1)
            {
                ///another frame exists

                if(frames[i+1].time > time)
                {
                    ///Found inbetween frames
                    cout << "Time " << time << " found between " << i << " and " << i+1 << endl;

                    ///Calculate in-between positions
                    float time_diff = frames[i+1].time - frames[i].time;
                    float time_pos = time - frames[i].time;
                    float time_percentage = time_pos / time_diff;

                    cout << "Time_diff: " << time_diff << " time_pos: " << time_pos << " time_percent: " << time_percentage << "%" << endl;

                    float n_xpos = frames[i].pos_x + ((frames[i+1].pos_x - frames[i].pos_x) * time_percentage);
                    float n_ypos = frames[i].pos_y + ((frames[i+1].pos_y - frames[i].pos_y) * time_percentage);

                    x = n_xpos;
                    y = n_ypos;
                }
            }
            else
            {
                ///thats the last frame
                cout << "Time " << time << " is after the last frame " << i << endl;

                x = frames[i].pos_x;
                y = frames[i].pos_y;
                r = frames[i].rotation;
                or_x = frames[i].or_x;
                or_y = frames[i].or_y;
                s_x = frames[i].scale_x;
                s_y = frames[i].scale_y;
            }
        }
    }
}

void Object::Draw(sf::RenderWindow& window)
{
    s_obj.setTexture(tex_obj);
    s_obj.setOrigin(or_x,or_y);
    s_obj.setPosition(x,y);
    window.draw(s_obj);
}
