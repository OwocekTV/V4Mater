#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "P4A.h"
#include "Object.h"

class Editor
{
    public:
    std::map<int,bool> keyMap;

    sf::Font font;
    sf::Text t_logo;
    sf::Text t_newfile;
    sf::Text t_loadfile;

    float fps = 60;

    int mouseX,mouseY;
    bool mouseLeftClick = false;
    bool mouseRightClick = false;
    bool isRightClicked = false;
    bool isLeftClicked = false;
    int RMB_x = 0, RMB_y = 0;
    int LMB_x = 0, LMB_y = 0;
    int distance_x = 0,distance_y = 0;
    int Ldistance_x = 0,Ldistance_y = 0;
    int camera_x = 320,camera_y = 180;
    int oldcamera_x = camera_x,oldcamera_y = camera_y;

    sf::View view;

    float f_frames = 0;
    int frames = 0;
    int max_frames = 240;
    bool play = false;

    Object obj_test;

    sf::RectangleShape r_outline;

    sf::Text t_curframes;

    int state = 3;
    std::string archiveFile = "";

    P4A p4a;

    Editor();
    std::string OpenArchiveFile();
    std::string OpenFile();
    void Draw(sf::RenderWindow& window);
};

#endif // EDITOR_H
