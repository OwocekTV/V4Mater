#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button
{
    public:
    sf::Texture tex_button,tex_icon;
    sf::Sprite button,icon;

    Button();
    void Load(int type);
    bool isClicked();
    void Draw(sf::RenderWindow& window);
};

#endif // BUTTON_H
