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
    int keyframes_set = 0; ///for stats

    std::map<int,int> keyframe_x;
    std::map<int,int> keyframe_y;
    std::map<int,float> keyframe_rot;
    std::map<int,bool> keyframe_isset;

    std::map<int,float> frame_x;
    std::map<int,float> frame_y;
    std::map<int,float> frame_rot;

    bool selected = false;
    bool outline = false;

    Object();
    void Load(std::string filename, int maxframes);
    void calculateAnimation();
    void setFrame(int frame);
    void setPos(int frame);
    void Draw(sf::RenderWindow& window);
};

#endif // OBJECT_H
