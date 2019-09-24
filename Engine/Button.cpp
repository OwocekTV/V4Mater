#include "Button.h"

using namespace std;

Button::Button()
{

}

void Button::Load(int type, string directory)
{
    tex_button_idle.loadFromFile(directory+"resources/ui/button_idle.png");
    tex_button_touch.loadFromFile(directory+"resources/ui/button_touch.png");
    button.setTexture(tex_button_idle);

    switch(type)
    {
        case 1:
        {
            tex_icon.loadFromFile(directory+"resources/ui/icon_new.png");
            break;
        }

        case 2:
        {
            tex_icon.loadFromFile(directory+"resources/ui/icon_open.png");
            break;
        }

        case 3:
        {
            tex_icon.loadFromFile(directory+"resources/ui/icon_save.png");
            break;
        }

        case 4:
        {
            tex_icon.loadFromFile(directory+"resources/ui/icon_info.png");
            break;
        }

        case 5:
        {
            tex_icon.loadFromFile(directory+"resources/ui/icon_animation.png");
            break;
        }

        case 6:
        {
            tex_icon.loadFromFile(directory+"resources/ui/icon_select.png");
            break;
        }

        case 7:
        {
            tex_icon.loadFromFile(directory+"resources/ui/icon_rotate.png");
            break;
        }

        case 8:
        {
            tex_icon.loadFromFile(directory+"resources/ui/icon_scale.png");
            break;
        }

        case 9:
        {
            tex_icon.loadFromFile(directory+"resources/ui/icon_origin.png");
            break;
        }

        case 10:
        {
            tex_icon.loadFromFile(directory+"resources/ui/icon_add.png");
            break;
        }

        case 11:
        {
            tex_icon.loadFromFile(directory+"resources/ui/icon_remove.png");
            break;
        }

        case 12:
        {
            tex_icon.loadFromFile(directory+"resources/ui/icon_play.png");
            break;
        }

        case 13:
        {
            tex_icon.loadFromFile(directory+"resources/ui/icon_pause.png");
            break;
        }

        case 14:
        {
            tex_icon.loadFromFile(directory+"resources/ui/icon_record.png");
            break;
        }
    }


    icon.setTexture(tex_icon);
}

void Button::setPosition(int x, int y)
{
    button.setPosition(x,y);
    icon.setPosition(x,y);
}

bool Button::isClicked(int mouseX, int mouseY, bool mouseLeftClick)
{
    if(disabled)
    {
        return false;
    }

    if((mouseX >= button.getPosition().x) && (mouseX <= button.getPosition().x + button.getGlobalBounds().width))
    {
        if((mouseY >= button.getPosition().y) && (mouseY < button.getPosition().y + button.getGlobalBounds().width))
        {
            if(mouseLeftClick == true)
            {
                return true;
            }
        }
    }

    return false;
}

bool Button::isHovered(int mouseX, int mouseY)
{
    if((mouseX >= button.getPosition().x) && (mouseX <= button.getPosition().x + button.getGlobalBounds().width))
    {
        if((mouseY >= button.getPosition().y) && (mouseY < button.getPosition().y + button.getGlobalBounds().width))
        {
            return true;
        }
    }

    return false;
}

bool Button::setEnabled(bool enable)
{
    disabled = !enable;
}

bool Button::setSelected(bool select)
{
    selected = select;
}

void Button::Draw(sf::RenderWindow& window)
{
    if(clickedOn)
    {
        button.setTexture(tex_button_touch);
    }
    else
    {
        button.setTexture(tex_button_idle);
    }

    if(disabled)
    {
        button.setColor(sf::Color(220,220,220,255));
        icon.setColor(sf::Color(220,220,220,255));
    }
    else if(selected)
    {
        button.setColor(sf::Color(200,200,200,255));
        icon.setColor(sf::Color(200,200,200,255));
    }
    else
    {
        button.setColor(sf::Color(255,255,255,255));
        icon.setColor(sf::Color(255,255,255,255));
    }

    window.draw(button);
    window.draw(icon);
}
