#include "Object.h"
#include <iostream>

using namespace std;

Object::Object()
{

}

void Object::Load(string filename, int xpos, int ypos)
{
    cout << "Loading object" << endl;

    if(tex_obj.loadFromFile(filename))
    {
        s_obj.setTexture(tex_obj);

        or_x = s_obj.getGlobalBounds().width/2;
        or_y = s_obj.getGlobalBounds().height/2;

        x = xpos;
        y = ypos;

        cout << "Object loaded successfully" << endl;
    }
}

void Object::Draw(sf::RenderWindow& window)
{
    s_obj.setTexture(tex_obj);
    s_obj.setOrigin(or_x,or_y);
    s_obj.setPosition(x,y);
    window.draw(s_obj);
}
