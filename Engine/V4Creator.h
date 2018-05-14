#ifndef V4CREATOR_H
#define V4CREATOR_H

#include <SFML/Graphics.hpp>

#include "Editor.h"

class V4Creator
{
    private:
    Editor editor;

    std::vector<float> tot_fps;
    std::map<int,bool> keyMap;

    float fps = 60;
    sf::Clock fpsclock;

    public:
    int mouseX,mouseY;
    bool mouseLeftClick = false;

    V4Creator();
    void Init();
};

#endif // V4CREATOR_H
