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
    bool black_out_flg;

    int shake_x1;
    int shake_x2;

    int rocks_fall_sound;//岩が落ちる音
    int roll_sound;//転がる音

public:
    FallingRock();
    ~FallingRock();
    void Update(GameMainScene* gamemain) override;
    void AnimUpdate();
    void Draw() const override;
    void HitReaction(ObjectType set_type) override;

    bool GetLanding() { return landing_flg; }
    bool GetBlackOut() { return black_out_flg; }

};

