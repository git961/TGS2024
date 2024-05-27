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

	float player_x;
	float player_y;

	bool just_generated;
public:
	Gem(World set_world, int set_score);
	~Gem();

	void Update(GameMainScene* gamemain);
	void Draw() const;

	void SetPlayerWorldLocation(World set_world)
	{
		player_x = set_world.x;
		player_y = set_world.y;
	}

	int GetGemScore() const { return gem_score; }
};