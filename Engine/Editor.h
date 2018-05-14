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

    int state = 0;
    std::string archiveFile = "";

    P4A p4a;

    Editor();
    std::string OpenArchiveFile();
    std::string OpenFile();
    void Draw(sf::RenderWindow& window);
};

#endif // EDITOR_H
