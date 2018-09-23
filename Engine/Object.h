#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

class Object
{
    public:
    sf::Texture tex_object;
    sf::Sprite s_object;

    sf::RectangleShape r_outline;

    float x=0,y=0;
    float oldx=x,oldy=y;
    int max_frames = 60;

    std::map<int,int> frame_x;
    std::map<int,int> frame_y;
    std::map<int,float> frame_rot;
    std::map<int,bool> frame_isset;

    bool selected = false;
    bool outline = false;

    Object();
    void Load(std::string filename, int maxframes);
    void setFrame(int frame);
    void setPos(int frame, bool rv);
    void Draw(sf::RenderWindow& window);
};

#endif // OBJECT_H
