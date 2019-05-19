#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

using namespace std;

class Object
{
    public:
    sf::Texture tex_obj;
    sf::Sprite s_obj;

    float x,y,r; ///local position
    float or_x,or_y; ///origin (for rotation)
    int layer = 0;

    vector<float> keyframes; ///positions on where the frame was recorded
    vector<float> key_x; ///X position for recorded frame
    vector<float> key_y; ///Y position for recorded frame
    vector<float> key_r; ///rotation for recorded frame

    Object();
    void Load(string filename, int xpos, int ypos);
    void Draw(sf::RenderWindow& window);
};

#endif // OBJECT_H
