#include "GameMainScene.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


GameMainScene::GameMainScene() {
	player=new Player;

	enemy = new Enemy(walk);
	camera_x = 0;
	camera_y = 0;
	ac = new AttackCheck;
	checkhit = false;
	enemy_damage_once=false;
}


GameMainScene::~GameMainScene() {
	delete enemy;
}

void GameMainScene::Update() {

	UpdateCamera();
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

		//つるはしを振るってる時だけ
		if (player->GetAttacking() == true)
		{
			//ダメージを一回だけ与える
			if (enemy_damage_once == false)
			{
				//つるはしとエネミーと当たってるかのチェック
				if (ac->HitCheck(enemy->GetX(), enemy->GetY(), enemy->GetWidth(), enemy->GetHeight()) == true) {
					//checkhit = true;
					enemy->Damege(1);
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


	//プレイヤー
	if (player != nullptr)
	{
		player->SetLocalPosition(camera_x, camera_y);
		player->Update(this);
	}

	//プレイヤーの攻撃
	if (ac != nullptr) {
			ac->Update(this,player);
	}

	// エネミー更新処理
	if (enemy != nullptr)
	{
		enemy->SetLocalPosition(camera_x, camera_y);
		enemy->Update(this);
	}

#ifdef DEBUG
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


void GameMainScene::UpdateCamera()
{

	CameraSetLocation(player->GetX(), player->GetY());

}

void GameMainScene::CameraSetLocation(float set_x, float set_y)
{

	camera_x = set_x - (SCREEN_WIDTH / 2);
	camera_y = set_y - (SCREEN_HEIGHT / 2);

}



AbstractScene* GameMainScene::Change() {
	//if (change == TRUE) {
	//	return new GameOverScene;
	//}
	return this;
}