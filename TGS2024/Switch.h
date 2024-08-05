#pragma once
#include "ObjectBase.h"
class Switch :
    public ObjectBase
{
private:
    bool canmove_flg;//動くか
    bool on_flg;//スイッチがオンになっているか？
    bool up_down_flg;//上に居るか？
    int switch_img[5];//画像用
    float limit_y;//どこまで移動するかの上限値
public:
    Switch(float set_x,float set_y);
    ~Switch();
    void Update();
    void Draw()const;
    bool GetCanMoveFlg() { return canmove_flg; }
    void SetLimit_y(float Set_y) { limit_y = Set_y; }
    void SetX(float set_x) { world.x = set_x; }
    void SetOnFlg(bool set_flg) { on_flg = set_flg; }
};

