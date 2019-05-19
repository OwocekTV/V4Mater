#ifndef V4CREATOR_H
#define V4CREATOR_H

#include <SFML/Graphics.hpp>

#include "Editor.h"

class V4Creator
{
    public:
    Editor editor;

    std::vector<float> tot_fps;
    std::map<int,bool> keyMap;

    float fps = 60;
    sf::Clock fpsclock;

    int mouseX,mouseY;
    bool mouseLeftClick = false;
    bool mouseRightClick = false;

    V4Creator();
    void Init();
};

#endif // V4CREATOR_H
