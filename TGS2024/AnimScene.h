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
    int alpha;

    int anim_scene;

    int back_img;//背景入れるよう
    int block_img;//ブロック画像
    int black_img;//黒の画像
    int p_backimg[4];
    int p_ase_img;

    bool ase_flg;
    int p_backimg_num;
public:
    AnimScene();
    ~AnimScene();

    void UpdateCamera();

    void ShakeCamera(bool set_true);
    void Update() override;
    void Draw() const override;
    AbstractScene* Change() override;

    void SetAnimScene(int set_scenenum) { anim_scene = set_scenenum; }
};

