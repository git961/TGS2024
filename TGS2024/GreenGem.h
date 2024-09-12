#pragma once
#include "CharacterBase.h"
#include "GameMainScene.h"

class GreenGem :
    public CharacterBase
{
private:
	int gem_img[5];				// 宝石画像
	int effect_img[4];			// ゲットしたときのエフェクト
	int gem_score;				// 宝石のスコア
	int count;					// sin用
	int move_x_timer;			// 座標xが動く時間
	double size;				// 画像の大きさ

	int get_gem_sound;			// 宝石ゲットse
	int drop_sound;				// 出現時se
	bool play_drop_sound;       // 1回だけサウンドを鳴らす用
	bool play_get_sound;        // 1回だけサウンドを鳴らす用

	float player_x;
	float player_y;

	bool just_generated;		// 宝石が生成された瞬間か？
	bool from_rolling_enemy;	// 転がるエネミーからドロップしたか？
	bool is_delete;				// 削除してもいいか？

	int anim_cnt;
	int anim_num;
	int effect_num;				// エフェクト画像番号
	int effect_anim_cnt;		// 取得時エフェクトの表示時間
	bool draw_effect;			// エフェクトを表示するか？

public:
	GreenGem(World set_world, int set_score);
	~GreenGem();

	void Update(GameMainScene* gamemain);
	void Draw() const;

private:
	void GemAnim();					// 宝石のアニメーション
	void ChangeSize();				// 生成時の宝石の大きさ変更処理
	void MoveX();					// 生成時のx座標の動き
	void ControlPosition();			// 画面外にでないように
	void GemSway();					// 宝石が上下に揺れる処理

public:
	void PlayGetSound();			// 宝石取得seを鳴らす処理

	void SetPlayerWorldLocation(World set_world)
	{
		player_x = set_world.x;
		player_y = set_world.y;
	}
	void SetFromRollingEnemyFlg(bool set_flg) { from_rolling_enemy = set_flg; }

	int GetGemScore() const { return gem_score; }
	bool GetDeleteFlg() const { return is_delete; }
	bool GetPlaySoundFlg() const { return play_get_sound; }

};

