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
    float max_time = 30;

    Editor();
    std::string OpenArchiveFile();
    std::string OpenFile();
    void Draw(sf::RenderWindow& window);
};

#endif // EDITOR_H
