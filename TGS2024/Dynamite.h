#pragma once
#include "ObjectBase.h"
#include "GameMainScene.h"
#include "Player.h"
class GameMainScene;
class Player;

class Dynamite :
    public ObjectBase
{
private:
    float move_x;
    float rotation;
    int dynamite_img;
    int explosion_img[10];
    int dynamite_flg;
    int direction;

    int explosion_num;
    int explosion_cnt;

public:
    Dynamite(World set_xy,int set_direction);
    ~Dynamite();
    void Update();
    void Draw() const;

    void SetDynamite(bool set_flg) { dynamite_flg = set_flg; }
    bool GetDynamite() { return dynamite_flg; }
};

