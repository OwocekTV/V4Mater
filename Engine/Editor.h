#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "P4A.h"
#include "Object.h"
#include "Button.h"
#include "Timeline.h"

class Editor
{
    public:
    std::map<int,bool> keyMap;

    sf::Font font;
    sf::Text t_logo;
    sf::Text t_newfile;
    sf::Text t_loadfile;

    float fps = 60;

    int mouseX,mouseY;
    bool mouseLeftClick = false;
    bool mouseRightClick = false;
    bool isRightClicked = false;
    bool isLeftClicked = false;
    int RMB_x = 0, RMB_y = 0;
    int LMB_x = 0, LMB_y = 0;
    sf::View view;

    std::vector<Object> objects;

    sf::RectangleShape r_outline;

    sf::Text t_curframes;

    int state = 3;
    std::string archiveFile = "";

    P4A p4a;
    Button buttons[14];
    int clickedOn = -1;
    bool playing = false;

    bool isResized = true;

    Timeline timeline;
    float cur_pos = 0;
    float max_time = 10;
    float timeline_old = 0;

    int object_selected = -1;
    bool object_clicked = false;
    float start_point = 999;
    float latest_point = 0;

    int highestLayer = -1;
    int highestIndex = -1;
    bool object_offset = false;
    int mX=0,mY=0,mR=0;

    bool allowMove = false;
    bool allowRotate = false;
    bool allowScale = false;
    bool allowOrigin = false;

    int guiMode = 0; ///0 - nothing, 1 - model settings, 2 - animation manager
    int animScroll = 0;

    bool createAnimMode = false;

    float temp_newAnimStart = 0;
    float temp_newAnimEnd = 0;
    string temp_newAnimName = "";

    struct Animation
    {
        string a_name;
        float a_begin;
        float a_end;
        bool del = false;
    };

    std::vector<Animation> animations;

    sf::Texture tex_animmgr,tex_animnew,tex_animrmv,tex_animrow;
    sf::Texture tex_mdlmgr;

    sf::Sprite s_animmgr,s_animnew;
    sf::Sprite s_mdlmgr;

    sf::Sprite s_animrow[7],s_animrmv[7];
    sf::Text s_animrow_bg[7],s_animrow_en[7],s_animrow_nm[7];

    ///TEMPORARY
    float oldrot = 0;

    string directory = "";

    bool buttons_loaded = false;
    sf::RectangleShape r_selected;

    Editor();
    std::string OpenFile();
    std::string SaveFile();
    void setPositions(float time);
    void saveAnim();
    void loadAnim(std::string data, P4A handle);
    void Draw(sf::RenderWindow& window);
};

#endif // EDITOR_H
