#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "P4A.h"

class Editor
{
    public:
    sf::Font font;
    sf::Text t_logo;
    sf::Text t_newfile;
    sf::Text t_loadfile;

    int mouseX,mouseY;
    bool mouseLeftClick = false;
    bool mouseRightClick = false;

    bool isAlreadyClicked = false;
    int RMB_x = 0;
    int RMB_y = 0;

    sf::CircleShape shape;
    int shape_x = 500;
    int shape_y = 500;

    int x_distance = 0;
    int y_distance = 0;

    int state = 3;
    std::string archiveFile = "";

    P4A p4a;

    Editor();
    std::string OpenArchiveFile();
    std::string OpenFile();
    void Draw(sf::RenderWindow& window);
};

#endif // EDITOR_H
