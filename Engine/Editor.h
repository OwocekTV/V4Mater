#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "P4A.h"

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

    bool isAlreadyClicked = false;
    int RMB_x = 0;
    int RMB_y = 0;

    sf::CircleShape shape;
    float shape_x = 500; ///for camera
    float shape_y = 500;

    float shape_ax = 0; ///for animation
    float shape_ay = 0;

    float x_distance = 0;
    float y_distance = 0;

    float f_frames = 0;
    int frames = 0;
    int max_frames = 60;
    bool play = false;
    bool selected = false;
    bool moveObject = false;
    bool isClicked = false;
    int LMB_x = 0;
    int LMB_y = 0;

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
