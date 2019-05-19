#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

using namespace std;

class Button
{
    public:
    sf::Texture tex_button_idle,tex_button_touch,tex_icon;
    sf::Sprite button,icon;

    bool clickedOn = false; ///for click action
    bool disabled = false; ///for disabling/enabling
    bool selected = false; ///for selecting

    Button();
    void Load(int type, string directory);
    void setPosition(int x, int y);
    bool isClicked(int mouseX, int mouseY, bool mouseLeftClick);
    bool isHovered(int mouseX, int mouseY);
    bool setEnabled(bool enable);
    bool setSelected(bool select);
    void Draw(sf::RenderWindow& window);
};

#endif // BUTTON_H
