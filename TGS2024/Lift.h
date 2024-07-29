#pragma once
#include "LiftBase.h"
class Lift :
    public LiftBase
{
private:
    int lift_img;
    bool canmove_flg;//動いて良いか？
public:
    Lift(float set_x, float set_y);
    ~Lift();

    void Update();
    void Draw() const;

    void SetCanMove(bool set_flg) { canmove_flg = set_flg; }
};

