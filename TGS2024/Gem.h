#pragma once

#include <math.h>
#include "CharacterBase.h"
#include "GameMainScene.h"

class GameMainScene;

class Gem : public CharacterBase
{
private:
	int gem_img;			// 宝石画像
	int gem_score;			// 宝石のスコア
	int count;				// sin用
	int move_x_timer;		// 座標xが動く時間
	double size;			// 画像の大きさ

	int get_gem_sound;		// 宝石ゲットse
	int drop_sound;			// 出現時se
	//int sparkling_sound;	// キラキラse
	bool play_drop_sound;        // 1回だけサウンドを鳴らす用

	float player_x;
	float player_y;

	bool just_generated;
	bool from_rolling_enemy;	// 転がるエネミーからドロップしたか？

	//bool is_deete;
public:
	Gem(World set_world, int set_score);
	~Gem();

	void Update(GameMainScene* gamemain);
	void Draw() const;

	void PlayGetSound();

	void SetPlayerWorldLocation(World set_world)
	{
		player_x = set_world.x;
		player_y = set_world.y;
	}
	void SetFromRollingEnemyFlg(bool set_flg){ from_rolling_enemy = set_flg; }

	int GetGemScore() const { return gem_score; }
	//bool GetDeleteFlg() const { return is_deete; }
};