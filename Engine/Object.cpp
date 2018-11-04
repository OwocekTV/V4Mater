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

void Object::calculateAnimation()
{
    vector<int> keyframe_ID;

    ///get all of the keyframe IDs first
    for(int i=0; i<max_frames; i++)
    {
        if(keyframe_isset[i] == true)
        {
            keyframe_ID.push_back(i);
        }
    }

    ///then, based on all positions, calculate!
    /**
    0 - keyframe = keyframe positions (x = 0)
    1 - empty = calc positions (x = 5)
    2 - empty = calc positions (x = 10)
    3 - empty = calc positions (x = 15)
    4 - keyframe = keyframe positions (x = 20)

    get X of 0
    get X of 4
    divide by amount of frames inbetween
    */

    int buff = 0;
    while(buff < keyframe_ID.size())
    {
        ///set the keyframe frames
        frame_x[keyframe_ID[buff]] = keyframe_x[keyframe_ID[buff]];
        frame_y[keyframe_ID[buff]] = keyframe_y[keyframe_ID[buff]];
        frame_rot[keyframe_ID[buff]] = keyframe_rot[keyframe_ID[buff]];

        ///check if the second frame exists
        if(buff+1 < keyframe_ID.size())
        {
            ///get the frame difference
            int framediff = keyframe_ID[buff+1] - keyframe_ID[buff];
            float xdiff = (keyframe_x[keyframe_ID[buff+1]] - keyframe_x[keyframe_ID[buff]]) / framediff;
            float ydiff = (keyframe_y[keyframe_ID[buff+1]] - keyframe_y[keyframe_ID[buff]]) / framediff;
            float rotdiff = (keyframe_rot[keyframe_ID[buff+1]] - keyframe_rot[keyframe_ID[buff]]) / framediff;

            int start_point = keyframe_ID[buff];

            ///set all the other frames between to their respective positions
            for(int i=1; i<=framediff; i++)
            {
                frame_x[start_point+i] = keyframe_x[start_point] + (xdiff*i);
                frame_y[start_point+i] = keyframe_y[start_point] + (ydiff*i);
                frame_rot[start_point+i] = keyframe_rot[start_point] + (rotdiff*i);
            }

            ///set the last keyframe frames
            frame_x[keyframe_ID[buff+1]] = keyframe_x[keyframe_ID[buff+1]];
            frame_y[keyframe_ID[buff+1]] = keyframe_y[keyframe_ID[buff+1]];
            frame_rot[keyframe_ID[buff+1]] = keyframe_rot[keyframe_ID[buff+1]];
        }

        buff++;
    }
}

void Object::setFrame(int frame)
{
    keyframe_x[frame] = x;
    keyframe_y[frame] = y;
    keyframe_rot[frame] = 0;
    keyframe_isset[frame] = true;

    calculateAnimation();
    keyframes_set++;
}

void Object::setPos(int frame)
{
    oldx = x;
    oldy = y;

    x = frame_x[frame];
    y = frame_y[frame];
    //rot = frame_rot[frame];
}

void Object::Draw(sf::RenderWindow& window)
{
    r_outline.setSize(sf::Vector2f(s_object.getGlobalBounds().width,s_object.getGlobalBounds().height));
    r_outline.setFillColor(sf::Color(0,0,0,0));
    r_outline.setOutlineColor(sf::Color::Black);
    r_outline.setOutlineThickness(-2);
    r_outline.setOrigin(s_object.getOrigin().x,s_object.getOrigin().y);
    r_outline.setPosition(x,y);

    s_object.setPosition(x,y);
    window.draw(s_object);

    if(outline == true)
    {
        window.draw(r_outline);
    }
}
