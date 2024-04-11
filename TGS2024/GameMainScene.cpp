#include "GameMainScene.h"


GameMainScene::GameMainScene() {
	player=new Player;

	enemy = new Enemy(walk);

	ac = new AttackCheck;
	checkhit = false;
}


GameMainScene::~GameMainScene() {
	delete enemy;
}

void GameMainScene::Update() {
	input.InputUpdate();
	fp.fpsUpdate();

	if (enemy != nullptr)
	{
		if (player->HitCheck(enemy->GetX(), enemy->GetY(), enemy->GetWidth(), enemy->GetHeight()) == true) {
			checkhit = true;
		}
		else {
			checkhit = false;
		}
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

	// エネミー更新処理
	if (enemy != nullptr)
	{
		enemy->Update(this);
	}

#ifdef DEBUG
	if (input.CheckBtn(XINPUT_BUTTON_A) == TRUE)
	{
		enemy->Damege(2);
	}
	if (enemy == nullptr)
	{
		enemy = new Enemy(walk);
	}
#endif // DEBUG

	if (enemy != nullptr)
	{
		// エネミー削除処理
		if (enemy->GetHp() <= 0)
		{
			delete enemy;
			enemy = nullptr;
		}

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

		// エネミー描画処理
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