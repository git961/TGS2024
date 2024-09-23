#pragma once
#include "CharacterBase.h"
#include "GameMainScene.h"
#include "StageBlock.h"
#include "AnimScene.h"
#include "padinput.h"
#include "Enemy.h"

class StageBlock;
class AnimScene;
class Enemy;

enum PlayerState {
    NOMAL,//地面に居る：歩くのが可能
    ATTACK,
    WALK,
    HITDAMAGE,
    DYNAMITE,
    DEATH,
    PANIM,
    ASE,
    STOP
};

class Player :
    public CharacterBase
{
private:
    Input input;
    PlayerState player_state;
    int player_img[72];
    //int player_walk_img[10];
    //int player_attack_img[15];
    //int player_throw_img[15];
    //int player_death_img[15];
    int pickaxe_img[8];
    int pickaxe_effect[4];
    int soil_effect[2];

    //int player_ase_img[10];
    
    float curent_x;//元居たｘ
    float curent_y;//元居たy
    
    float set_speed;
    
    float limit_y;//落下の上限用
    bool fall_flg;//落ちているか？
    bool lift_hit_flg;//リフトに当たっているか？
    bool geyser_hit_flg;//間欠泉に当たっているか？
    bool magma_hit_flg;//マグマに当たっているか
    bool floorblock_hit_flg;//床ブロックに当たっているか
    bool fallingfloor_hit_flg;//落ちる床に当たっているか
    float vel;//初速度

    float img_down;//画像の表示位置を下げる用
    int p_imgnum;//プレイヤーの画像番号切り替え用
    //int p_nomal_num;

    int p_atk_imgnum;//つるはし画像切り替え用
    float pickaxe_add_x;//つるはしの画像ずらす用

    //int walk_num;//プレイヤ歩行画像切り替え用
    int walk_abs;//プレイヤ歩行画像切りかえ計算用
    float old_worldx;
    int fall_abs;//プレイヤ落下画像切りかえ計算用
    float old_worldy;

    int effect_num;//effectの画像番号切り替え用
    int anim_cnt;//画像切り替え用
    bool is_hit_enemy;//エネミーに当たったか

    int reset_timer;//攻撃をしばらくしなかった場合元に戻す


    float atk_cnt_timer;//攻撃発生してからとめるまでの時間をカウントする用
    int next_attackflg;//攻撃中もう一度ボタンが押されたら攻撃をする
    int attack_cnt;//何回攻撃ボタンを押したかカウント用
    int wait_atk_cnt;//もう一度攻撃できるようになるまでの時間カウント用
    bool wait_flg;//

    bool is_atk_putout;//攻撃判定を出すか？

    int atk_sound;//つるはし攻撃音
    int op_run_sound;//オープニング走る音
    int damage_sound;//被ダメージ音
    int throw_dynamite_sound;//ダイナマイト投げる音
    int death_sound;//死亡音


    //プレイヤーの状態
   // bool walk;//true:歩いてる false:止まってる
    bool attacking;//true:攻撃中 false:攻撃してない 


    //ダイナマイト投擲用

    int dyna_anmcnt;//ダイナマイト投擲アニメーション切り替え用
    //int dyna_throw_num;
    bool dyna_anm_start;
    bool atk_dynamite;//true:発射する false:発射してない 
    
    int dyna_stock_num;//残弾数
    int dyna_stock_cnt;//残弾補充のカウント


    //ダメージ受けた時に点滅させるよう
    bool hit_damage;//ダメージを受けた
    bool flash_start;
    bool flash_flg;//点滅させるフラグ
    int flash_cnt;

    float walk_velocity_x;

   //死亡アニメーション
    int death_anim_cnt;
   // int death_num;
    bool death_flg;//死んだよフラグ


    //int op_num;
    int op_cnt;

    bool tuto_anim_flg;
    int tuto_num;
    bool tuto_atk_flg;//つるはしのチュートリアル用フラグ
    int tuto_ui_num;//表示するUI
    bool rock_break_flg;
    int rock_cnt;
    int tuto_cnt;
    bool walk_stop_flg;
    bool tuto_anim_dynaflg;//カメラをダイナマイトに追従させる用
    bool start_flg;

    bool helmet_flg;//ヘルメットを落とすフラグ
    float helmet_down;
    int helmet_img;//

    // bool stop_walk_snd;             // 足音を止めるか？

    // エンド画面用
    int player_end_img[3];          // エンド画面でのプレイヤー画像
    int end_img_num;                // プレイヤーエンド画像の画像番号
    int end_anim_cnt;               // エンドアニメーション用カウント

    // エンドクレジット画面用
    int player_credits_img[8];          // クレジット画面でのプレイヤー画像
    int applause_img[4];                // 拍手画像
    int cracker_img[5];                 // クラッカー画像
    int ribbon_img[5];                  // クラッカーのリボン画像
    int credits_img_num;                // プレイヤークレジット画像の画像番号
    int ribbon_img_num;                 // クラッカーのリボンの画像番号
    int credits_anim_cnt;               // クレジットアニメーション用カウント
    int ribbon_anim_cnt;                // クラッカーのリボンアニメーション用カウント
    int cracker_anim_cnt;               // クラッカーアニメーション用カウント
    int credits_timer;                  // クレジット画面の経過時間
    bool facing_left_flg;               // 左向きか？
    bool push_b_flg;                    // Bボタンを押したか？
    int dash_anim_cnt;                  // push_bに向かって走るアニメーションカウント
    bool change_to_title_flg;           // シーンをタイトルに変更するか？
    int ribbon_x;                       // クラッカーのリボンx座標
    int ribbon_y;                       // クラッカーのリボンy座標
    bool set_ribbon_pos_flg;            // リボンの座標をセットしたか？
    int change_scene_cnt;               // タイトルへ遷移するカウント
    int credits_walk_cnt;               // クレジット画面の歩行アニメーションカウント
    bool walk_cnt_up_flg;               // 歩行アニメーションのカウントを増やすか？
    bool anim_end_flg;                  // プレイヤーのアニメーションが終わったか？

    int rest_move_count;//移動量が残っている時用
    
    bool stop_up_flg;//プレイヤーの上昇を止めるか？

    int lift_anim_cnt;//リフトアニメカウント用

public:
    Player();
    Player(float set_x,float set_y);
    ~Player();


    void Update(GameMainScene* gamemain);
    void Draw() const;

    //プレイヤー移動用
    void PlayerMove();
    void WalkAnim();
    void DeathAnim();
    void ThrowAnim();

    void PlayerFall();//プレイヤーが落下する処理
    void PlayerFallAnim();//落下中のプレイヤーアニメーション更新

    void PlayerAttack();
    void PlayerTutoAttack();
    void TutoWalkAnim();

    bool GetAttacking() { return is_atk_putout; }
    
    bool GetAtkDynamite() { return atk_dynamite; }
    void SetAtkDynamite(bool set_flg) { atk_dynamite=set_flg; }
    int GetDynaNum() { return dyna_stock_num; }

    float GetHp() { return hp; }

    bool GetDeathFlg() { return death_flg; }

    //足元になにもなかったら落ちる
    void SetFallFlg(bool set_flg) {
        fall_flg = set_flg;
    }

    void SetLiftHitFlg(bool set_flg) {lift_hit_flg = set_flg;}
    void SetGeyserHitFlg(bool set_flg) {geyser_hit_flg = set_flg;}
    void SetMagmaHitFlg(bool set_flg) {magma_hit_flg = set_flg;}
    void SetFallingFloorHitFlg(bool set_flg) {fallingfloor_hit_flg = set_flg;}

    //いる所によって落下する所を更新する
    void SetLimitY(float set_y) {
        //30px分開いてしまうのでプラスしている
        limit_y = set_y/*+30*/;
    }
    float GetLimitY() { return limit_y; }

    void SetEnemyHit(bool set_hitflg)
    {
        is_hit_enemy = set_hitflg;
    }

    void SetDamage(float damage) { hp = hp - damage; }

    void SetDamageFlg(bool set_damageflg) { hit_damage = set_damageflg; }

    void SetX(float set_x)
    {
        // 端に来たら跳ね返る
        if (world.x + width / 2 > set_x)
        {
            world.x = set_x - 64;
        }
    }

    //リフトのYをプレイヤーのワールド座標に入れる
    void SetY(float set_y)
    {
        if (floorblock_hit_flg == false)
        {
            world.y = set_y - 35.0f;
        }
    }

    void EventSetY(float set_y)
    {
         world.y = set_y - 35.0f;
    }

    void SetPlayerState(bool is_stop)
    {
        if (is_stop == true)
        {
            player_state = STOP;
        }
        else {
            player_state = NOMAL;
        }
    };

    PlayerState GetState() { return player_state; }

    void LiftEvent(int set_num);

    void OpAnimUpdate(AnimScene *anim_scene,int set_case);//最初のアニメーション用
    void TutorialAnimUpdate();//チュートリアル用アップデート
    void RespawnAnimUpdate();//復活するときのアニメーション用

    int GetTutoUiNum() { return tuto_ui_num; }
    void SetMoveStop(bool set_flg) { walk_stop_flg = set_flg; }
    bool GetTutoAnimDynaFlg() { return tuto_anim_dynaflg; }
    bool GetStartFlg() { return start_flg; }

    // エンド用
    void EndAnimUpdate();               // エンド画面用アニメーション更新処理
    void EndAnimDraw() const;           // エンド画面用アニメーション描画処理

    // エンドクレジット用
    void EndCreditsAnimUpdate();        // エンドクレジット画面用アニメーション更新処理
    void EndCreditsAnimDraw() const;    // エンドクレジット画面用アニメーション描画処理
    void PlayerMoveEndCredits();        // クレジット画面でのプレイヤー移動処理
    void ChangeSceneAnim();             // Bボタンでシーンを変えるときのアニメーション
    void DanceAnim();                   // コサックダンスアニメーション
    void ApplauseAnim();                // 拍手アニメーション
    void CrackerAnim();                 // クラッカーアニメーション
    void RibbonAnim();                  // リボンアニメーション
    bool GetAnimEndFlg() const { return anim_end_flg; }

    void SetPushBFlg() { push_b_flg = true; }       // Bボタン押したフラグの設定
    bool GetChangeToTitleFlg() const { return change_to_title_flg; }

    void CheckEdgeCage(float cage_x);       // 檻の端にプレイヤーがいるのか調べる

    void MoveBack();//床ブロックと当たっていたらプレイヤーの移動を戻す

    void HitMapChip(GameMainScene* gamemain);

    //下がめり込んでいるか
    void SinkCheck(GameMainScene* gamemain,float set_x, float set_y);
    void SinkCheckTop(GameMainScene* gamemain,float set_x, float set_y);
    void SinkCheckObject(float set_y);
    void SinkCheckX(float set_x,float set_half_width);

    void PushUpPlayer(float set_upper);

};
