#include "GameMainScene.h"


GameMainScene::GameMainScene() {
	player=new Player;
	enemy=new Enemy;
	ac = new AttackCheck;
	checkhit = false;
}


GameMainScene::~GameMainScene() {

}

void GameMainScene::Update() {
	input.InputUpdate();


	if (player->HitCheck(enemy->GetX(), enemy->GetY(), enemy->GetWidth(), enemy->GetHeight())==true) {
		checkhit = true;
	}
	else {
		checkhit = false;
	}

	if (player != nullptr)
	{
		player->Update(this);
	}

	if (ac != nullptr) {
			ac->Update(this,player);
	}

}

void GameMainScene::Draw() const {
		DrawFormatString(0, 0, 0xffffff, "GameMain");

		if (checkhit == true)
		{
			DrawFormatString(0, 10, 0xffffff, "hit");
		}

		if (player != nullptr)
		{
			player->Draw();
		}

		if (enemy != nullptr)
		{
			enemy->Draw();
		}

		if (ac != nullptr) {
			if (ac->GetAttackFlg() == true)
			{
				ac->Draw();
			}
		}
}

AbstractScene* GameMainScene::Change() {
	//if (change == TRUE) {
	//	return new GameOverScene;
	//}
	return this;
}