#pragma once
#include "ObjectBase.h"
class Switch :
    public ObjectBase
{
private:
    bool canmove_flg;//動くか
    bool up_down_flg;//上に居るか？
    int switch_img;//画像用
    float limit_y;//どこまで移動するかの上限値
public:
    Switch();
    ~Switch();
    void Update();
    bool GetCanMoveFlg() { return canmove_flg; }
    void SetLimit_y(float Set_y) { limit_y = Set_y; }
};

