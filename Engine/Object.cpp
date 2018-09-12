#include "Object.h"

using namespace std;

Object::Object()
{

}

void Object::Load(string filename)
{
    tex_object.loadFromFile(filename);
    s_object.setTexture(tex_object);
}

void Object::Draw(sf::RenderWindow& window)
{
    window.draw(s_object);
}
