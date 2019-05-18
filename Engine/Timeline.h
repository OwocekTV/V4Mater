#ifndef TIMELINE_H
#define TIMELINE_H

#include <SFML/Graphics.hpp>

using namespace std;

class Timeline
{
    public:
    sf::RectangleShape main_line;
    vector<sf::RectangleShape> big_lines;

    Timeline();
    void Create(float time, sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
};

#endif // TIMELINE_H
