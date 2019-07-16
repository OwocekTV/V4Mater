#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "P4A.h"
#include "Object.h"
#include "Button.h"
#include "Timeline.h"

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
    sf::View view;

    std::vector<Object> objects;

    sf::RectangleShape r_outline;

    sf::Text t_curframes;

    int state = 3;
    std::string archiveFile = "";

    P4A p4a;
    Button buttons[11];
    int clickedOn = -1;
    bool playing = false;

    bool isResized = true;

    Timeline timeline;
    float cur_pos = 0;
    float max_time = 10;
    float timeline_old = 0;

    int object_selected = -1;
    bool object_clicked = false;

    int highestLayer = -1;
    int highestIndex = -1;
    bool object_offset = false;
    int mX=0,mY=0,mR=0;

    bool allowMove = false;
    bool allowRotate = false;

    ///TEMPORARY
    float oldrot = 0;

    string directory = "";

    bool buttons_loaded = false;
    sf::RectangleShape r_selected;

    Editor();
    std::string OpenArchiveFile();
    std::string OpenFile();
    void Draw(sf::RenderWindow& window);
};

#endif // EDITOR_H
