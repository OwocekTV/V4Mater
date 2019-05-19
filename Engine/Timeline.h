#ifndef TIMELINE_H
#define TIMELINE_H

#include <SFML/Graphics.hpp>

using namespace std;

class Timeline
{
    public:
    sf::Font font;

    sf::RectangleShape main_line;
    vector<sf::RectangleShape> big_lines;
    vector<sf::Text> time_lines;

    sf::RectangleShape cursor;
    sf::Text cursor_t1;
    sf::Text cursor_t2;

    float max_time = 0;
    float cur_pos = 0; ///time position

    int mouseX,mouseY;
    bool mouseLeftClick = false;
    bool cursorHold = false;

    Timeline();
    void Create(float time, sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
};

#endif // TIMELINE_H
