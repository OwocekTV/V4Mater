#include "Object.h"
#include <iostream>

using namespace std;

Object::Object()
{

}

void Object::Load(string filename, int maxframes)
{
    tex_object.loadFromFile(filename);
    s_object.setTexture(tex_object);
    s_object.setOrigin(s_object.getGlobalBounds().width/2,s_object.getGlobalBounds().height/2);

    max_frames = maxframes;
}

void Object::setFrame(int frame)
{
    frame_x[frame] = x;
    frame_y[frame] = y;
    frame_rot[frame] = 0;
    frame_isset[frame] = true;
}

void Object::setPos(int frame, bool rv)
{
    bool first_keyframe = false;
    bool last_keyframe = false;

    float first_x = 0;
    float first_y = 0;
    float first_rot = 0;
    float first_set = false;
    float first_id = 0;

    float last_x = 0;
    float last_y = 0;
    float last_rot = 0;
    float last_set = false;
    float last_id = 0;

    float original_x = frame_x[0];
    float original_y = frame_y[0];

    for(int i=0; i<max_frames; i++)
    {
        if(first_keyframe == false)
        {
            if(i <= frame)
            {
                if(frame_isset[i] == true)
                {
                    first_x = frame_x[i];
                    first_y = frame_y[i];
                    first_rot = frame_rot[i];
                    first_set = true;
                    first_id = i;
                }
            }
        }
    }

    if(first_set == true)
    {
        first_keyframe = true;
    }

    if(first_keyframe == true)
    {
        for(int i=0; i<max_frames; i++)
        {
            if(last_keyframe == false)
            {
                if(i > frame)
                {
                    if(frame_isset[i] == true)
                    {
                        last_x = frame_x[i];
                        last_y = frame_y[i];
                        last_rot = frame_rot[i];
                        last_keyframe = true;
                        last_id = i;
                    }
                }
            }
        }
    }

    cout << "frame: " << frame << " first keyframe: " << first_id << " last keyframe: " << last_id << endl;

    int difference = last_id - first_id;

    if(difference > 0)
    {
        ///calculate difference here
        float xdiff = (last_x - first_x) / difference;
        float ydiff = (last_y - first_y) / difference;
        float rotdiff = (last_rot - first_rot) / difference;

        int diffcount = 0;
        if(frame >= first_id)
        {
            diffcount = difference - (last_id - frame);
        }

        float new_x = frame_x[first_id] + (xdiff * diffcount);
        float new_y = frame_y[first_id] + (ydiff * diffcount);

        x = new_x;
        y = new_y;

        oldx = x;
        oldy = y;
    }
}

void Object::Draw(sf::RenderWindow& window)
{
    s_object.setPosition(x,y);
    window.draw(s_object);
}
