#include "Timeline.h"
#include <iostream>
#include <sstream>

using namespace std;

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 2)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

Timeline::Timeline()
{
    font.loadFromFile("resources/opensans.ttf");
}

void Timeline::Create(float time, sf::RenderWindow& window)
{
    int window_x = window.getSize().x;
    int window_y = window.getSize().y;

    big_lines.clear();
    time_lines.clear();

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

    //cout << mline_x << " " << mline_length << endl;

    int a_big = 5;

    for(int i=0; i<=a_big; i++)
    {
        float big_gap = float(mline_length) / float(a_big);
        float time_gap = float(time) / float(a_big);
        //cout << "big_gap:" << big_gap << endl;

        sf::RectangleShape tmp_big(sf::Vector2f(4,32));
        tmp_big.setOrigin(tmp_big.getGlobalBounds().width/2,tmp_big.getGlobalBounds().height/2);
        tmp_big.setPosition(mline_x+(big_gap * i), mline_y);
        tmp_big.setFillColor(sf::Color::Black);

        sf::Text tmp_text;
        tmp_text.setFont(font);
        tmp_text.setFillColor(sf::Color::Black);
        tmp_text.setCharacterSize(20);
        tmp_text.setString(to_string_with_precision((time_gap*i)));
        tmp_text.setOrigin(tmp_text.getGlobalBounds().width/2,tmp_text.getGlobalBounds().height/2);
        tmp_text.setPosition(mline_x+(big_gap * i), mline_y-40);

        big_lines.push_back(tmp_big);
        time_lines.push_back(tmp_text);
    }

    cursor.setSize(sf::Vector2f(8,50));
    cursor.setOrigin(cursor.getGlobalBounds().width/2,cursor.getGlobalBounds().height/2);
    cursor.setFillColor(sf::Color::Black);


    cursor_t1.setFont(font);
    cursor_t1.setFillColor(sf::Color::Black);
    cursor_t1.setCharacterSize(16);
}

void Timeline::Draw(sf::RenderWindow& window)
{
    window.draw(main_line);

    for(int i=0; i<big_lines.size(); i++)
    {
        window.draw(big_lines[i]);
        window.draw(time_lines[i]);
    }

    int mline_length = main_line.getSize().x;
    int mline_x = main_line.getPosition().x - (mline_length / 2);
    int mline_y = main_line.getPosition().y;

    float cursor_pos = mline_x + cur_pos / max_time * mline_length;
    cursor.setPosition(cursor_pos, mline_y);

    cursor_t1.setString(to_string_with_precision(cur_pos)+" s");
    cursor_t1.setOrigin(cursor_t1.getGlobalBounds().width/2,cursor_t1.getGlobalBounds().height/2);
    cursor_t1.setPosition(cursor_pos, mline_y+30);

    //cout << "mouseX: " << mouseX << " mouseY: " << mouseY << " cursor_pos: " << cursor_pos << " mline_y: " << mline_y << " cursorHold: " << cursorHold << " mouseLeftClick: " << mouseLeftClick << endl;

    if(mouseX > cursor_pos - 4)
    {
        if(mouseX < cursor_pos + 4)
        {
            if(mouseY > mline_y - 25)
            {
                if(mouseY < mline_y + 25)
                {
                    if(cursorHold == false)
                    {
                        if(mouseLeftClick)
                        {
                            cursorHold = true;
                        }
                    }
                }
            }
        }
    }

    if(cursorHold)
    {
        cur_pos = ((mouseX - mline_x) / float(mline_length)) * max_time;
        //cout << "cur_pos = ((" << mouseX << " - " << mline_x << ") / " << mline_length << ") * " << max_time << ": " << cur_pos << endl;

        if(cur_pos <= 0)
        {
            cur_pos = 0;
        }

        if(cur_pos >= max_time)
        {
            cur_pos = max_time;
        }

        if(mouseLeftClick == false)
        {
            cursorHold = false;
        }
    }

    window.draw(cursor);
    window.draw(cursor_t1);
}
