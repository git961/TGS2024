#pragma once
#include "Switch.h"
#include "AttackCheck.h"

class Switch;
class AttackCheck;

class Lift:
    public ObjectBase
{
private:
    Switch *switch_object;
    
    int lift_img;
    bool canmove_flg;//動いて良いか？
    bool down_flg;//下にさがってもいいか

    float screen_position_x;
    float screen_position_y;

    float move_y;//y座標の増加量
    float up_max_y;//y座標の移動の限界座標入れるよう
    float down_max_y;//y座標の移動の限界座標入れるよう


public:
    Lift(float set_x, float set_y);
    ~Lift();

    void Update(AttackCheck* ac);
    void Draw() const;

    void SetCanMove(bool set_flg) { canmove_flg = set_flg; }
    void SetScreenPos(float set_x, float set_y) { screen_position_x = set_x; screen_position_y = set_y; }
};

