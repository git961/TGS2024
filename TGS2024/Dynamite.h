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
public:
    Dynamite(World set_xy);
    ~Dynamite();
    void Update();
    void Draw() const;
};

