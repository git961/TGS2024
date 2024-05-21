#pragma once

#include "CharacterBase.h"
#include "GameMainScene.h"

class GameMainScene;

class Jem : public CharacterBase
{
private:
	int jem_img;          // 宝石画像

	//float enemy_x;			// 敵の死亡座標
	//float enemy_y;			// 敵の死亡座標

public:
	Jem(World set_world);
	~Jem();

	void Update(GameMainScene* gamemain);
	void Draw() const;

	//// set関数
	//void SetEnemyWorldLocation(World set_world)
	//{
	//	enemy_x = set_world.x;
	//	enemy_y = set_world.y;
	//}
};