#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

class Object
{
    public:
    sf::Texture tex_object;
    sf::Sprite s_object;

    float x = 0;
    float y = 0;

    Object();
    void Load(std::string filename);
    void Draw(sf::RenderWindow& window);
};

#endif // OBJECT_H
