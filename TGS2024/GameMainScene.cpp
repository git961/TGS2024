#include "GameMainScene.h"


//画面の中央を座標に入れる
static cameraposition camera_pos{ SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f };

static cameraposition screen_origin_position = {
	camera_pos.x - SCREEN_WIDTH / 2.0f,
	camera_pos.y - SCREEN_HEIGHT / 2.0f
};


GameMainScene::GameMainScene() {

	mapio = new MapIo;


	player=new Player();

	enemy = new Enemy * [ENEMYMAXNUM];
	rolling_enemy = new RollingEnemy;
	stage_block = new StageBlock * [map_blockmax_y * map_blockmax_x];


	ac = new AttackCheck;
	checkhit = false;
	enemy_damage_once=false;

	player_damage_once = false;
	//back.png
	back_img=LoadGraph("images/background_test.png", TRUE);


	game_state = PLAY;

	//enemyhit = false;		// 当たっていない

	// 背景画像ローカル座標
	location_x = 0.0f;
	location_y = 0.0f;
	// 背景画像ワールド座標
	world_x = 0.0f;
	world_y = 0.0f;

	//カメラ座標は上の代入で座標真ん中取ってるから
	//それを左上の原点に変換するヤツ->キャラベースのSetLocalPositionに続く
	cameraposition screen_origin_position = {
	camera_pos.x - SCREEN_WIDTH / 2.0f,
	camera_pos.y - SCREEN_HEIGHT / 2.0f
	};
	count = 0;

	mapio->LoadMapData();
	if (mapio != nullptr) {
		//stage_block = new StageBlock(this->mapio);

		for (int i = 0; i < map_blockmax_y; i++)
		{
			for (int j = 0; j < map_blockmax_x; j++)
			{
				//もしマップioのgetマップデータが１だったら

				if (mapio->GetMapData(i, j) == 1) {
					stage_block[count++] = new StageBlock(j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
				}
				//stage_blockdata[i][j] = mapio->GetMapData(i, j);
				//if (stage_blockdata[i][j] != 0)
				//{
				//	block_world.x[j] = j * BLOCKSIZE + BLOCKSIZE / 2;
				//	block_world.y[i] = i * BLOCKSIZE + BLOCKSIZE / 2;
				//}

			}
		}
	}

	gem = new Gem * [ENEMYMAXNUM];
	score = new Score;

	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		enemy[i] = new Enemy(i);
		gem[i] = nullptr;
	}

	check_num = 0;

	defeat_enemy_num = 0;
	pose_flg = false;
	map_mode = 0;				// 押されていない
}


GameMainScene::~GameMainScene() {
	delete[] enemy;
	delete stage_block;
	delete player;
	delete mapio;
	delete ac;
	delete rolling_enemy;
	delete[] gem;
	delete score;
}

void GameMainScene::Update() {


	input.InputUpdate();
	fp.fpsUpdate();

	switch (game_state)
	{
	case EDITOR:

			mapio->InputTest(this);
			
			//右スティック押し込み
			if (input.CheckBtn(XINPUT_BUTTON_RIGHT_THUMB) == TRUE)
			{
				//Inputを保存
				mapio->SaveMapData();
				count = 0;

				//マップチップに反映する
				for (int i = 0; i < map_blockmax_y; i++)
				{
					for (int j = 0; j < map_blockmax_x; j++)
					{
						//もしマップioのgetマップデータが１だったら

						if (mapio->GetMapData(i, j) == 1) {
							stage_block[count++] = new StageBlock(j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
						}
			

					}
				}

				game_state = PLAY;
			}

		break;
	case POSE:
		if (input.CheckBtn(XINPUT_BUTTON_START) == TRUE)
		{
			game_state=PLAY;
		}
		break;
	case PLAY:
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			game_state = EDITOR;
		}

#ifdef DEBUG
		if (rolling_enemy == nullptr)
		{
			// 転がるエネミーが消えたら新しく出現させる
			rolling_enemy = new RollingEnemy;
		}

		// 生成された歩行エネミーをすべて倒したら
		if (defeat_enemy_num == ENEMYMAXNUM)
		{
			// 歩行エネミーの生成
			for (int i = 0; i < ENEMYMAXNUM; i++)
			{
				if (enemy[i] == nullptr)
				{
					enemy[i] = new Enemy(i);
				}
			}
			defeat_enemy_num = 0;
		}
#endif

		//ワールド座標ースクリーン座標の原点してオブジェクトのスクリーン座標を出す計算
		location_x = world_x - screen_origin_position.x;
		location_y = world_y - screen_origin_position.y;

		if (input.CheckBtn(XINPUT_BUTTON_START) == TRUE)
		{
			game_state=POSE;
		}

		// 歩行エネミーとプレイヤーの当たり判定
		for (int i = 0; i < ENEMYMAXNUM; i++)
		{
			if (enemy[i] != nullptr)
			{
				if (enemy[i]->GetHp() > 0)
				{
					// 歩行エネミーとの当たり判定
					if (player->HitCheck(enemy[i]->GetWorldLocation(), enemy[i]->GetWidth(), enemy[i]->GetHeight()) == true) {
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
							if (ac->HitCheck(enemy[i]->GetWorldLocation(), enemy[i]->GetWidth(), enemy[i]->GetHeight()) == true) {//checkhit = true;
								enemy[i]->Damege(10);
								// 歩行エネミーのノックバック処理
								enemy[i]->SetKnockBackStartFlg(true);
								enemy[i]->SetPlayerWorldLocation(player->GetWorldLocation());
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
		}

		//プレイヤー
		if (player != nullptr)
		{
			player->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
			player->Update(this);

			//プレイヤーと歩行の敵との当たり判定
			for (int i = 0; i < ENEMYMAXNUM; i++)
			{
				if (enemy[i] != nullptr) {
					//もしプレイヤーとエネミーが当たったら
					if (player->HitCheck(enemy[i]->GetWorldLocation(), enemy[i]->GetWidth(), enemy[i]->GetHeight() == true))
					{
						if (enemy[i]->GetHp() > 0)
						{
							if (player_damage_once == false)
							{
								player_damage_once = true;
								player->SetDamageFlg(player_damage_once);
								player->SetDamage(10);
							}
							if (player->GetHp() < 0)
							{

							}
						}
					}
				}
			}


			//プレイヤーの攻撃
			if (ac != nullptr) {
				ac->Update(this, player);
			}

			//プレイヤーの死亡処理
			if (player->GetDeathFlg() == true)
			{
				delete player;
				player_damage_once = false;
				player = nullptr;
				player = new Player();
			}
		}


		for (int i = 0; i < ENEMYMAXNUM; i++)
		{
			// エネミー更新処理
			if (enemy[i] != nullptr)
			{
				enemy[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

				enemy[i]->Update(this);

				// エネミー削除処理
				if (enemy[i]->GetDeleteFlg() == true)
				{
					if (player != nullptr) {
						player->SetEnemyHit(false);
					}
					delete enemy[i];
					enemy[i] = nullptr;
					defeat_enemy_num++;
				}
			}
		}

		// 転がるエネミー更新処理
		if (rolling_enemy != nullptr)
		{
			rolling_enemy->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

			rolling_enemy->Update(this);

			if (rolling_enemy->GetDeleteFlg() == true)
			{
				delete rolling_enemy;
				rolling_enemy = nullptr;
			}
		}

		// 宝石生成処理
		for (int i = 0; i < ENEMYMAXNUM; i++)
		{
			if (enemy[i] != nullptr)
			{
				if (enemy[i]->GetGemDropFlg() == true)
				{
					if (gem[i] == nullptr)
					{
						gem[i] = new Gem(enemy[i]->GetWorldLocation());
						enemy[i]->SetGemDropFlg(false);
					}
				}
			}
		}

		// 宝石更新処理
		for (int i = 0; i < ENEMYMAXNUM; i++)
		{
			if (gem[i] != nullptr)
			{
				gem[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
				gem[i]->Update(this);
			}
		}

		// 宝石とプレイヤーの当たり判定
		for (int i = 0; i < ENEMYMAXNUM; i++)
		{
			if (player != nullptr && gem[i] != nullptr)
			{
				if (player->HitCheck(gem[i]->GetWorldLocation(), gem[i]->GetWidth(), gem[i]->GetHeight()) == true)
				{
					score->SetScore(gem[i]->GetGemScore());
					delete gem[i];
					gem[i] = nullptr;
				}
			}
		}


		if (player != nullptr) {
			UpdateCamera(player->GetWorldLocation());
		}

		screen_origin_position = {
			camera_pos.x - SCREEN_WIDTH / 2.0f,
			camera_pos.y - SCREEN_HEIGHT / 2.0f
		};

		// 転がるエネミーとプレイヤーの当たり判定
		if (rolling_enemy != nullptr)
		{
			if (rolling_enemy->GetHp() > 0)
			{
				if (player != nullptr) {

					// 転がるエネミーとの当たり判定
					if (player->HitCheck(rolling_enemy->GetWorldLocation(), rolling_enemy->GetWidth(), rolling_enemy->GetHeight()) == true) {
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
							if (ac->HitCheck(rolling_enemy->GetWorldLocation(), rolling_enemy->GetWidth(), rolling_enemy->GetHeight()) == true) {//checkhit = true;
								rolling_enemy->Damege(10);
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
		}

		// 歩行エネミー同士の当たり判定
		for (int i = 0; i < ENEMYMAXNUM; i++)
		{
			if (enemy[i] != nullptr && enemy[i]->GetHp() > 0)
			{
				for (int j = i + 1; j < ENEMYMAXNUM; j++)
				{
					if (enemy[j] != nullptr && enemy[j]->GetHp() > 0)
					{
						if (enemy[i]->HitCheck(enemy[j]->GetWorldLocation(), enemy[j]->GetWidth(), enemy[j]->GetHeight()) == true)
						{
							if (enemy[i]->GetIsKnockBack() == true)
							{
								// ノックバックしている敵に当たったら自身もノックバックを開始する
								enemy[j]->SetKnockBackStartFlg(true);
							}
							else
							{
								// 当たっていたら２体とも進行方向を反対に変更する
								enemy[j]->ChangeDirection();
								enemy[i]->ChangeDirection();
							}
							//enemyhit = true;
						}
						else
						{
							//enemyhit = false;
						}
					}
				}
			}
		}

		if (player != nullptr)
		{
			UpdateCamera(player->GetWorldLocation());
		}
		screen_origin_position = {
			camera_pos.x - SCREEN_WIDTH / 2.0f,
			camera_pos.y - SCREEN_HEIGHT / 2.0f
		};

		for (int j = 0; j < count; j++)
		{
			if (stage_block[j] != nullptr)
			{
				stage_block[j]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

				if (player != nullptr)
				{
					//if (player->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()) == true)
					//{
					//	//各頂点の座標を確保しておく
					//	player->HitCheckB(stage_block[j]->GetVertex(), stage_block[j]->GetWorldLocation());
					//	
					//}

					if (stage_block[j]->HitCheck(player->GetWorldLocation(), player->GetWidth(), player->GetHeight()) == true)
					{
						//各頂点の座標を確保しておく
						player->HitCheckB(stage_block[j]->GetVertex(), stage_block[j]->GetWorldLocation());

					}

				}
			}
		}


		break;
	default:
		break;
	}

	/*
	if (pose_flg == true)
	{
		if (input.CheckBtn(XINPUT_BUTTON_START) == TRUE)
		{
			pose_flg = false;
		}
	}
	else
	{

#ifdef DEBUG
	//if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	//{
	//	// テスト用
	//	map_mode = 1;

	//	mapio->SaveMapData();


	//}
	//else {
	//	// テスト
	//	map_mode = 0;

	//	mapio->InputTest(this);

	//	}

		if (rolling_enemy == nullptr)
		{
			// 転がるエネミーが消えたら新しく出現させる
			rolling_enemy = new RollingEnemy;
		}

		// 生成された歩行エネミーをすべて倒したら
		if (defeat_enemy_num == ENEMYMAXNUM)
		{
			// 歩行エネミーの生成
			for (int i = 0; i < ENEMYMAXNUM; i++)
			{
				if (enemy[i] == nullptr)
				{
					enemy[i] = new Enemy(i);
				}
			}
			defeat_enemy_num = 0;
		}


#endif // DEBUG
		/*
		//ワールド座標ースクリーン座標の原点してオブジェクトのスクリーン座標を出す計算
		location_x = world_x - screen_origin_position.x;
		location_y = world_y - screen_origin_position.y;

		if (input.CheckBtn(XINPUT_BUTTON_START) == TRUE)
		{
			pose_flg = true;
		}

		// 歩行エネミーとプレイヤーの当たり判定
		for (int i = 0; i < ENEMYMAXNUM; i++)
		{
			if (enemy[i] != nullptr)
			{
				if (enemy[i]->GetHp() > 0)
				{
					// 歩行エネミーとの当たり判定
					if (player->HitCheck(enemy[i]->GetWorldLocation(), enemy[i]->GetWidth(), enemy[i]->GetHeight()) == true) {
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
							if (ac->HitCheck(enemy[i]->GetWorldLocation(), enemy[i]->GetWidth(), enemy[i]->GetHeight()) == true) {//checkhit = true;
								enemy[i]->Damege(10);
								// 歩行エネミーのノックバック処理
								enemy[i]->SetKnockBackStartFlg(true);
								enemy[i]->SetPlayerWorldLocation(player->GetWorldLocation());
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
		}

		//プレイヤー
		if (player != nullptr)
		{
			player->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
			player->Update(this);

			//プレイヤーと歩行の敵との当たり判定
			for (int i = 0; i < ENEMYMAXNUM; i++)
			{
				if (enemy[i] != nullptr) {
					//もしプレイヤーとエネミーが当たったら
					if (player->HitCheck(enemy[i]->GetWorldLocation(), enemy[i]->GetWidth(), enemy[i]->GetHeight() == true))
					{
						if (enemy[i]->GetHp() > 0)
						{
							if (player_damage_once == false)
							{
								player_damage_once = true;
								player->SetDamageFlg(player_damage_once);
								player->SetDamage(10);
							}
							if (player->GetHp() < 0)
							{

							}
						}
					}
				}
			}


			//プレイヤーの攻撃
			if (ac != nullptr) {
				ac->Update(this, player);
			}

			//プレイヤーの死亡処理
			if (player->GetDeathFlg() == true)
			{
				delete player;
				player_damage_once = false;
				player = nullptr;
				player = new Player();
			}
		}


		for (int i = 0; i < ENEMYMAXNUM; i++)
		{
			// エネミー更新処理
			if (enemy[i] != nullptr)
			{
				enemy[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

				enemy[i]->Update(this);

				// エネミー削除処理
				if (enemy[i]->GetDeleteFlg() == true)
				{
					if (player != nullptr) {
						player->SetEnemyHit(false);
					}
					delete enemy[i];
					enemy[i] = nullptr;
					defeat_enemy_num++;
				}
			}
		}

		// 転がるエネミー更新処理
		if (rolling_enemy != nullptr)
		{
			rolling_enemy->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

			rolling_enemy->Update(this);

			if (rolling_enemy->GetDeleteFlg() == true)
			{
				delete rolling_enemy;
				rolling_enemy = nullptr;
			}
		}

		if (player != nullptr) {
			UpdateCamera(player->GetWorldLocation());
		}

		screen_origin_position = {
			camera_pos.x - SCREEN_WIDTH / 2.0f,
			camera_pos.y - SCREEN_HEIGHT / 2.0f
		};

		// 転がるエネミーとプレイヤーの当たり判定
		if (rolling_enemy != nullptr)
		{
			if (rolling_enemy->GetHp() > 0)
			{
				if (player != nullptr) {

					// 転がるエネミーとの当たり判定
					if (player->HitCheck(rolling_enemy->GetWorldLocation(), rolling_enemy->GetWidth(), rolling_enemy->GetHeight()) == true) {
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
							if (ac->HitCheck(rolling_enemy->GetWorldLocation(), rolling_enemy->GetWidth(), rolling_enemy->GetHeight()) == true) {//checkhit = true;
								rolling_enemy->Damege(10);
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
		}

		// 歩行エネミー同士の当たり判定
		for (int i = 0; i < ENEMYMAXNUM; i++)
		{
			if (enemy[i] != nullptr && enemy[i]->GetHp() > 0)
			{
				for (int j = i + 1; j < ENEMYMAXNUM; j++)
				{
					if (enemy[j] != nullptr && enemy[j]->GetHp() > 0)
					{
						if (enemy[i]->HitCheck(enemy[j]->GetWorldLocation(), enemy[j]->GetWidth(), enemy[j]->GetHeight()) == true)
						{
							if (enemy[i]->GetIsKnockBack() == true)
							{
								// ノックバックしている敵に当たったら自身もノックバックを開始する
								enemy[j]->SetKnockBackStartFlg(true);
							}
							else
							{
								// 当たっていたら２体とも進行方向を反対に変更する
								enemy[j]->ChangeDirection();
								enemy[i]->ChangeDirection();
							}
							//enemyhit = true;
						}
						else
						{
							//enemyhit = false;
						}
					}
				}
			}
		}

		if (player != nullptr)
		{
			UpdateCamera(player->GetWorldLocation());
		}
		screen_origin_position = {
			camera_pos.x - SCREEN_WIDTH / 2.0f,
			camera_pos.y - SCREEN_HEIGHT / 2.0f
		};

		for (int j = 0; j < count; j++)
		{
			if (stage_block[j] != nullptr)
			{
				stage_block[j]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

				if (player != nullptr)
				{
					//if (player->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()) == true)
					//{
					//	//各頂点の座標を確保しておく
					//	player->HitCheckB(stage_block[j]->GetVertex(), stage_block[j]->GetWorldLocation());
					//	
					//}

					if (stage_block[j]->HitCheck(player->GetWorldLocation(), player->GetWidth(), player->GetHeight()) == true)
					{
						//各頂点の座標を確保しておく
						player->HitCheckB(stage_block[j]->GetVertex(), stage_block[j]->GetWorldLocation());

					}

				}
			}
		}
		*/
	//}

}

void GameMainScene::Draw() const {
	// 背景画像描画（仮）
	DrawGraph(location_x, location_y, back_img,FALSE);

	//DrawFormatString(0, 0, 0xffffff, "GameMain");
	//fp.display_fps();

	//if (checkhit == true)
	//{
	//	DrawFormatString(0, 10, 0xffffff, "hit");
	//}

	//プレイヤー描画
	if (player != nullptr)
	{
		player->Draw();
	}

	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		// エネミー描画処理
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}

	if (rolling_enemy != nullptr)
	{
		// 転がるエネミー描画
		rolling_enemy->Draw();
	}

	//プレイヤー攻撃描画
	if (ac != nullptr) {
		if (ac->GetAttackFlg() == true)
		{
			ac->Draw();
		}
	}
		
	for (int j = 0; j < count; j++)
	{
		if (stage_block[j] != nullptr)
		{
			stage_block[j]->Draw();
		}
	}

	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		// 宝石描画処理
		if (gem[i] != nullptr)
		{
			gem[i]->Draw();
		}
	}

	if (score != nullptr)
	{
		score->Draw();
	}

#ifdef DEBUG

	//DrawFormatString(300, 180, 0xffffff, "camerax: %f", camera_pos.x);
	//DrawFormatString(300, 200, 0xffffff, "cameray: %f", camera_pos.y);
	//DrawFormatString(300, 220, 0xffffff, "screen_origin_position.x: %f", screen_origin_position.x);
	//DrawFormatString(300, 240, 0xffffff, "screen_origin_position.y: %f", screen_origin_position.y);
	//DrawFormatString(400, 150, 0xffffff, "enemyhit = %d", enemyhit);
	//DrawFormatString(30, 300, 0xffffff, "m_mode: %d", map_mode);
	
	switch (game_state)
	{
	case EDITOR:
		DrawFormatString(400, 100, 0xffffff, "EDITOR_NOW");
		mapio->Draw();

		break;
	case POSE:
		DrawFormatString(400, 100, 0xffffff, "POSE_NOW");
		break;
	case PLAY:
		DrawFormatString(400, 100, 0xffffff, "PLAY_NOW");
		break;
	default:
		break;
	}

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