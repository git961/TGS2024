#pragma once
#include "ObjectBase.h"
class Switch :
    public ObjectBase
{
private:
    int switch_img[5];//画像用
    int event_switch_img[6];//画像用

    int img_num;
    bool anim_event_flg;
public:
    Switch(float set_x,float set_y);
    ~Switch();
    void Update(GameMainScene* gamemain);
    void Draw()const;
    void SetY(float set_y) { world.y = set_y; }
    void SetX(float set_x) { world.x = set_x; }
    void SetImgNum(int set_num) { img_num = set_num; }
    void SetEventFlg(bool set_flg) { anim_event_flg = set_flg; }
};

