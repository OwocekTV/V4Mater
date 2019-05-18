#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button
{
    public:
    sf::Texture tex_button_idle,tex_button_touch,tex_icon;
    sf::Sprite button,icon;

    bool clickedOn = false;
    bool disabled = false;

    Button();
    void Load(int type);
    void setPosition(int x, int y);
    bool isClicked(int mouseX, int mouseY, bool mouseLeftClick);
    bool isHovered(int mouseX, int mouseY);
    bool setEnabled(bool enable);
    void Draw(sf::RenderWindow& window);
};

#endif // BUTTON_H
