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
	fp.fpsUpdate();

	//プレイヤーが何かと当たってるかのチェック
	if (player->HitCheck(enemy->GetX(), enemy->GetY(), enemy->GetWidth(), enemy->GetHeight())==true) {
		checkhit = true;
	}
	else {
		checkhit = false;
	}

	//つるはしが何かと当たってるかのチェック

	//プレイヤー
	if (player != nullptr)
	{
		player->Update(this);
	}

	//プレイヤーの攻撃
	if (ac != nullptr) {
			ac->Update(this,player);
	}

}

void GameMainScene::Draw() const {
		DrawFormatString(0, 0, 0xffffff, "GameMain");
		fp.display_fps();

		if (checkhit == true)
		{
			DrawFormatString(0, 10, 0xffffff, "hit");
		}

		//プレイヤー描画
		if (player != nullptr)
		{
			player->Draw();
		}

		//敵描画
		if (enemy != nullptr)
		{
			enemy->Draw();
		}

		//プレイヤー攻撃描画
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