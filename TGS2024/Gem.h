#pragma once

#include "CharacterBase.h"
#include "GameMainScene.h"

class GameMainScene;

class Gem : public CharacterBase
{
private:
	int gem_img;          // 宝石画像

	//float enemy_x;			// 敵の死亡座標
	//float enemy_y;			// 敵の死亡座標

public:
	Gem(World set_world);
	~Gem();

	void Update(GameMainScene* gamemain);
	void Draw() const;

	//// set関数
	//void SetEnemyWorldLocation(World set_world)
	//{
	//	enemy_x = set_world.x;
	//	enemy_y = set_world.y;
	//}
};