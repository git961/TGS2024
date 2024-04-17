#include "GameMainScene.h"


//画面の中央を座標に入れる
static cameraposition camera_pos{ SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f };

static cameraposition screen_origin_position = {
	camera_pos.x - SCREEN_WIDTH / 2.0f,
	camera_pos.y - SCREEN_HEIGHT / 2.0f
};


GameMainScene::GameMainScene() {
	player=new Player;

	enemy = new Enemy * [10];
	rolling_enemy = new RollingEnemy;

	ac = new AttackCheck;
	checkhit = false;
	enemy_damage_once=false;

	mapio = new MapIo;
	//back.png
	back_img=LoadGraph("image/back.png", TRUE);

	//カメラ座標は上の代入で座標真ん中取ってるから
	//それを左上の原点に変換するヤツ->キャラベースのSetLocalPositionに続く
	cameraposition screen_origin_position = {
	camera_pos.x - SCREEN_WIDTH / 2.0f,
	camera_pos.y - SCREEN_HEIGHT / 2.0f
	};

	mapio->LoadMapData();
	//stage_block = new StageBlock;


	for (int i = 0; i < 10; i++)
	{
		enemy[i] = new Enemy(i);
	}

}


GameMainScene::~GameMainScene() {
	delete[] enemy;
	delete rolling_enemy;
}

void GameMainScene::Update() {
#ifdef DEBUG
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		mapio->SaveMapData();

	}
	else {
		mapio->InputTest(this);

	}
#endif // DEBUG

	input.InputUpdate();
	fp.fpsUpdate();

	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			// 歩行敵との当たり判定
			if (player->HitCheck(enemy[i]->GetLocation(), enemy[i]->GetWidth(), enemy[i]->GetHeight()) == true) {
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
					if (ac->HitCheck(enemy[i]->GetLocation(), enemy[i]->GetWidth(), enemy[i]->GetHeight()) == true) {//checkhit = true;
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

	// 転がる敵との当たり判定
	if (rolling_enemy != nullptr)
	{
		// 歩行敵との当たり判定
		if (player->HitCheck(rolling_enemy->GetLocation(), rolling_enemy->GetWidth(), rolling_enemy->GetHeight()) == true) {
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
				if (ac->HitCheck(rolling_enemy->GetLocation(), rolling_enemy->GetWidth(), rolling_enemy->GetHeight()) == true) {//checkhit = true;
					rolling_enemy->Damege(1);
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

	for (int i = 0; i < 10; i++)
	{
		// エネミー更新処理
		if (enemy[i] != nullptr)
		{
			enemy[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

			enemy[i]->Update(this);

			// エネミー削除処理
			if (enemy[i]->GetHp() <= 0)
			{
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
	}

	// 転がる敵更新処理
	if (rolling_enemy != nullptr)
	{
		rolling_enemy->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

		rolling_enemy->Update(this);

		if (rolling_enemy->GetHp() <= 0)
		{
			delete rolling_enemy;
			rolling_enemy = nullptr;
		}
	}

	UpdateCamera(player->GetWorldLocation());

	screen_origin_position = {
		camera_pos.x - SCREEN_WIDTH / 2.0f,
		camera_pos.y - SCREEN_HEIGHT / 2.0f
	};


#ifdef DEBUG
	//if (enemy == nullptr)
	//{
	//	enemy = new Enemy(walk);
	//}

	if(rolling_enemy == nullptr)
	{
		rolling_enemy = new RollingEnemy;
	}
#endif // DEBUG

}

void GameMainScene::Draw() const {
	//DrawGraph(0, 0, back_img,FALSE);
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

		if (rolling_enemy != nullptr)
		{
			rolling_enemy->Draw();
		}

		//プレイヤー攻撃描画
		if (ac != nullptr) {
			if (ac->GetAttackFlg() == true)
			{
				ac->Draw();
			}
		}

#ifdef DEBUG


		DrawFormatString(300, 180, 0xffffff, "camerax: %f", camera_pos.x);
		DrawFormatString(300, 200, 0xffffff, "cameray: %f", camera_pos.y);
		DrawFormatString(300, 220, 0xffffff, "screen_origin_position.x: %f", screen_origin_position.x);
		DrawFormatString(300, 240, 0xffffff, "screen_origin_position.y: %f", screen_origin_position.y);

		mapio->Draw();
#endif // DEBUG
}


void GameMainScene::UpdateCamera(World world)
{
	//追従する相手のワールド座標をもらう
	camera_pos.x = world.x;
	camera_pos.y = world.y;


	//X軸のステージの内外判定

	//ワールド左端に到達したらカメラが移動しないように
	if (camera_pos.x - WINDOW_HALFX<= 0.0f)
	{
		camera_pos.x = WINDOW_HALFX;
	}
	else if (camera_pos.x +WINDOW_HALFX>= FIELD_WIDTH)
	{
		//ワールド右端に到達したらカメラが移動しないように
		camera_pos.x =FIELD_WIDTH - WINDOW_HALFX;
	}


	//Y軸のステージの内外判定

	//ワールドの底に到達したらカメラが移動しないように
	if (camera_pos.y -  WINDOW_HALFY<= 0.0f)
	{
		camera_pos.y = WINDOW_HALFY;
	}
	else if (camera_pos.y + WINDOW_HALFY >= FIELD_HEIGHT)
	{
		//ワールドのてっぺんに到達したらカメラが移動しないように
		camera_pos.y = FIELD_HEIGHT-WINDOW_HALFY;
	}

}



AbstractScene* GameMainScene::Change() {
	//if (change == TRUE) {
	//	return new GameOverScene;
	//}
	return this;
}