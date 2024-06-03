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
    float alpha;

    int anim_scene;

    int cnt;

    int fps_cnt;
    int fps;

    int back_img;//背景入れるよう
    int block_img;//ブロック画像
    int black_img;//黒の画像
    int p_backimg[4];
    int p_ase_img;
    int p_exc_img;

    bool ase_flg;
    bool exc_flg;
    int p_backimg_num;

    bool shake_flg;
    bool run_flg;

    bool next_scene_flg;

    int cloth_rubbing_sound;//布擦れse
    int shake_sound;//揺れse
    int anim_bgm;
    int op_sad_sound;//悲しい音
    bool play_sad_sound;
public:
    AnimScene();
    ~AnimScene();


    void ShakeCamera(bool set_true,int set_num);
    void Update() override;
    void Draw() const override;
    AbstractScene* Change() override;

    void SetAnimScene(int set_scenenum) { anim_scene = set_scenenum; }
    void SetShakeFlg(bool set_flg) { shake_flg=set_flg; }
    void SetRun(bool set_flg) { run_flg=set_flg; }
    void SetExc(bool set_flg) { exc_flg=set_flg; }
};

