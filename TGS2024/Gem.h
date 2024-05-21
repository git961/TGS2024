#pragma once

#include "CharacterBase.h"
#include "GameMainScene.h"

class GameMainScene;

class Gem : public CharacterBase
{
private:
	int gem_img;			// 宝石画像
	int gem_score;			// 宝石のスコア

public:
	Gem(World set_world);
	~Gem();

	void Update(GameMainScene* gamemain);
	void Draw() const;

	int GetGemScore() const { return gem_score; }
};