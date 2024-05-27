#pragma once
#include "AbstractScene.h"
#include "FallingRock.h"
#include "Player.h"

class FallingRock;
class Player;


class AnimScene :
    public AbstractScene
{
private:

    struct cameraposition
    {
        float x;
        float y;

    };

    cameraposition camera_pos;

    cameraposition screen_origin_position;


    FallingRock *fallingrock;
    Player* player;

    float x, y;
    int shake_cnt;
    int shake_x1;
    int shake_x2;

    int back_img;//背景入れるよう
    int block_img;//ブロック画像
public:
    AnimScene();
    ~AnimScene();

    void UpdateCamera();


    void Update() override;
    void Draw() const override;
    AbstractScene* Change() override;
};

