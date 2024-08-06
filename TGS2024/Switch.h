#pragma once
#include "ObjectBase.h"
class Switch :
    public ObjectBase
{
private:
    int switch_img[5];//画像用

    int img_num;

public:
    Switch(float set_x,float set_y);
    ~Switch();
    void Update();
    void Draw()const;
    void SetY(float set_y) { world.y = set_y; }
    void SetX(float set_x) { world.x = set_x; }
    void SetImgNum(int set_num) { img_num = set_num; }
};

