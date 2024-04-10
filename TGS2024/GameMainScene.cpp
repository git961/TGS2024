#include "GameMainScene.h"


GameMainScene::GameMainScene() {
	player=new Player;
	enemy=new Enemy;
	checkhit = false;
}


GameMainScene::~GameMainScene() {

}

void GameMainScene::Update() {
	input.InputUpdate();


	if (player->HitCheck(enemy->GetEnemyX(), enemy->GetEnemyY(), enemy->GetEnemyWidth(), enemy->GetEnemyHeight())==true) {
		checkhit = true;
	}
	else {
		checkhit = false;
	}

	if (player != nullptr)
	{
		player->Update(this);
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
}

AbstractScene* GameMainScene::Change() {
	//if (change == TRUE) {
	//	return new GameOverScene;
	//}
	return this;
}