#include "Button.h"

Button::Button()
{

}

void Button::Load(int type)
{
    tex_button_idle.loadFromFile("resources/ui/button_idle.png");
    tex_button_touch.loadFromFile("resources/ui/button_touch.png");
    button.setTexture(tex_button_idle);

    switch(type)
    {
        case 1:
        {
            tex_icon.loadFromFile("resources/ui/icon_new.png");
            icon.setTexture(tex_icon);

            break;
        }

        case 2:
        {
            tex_icon.loadFromFile("resources/ui/icon_open.png");
            icon.setTexture(tex_icon);

            break;
        }

        case 3:
        {
            tex_icon.loadFromFile("resources/ui/icon_save.png");
            icon.setTexture(tex_icon);

            break;
        }

        case 4:
        {
            tex_icon.loadFromFile("resources/ui/icon_info.png");
            icon.setTexture(tex_icon);

            break;
        }

        case 5:
        {
            tex_icon.loadFromFile("resources/ui/icon_animation.png");
            icon.setTexture(tex_icon);

            break;
        }

        case 6:
        {
            tex_icon.loadFromFile("resources/ui/icon_select.png");
            icon.setTexture(tex_icon);

            break;
        }

        case 7:
        {
            tex_icon.loadFromFile("resources/ui/icon_rotate.png");
            icon.setTexture(tex_icon);

            break;
        }

        case 8:
        {
            tex_icon.loadFromFile("resources/ui/icon_add.png");
            icon.setTexture(tex_icon);

            break;
        }

        case 9:
        {
            tex_icon.loadFromFile("resources/ui/icon_remove.png");
            icon.setTexture(tex_icon);

            break;
        }

        case 10:
        {
            tex_icon.loadFromFile("resources/ui/icon_play.png");
            icon.setTexture(tex_icon);

            break;
        }

        case 11:
        {
            tex_icon.loadFromFile("resources/ui/icon_pause.png");
            icon.setTexture(tex_icon);

            break;
        }

        case 12:
        {
            tex_icon.loadFromFile("resources/ui/icon_record.png");
            icon.setTexture(tex_icon);

            break;
        }
    }
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

    if((mouseX >= button.getPosition().x) && (mouseX <= button.getPosition().x + 48))
    {
        if((mouseY >= button.getPosition().y) && (mouseY < button.getPosition().y + 48))
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
    if((mouseX >= button.getPosition().x) && (mouseX <= button.getPosition().x + 48))
    {
        if((mouseY >= button.getPosition().y) && (mouseY < button.getPosition().y + 48))
        {
            return true;
        }
    }

    return false;
}

bool Button::setEnabled(bool enable)
{
    if(enable)
    disabled = false;
    else
    disabled = true;
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
    else
    {
        button.setColor(sf::Color(255,255,255,255));
        icon.setColor(sf::Color(255,255,255,255));
    }

    window.draw(button);
    window.draw(icon);
}
