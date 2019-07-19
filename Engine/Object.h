#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

using namespace std;

class Object
{
    public:
    sf::Texture tex_obj;
    sf::Sprite s_obj;

    float x,y,r=0,rs=0; ///local position
    float or_x,or_y; ///origin (for rotation)
    float s_x=1,s_y=1; ///scale
    int layer = 0;

    struct Frame
    {
        float time; ///timestamp
        float pos_x; ///x position
        float pos_y; ///y position
        float or_x; ///x origin
        float or_y; ///y origin
        float rotation; ///rotation
        float scale_x; ///x scale
        float scale_y; ///y scale
    };

    vector<Frame> frames; ///frames

    Object();
    void Load(string filename, int xpos, int ypos);
    void SetFrame(float time);
    void SetPos(float time);
    void Draw(sf::RenderWindow& window);
};

#endif // OBJECT_H
