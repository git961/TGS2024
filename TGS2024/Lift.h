#pragma once
#include "Switch.h"
#include "AttackCheck.h"
#include "Player.h"

class Switch;
class AttackCheck;
class Player;

class Lift : public ObjectBase
{
private:
    Switch *switch_object;
    
    int lift_img;
    bool anim_start_flg;//
    bool canmove_flg;//動いて良いか？
    bool down_flg;//下にさがってもいいか

    float check_inside_x;//プレイヤーが近くに居るかのチェック用

    float screen_position_x;
    float screen_position_y;

    float shift_y;//リフトの座標ずらす用
    float shift_img_y;//画像の座標ずらす用

    float move_y;//y座標の増加量
    float up_max_y;//y座標の移動の限界座標入れるよう
    float down_max_y;//y座標の移動の限界座標入れるよう

    int anim_cnt;
    int img_num;


public:
    Lift(float set_x, float set_y);
    ~Lift();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    void UpAnim();
    void DownAnim();

    bool GetDownFlg() { return down_flg; }
    bool GetCanMoveFlg() { return canmove_flg; }

    void SetUpMaxY(float set_y) { up_max_y = set_y; }
    void SetCanMove(bool set_flg) { canmove_flg = set_flg; }
    void SetDownFlg(bool set_flg) { down_flg = set_flg; }
    void SetScreenPos(float set_x, float set_y) { screen_position_x = set_x; screen_position_y = set_y; }
};

