#pragma once
#include "ObjectBase.h"
#include "Define.h"
#include <math.h>

class FallingRock :
    public ObjectBase
{
private:
    int rock_img;//岩画像読込
    int rock_effect_img[10];//岩画像読込

    int anim_cnt;
    int rock_img_num;
    double angle;
    double degree;
    float speed;

    int rock_state;
    bool landing_flg;

    int shake_x1;
    int shake_x2;


public:
    FallingRock();
    ~FallingRock();
    void Update();
    void Draw() const;

    bool GetLanding() { return landing_flg; }

};

