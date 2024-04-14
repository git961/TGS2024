#include "GameMainScene.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

//画面の中央を座標に入れる
static cameraposition camera_pos{ SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f };

static cameraposition screen_origin_position = {
	camera_pos.x - SCREEN_WIDTH / 2.0f,
	camera_pos.y - SCREEN_HEIGHT / 2.0f
};


GameMainScene::GameMainScene() {
	player=new Player;

	enemy = new Enemy(walk);
	ac = new AttackCheck;
	checkhit = false;
	enemy_damage_once=false;

	//back.png
	back_img=LoadGraph("back.png", TRUE);

	//カメラ座標は上の代入で座標真ん中取ってるから
	//それを左上の原点に変換するヤツ->キャラベースのSetLocalPositionに続く
	cameraposition screen_origin_position = {
	camera_pos.x - SCREEN_WIDTH / 2.0f,
	camera_pos.y - SCREEN_HEIGHT / 2.0f
	};


}


GameMainScene::~GameMainScene() {
	delete enemy;
}

void GameMainScene::Update() {


	input.InputUpdate();
	fp.fpsUpdate();

	if (enemy != nullptr)
	{
		if (player->HitCheck(enemy->GetLocation(), enemy->GetWidth(), enemy->GetHeight()) == true) {
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
				if (ac->HitCheck(enemy->GetLocation(), enemy->GetWidth(), enemy->GetHeight()) == true) {
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
		player->SetLocalPosition(screen_origin_position.x,screen_origin_position.y);
		player->Update(this);
	}

	//プレイヤーの攻撃
	if (ac != nullptr) {
			ac->Update(this,player);
	}

	// エネミー更新処理
	if (enemy != nullptr)
	{
		enemy->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
		enemy->Update(this);
	}

	UpdateCamera(player->GetLocation());

	screen_origin_position = {
camera_pos.x - SCREEN_WIDTH / 2.0f,
camera_pos.y - SCREEN_HEIGHT / 2.0f
	};

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
	DrawGraph(camera_pos.x, camera_pos.y, back_img,false);
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


void GameMainScene::UpdateCamera(Vec2 player_pos)
{

	camera_pos.x = player_pos.x;
	camera_pos.y = player_pos.y;

	//ここで固定するのはcameraのｘｙ何で動いたのか意味わからん

	if (camera_pos.x  <= 0.0f)
	{
		camera_pos.x = 1;
	}
	else if (camera_pos.x >= 700)
	{
		camera_pos.x =690;
	}

	if (camera_pos.y - 720 / 2 <= 0.0f)
	{
		camera_pos.y = 720 / 2;
	}
	else if (camera_pos.y + 360 >= 0)
	{
		camera_pos.y = 360;
	}

}



AbstractScene* GameMainScene::Change() {
	//if (change == TRUE) {
	//	return new GameOverScene;
	//}
	return this;
}