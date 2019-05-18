#include "Timeline.h"
#include <iostream>

using namespace std;

Timeline::Timeline()
{

}

void Timeline::Create(float time, sf::RenderWindow& window)
{
    int window_x = window.getSize().x;
    int window_y = window.getSize().y;

    big_lines.clear();

    if(window_y < 650)
    {
        ///draw the line away from the buttons
        main_line.setSize(sf::Vector2f((window.getSize().x-48)-((window.getSize().x-48) / 26.667),4));
        main_line.setOrigin(main_line.getGlobalBounds().width/2,main_line.getGlobalBounds().height/2);
        main_line.setPosition((window.getSize().x-48)/2,window.getSize().y-(window.getSize().y / 18)-28);
        main_line.setFillColor(sf::Color::Black);
    }
    else
    {
        main_line.setSize(sf::Vector2f(window.getSize().x-(window.getSize().x / 26.667),4));
        main_line.setOrigin(main_line.getGlobalBounds().width/2,main_line.getGlobalBounds().height/2);
        main_line.setPosition(window.getSize().x/2,window.getSize().y-(window.getSize().y / 18)-28);
        main_line.setFillColor(sf::Color::Black);
    }

    int mline_length = main_line.getSize().x;
    int mline_x = main_line.getPosition().x - (mline_length / 2);
    int mline_y = main_line.getPosition().y;

    cout << mline_x << " " << mline_length << endl;

    int a_big = 5;

    for(int i=0; i<=a_big; i++)
    {
        float big_gap = float(mline_length) / float(a_big);
        cout << "big_gap:" << big_gap << endl;

        sf::RectangleShape tmp_big(sf::Vector2f(4,32));
        tmp_big.setOrigin(tmp_big.getGlobalBounds().width/2,tmp_big.getGlobalBounds().height/2);
        tmp_big.setPosition(mline_x+(big_gap * i), mline_y);
        tmp_big.setFillColor(sf::Color::Black);

        big_lines.push_back(tmp_big);
    }
}

void Timeline::Draw(sf::RenderWindow& window)
{
    window.draw(main_line);

    for(int i=0; i<big_lines.size(); i++)
    {
        window.draw(big_lines[i]);
    }
}
