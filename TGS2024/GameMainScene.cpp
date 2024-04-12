#include "GameMainScene.h"


GameMainScene::GameMainScene() {
	player=new Player;

	enemy = new Enemy * [10];

	ac = new AttackCheck;
	checkhit = false;
	enemy_damage_once=false;

	for (int i = 0; i < 10; i++)
	{
		enemy[i] = new Enemy(i);
	}

}


GameMainScene::~GameMainScene() {
	delete[] enemy;
}

void GameMainScene::Update() {
	input.InputUpdate();
	fp.fpsUpdate();

	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			if (player->HitCheck(enemy[i]->GetX(), enemy[i]->GetY(), enemy[i]->GetWidth(), enemy[i]->GetHeight()) == true) {
				checkhit = true;
			}
			else {
				checkhit = false;
			}

			//つるはしを振るってる時だけ
			if (player->GetAttacking() == true)
			{
				//ダメージを一回だけ与える
				if (enemy_damage_once == false)
				{
					//つるはしとエネミーと当たってるかのチェック
					if (ac->HitCheck(enemy[i]->GetX(), enemy[i]->GetY(), enemy[i]->GetWidth(), enemy[i]->GetHeight()) == true) {
						//checkhit = true;
						enemy[i]->Damege(1);
						enemy_damage_once = true;
					}
					else {
						//checkhit = false;
					}
				}
			}
			else
			{
				//プレイヤーがつるはし振ってなかったら
				enemy_damage_once = false;
			}

		}
	}


	//プレイヤー
	if (player != nullptr)
	{
		player->Update(this);
	}

	//プレイヤーの攻撃
	if (ac != nullptr) {
			ac->Update(this,player);
	}

	for (int i = 0; i < 10; i++)
	{
		// エネミー更新処理
		if (enemy[i] != nullptr)
		{
			enemy[i]->Update(this);

			// エネミー削除処理
			if (enemy[i]->GetHp() <= 0)
			{
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
	}

#ifdef DEBUG
	//if (enemy == nullptr)
	//{
	//	enemy = new Enemy(walk);
	//}
#endif // DEBUG

	//for (int i = 0; i < 10; i++)
	//{
	//	if (enemy[i] != nullptr)
	//	{
	//		// エネミー削除処理
	//		if (enemy[i]->GetHp() <= 0)
	//		{
	//			delete enemy;
	//			enemy = nullptr;
	//		}

	//	}
	//}

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

		for (int i = 0; i < 10; i++)
		{
			// エネミー描画処理
			if (enemy[i] != nullptr)
			{
				enemy[i]->Draw();
			}
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