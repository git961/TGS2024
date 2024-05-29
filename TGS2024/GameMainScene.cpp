#include "GameMainScene.h"


//画面の中央を座標に入れる
static cameraposition camera_pos{ SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f };

static cameraposition screen_origin_position =
{
	camera_pos.x - SCREEN_WIDTH / 2.0f,
	camera_pos.y - SCREEN_HEIGHT / 2.0f
};


GameMainScene::GameMainScene()
{


	//check_abs = 0;

	mapio = new MapIo;

	player = new Player();

	enemy = new Enemy * [ENEMYMAXNUM];
	rolling_enemy = new RollingEnemy;
	stage_block = new StageBlock * [map_blockmax_y * map_blockmax_x];

	ui = new UI(player->GetHp(),player->GetDynaNum());
	ac = new AttackCheck;

	walk_gem = new Gem * [ENEMYMAXNUM];
	roll_gem = nullptr;
	score = new Score;


	dynamite = new Dynamite * [DYNAMITE_MAXNUM];
	checkhit = false;
	enemy_damage_once = false;

	player_damage_once = false;
	//back.png
	back_img = LoadGraph("images/backimg.png", TRUE);
	//back_img = LoadGraph("images/background_test.png", TRUE);


	//game_state = TUTORIAL;
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

	block_count = 0;
	enemy_count = 0;

	mapio->LoadMapData();
	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		enemy[i] = nullptr;
	}

	if (mapio != nullptr) {
		//stage_block = new StageBlock(this->mapio);

		for (int i = 0; i < map_blockmax_y; i++)
		{
			for (int j = 0; j < map_blockmax_x; j++)
			{
				map_old_array[i][j] = mapio->GetMapData(i, j);

				switch (mapio->GetMapData(i, j))
				{
				case 1:
					stage_block[block_count++] = new StageBlock(1, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
					break;
				case 2:
					enemy[enemy_count++] = new Enemy(j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
					break;
				case 3:
					stage_block[block_count++] = new StageBlock(3, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
					break;
				case 4:
					stage_block[block_count++] = new StageBlock(4, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
					break;

				}

				/*
				//もしマップioのgetマップデータが１だったら
				if (mapio->GetMapData(i, j) == 1) {
					stage_block[block_count++] = new StageBlock(1,j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
				}

				if (mapio->GetMapData(i, j) == 3) {
					stage_block[block_count++] = new StageBlock(3, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
				}


				if (mapio->GetMapData(i, j) == 4) {
					stage_block[block_count++] = new StageBlock(4, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
				}

				if (mapio->GetMapData(i, j) == 2) {
					if (enemy_count < ENEMYMAXNUM)
					{
						enemy[enemy_count++] = new Enemy(j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
					}
				}

				*/

			}
		}
	}


	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		walk_gem[i] = nullptr;
	}

	for (int i = 0; i < DYNAMITE_MAXNUM; i++)
	{
		dynamite[i] = nullptr;
	}

	check_num = 0;

	pose_flg = false;

	walk_gem_score = 100;
	roll_gem_score = 500;
	goal_flg = false;


	shake_cnt=0;
	shake_x1=0;
	shake_x2=0;
	shake_flg=false;
	
	play_start_flg = false;

	// サウンド読込
	main_bgm = LoadSoundMem("sounds/bgm/gamemain.mp3");
	volume = 150;

	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, main_bgm);
}


GameMainScene::~GameMainScene()
{
	delete[] enemy;
	delete stage_block;
	delete player;
	delete mapio;
	delete ac;
	delete rolling_enemy;
	delete[] walk_gem;
	delete roll_gem;
	delete score;
}

void GameMainScene::Update()
{
	input.InputUpdate();
	fp.fpsUpdate();

	// ゲームメインbgmの音量設定
	if (game_state == POSE)
	{
		// ポーズ中は音量が小さくなる
		if (volume != 100)
		{
			volume = 100;
			ChangeVolumeSoundMem(volume, main_bgm);
		}
	}
	else
	{
		if (volume != 180)
		{
			volume = 180;
			ChangeVolumeSoundMem(volume, main_bgm);
		}
	}

	// ゲームメインbgmループ再生
	if (CheckSoundMem(main_bgm) == FALSE)
	{
		PlaySoundMem(main_bgm, DX_PLAYTYPE_LOOP);
	}

	switch (game_state)
	{
	case EDITOR:

		mapio->InputTest(this);

		for (int i = 0; i < ENEMYMAXNUM; i++)
		{
			enemy[i] = nullptr;
		}

		//右スティック押し込み
		if (input.CheckBtn(XINPUT_BUTTON_RIGHT_THUMB) == TRUE || CheckHitKey(KEY_INPUT_P) == TRUE)
		{
			//Inputを保存
			mapio->SaveMapData();
			block_count = 0;
			enemy_count = 0;

			//マップチップに反映する
			for (int i = 0; i < map_blockmax_y; i++)
			{
				for (int j = 0; j < map_blockmax_x; j++)
				{

					switch (mapio->GetMapData(i, j))
					{
					case 1:
						stage_block[block_count++] = new StageBlock(1, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 3:
						stage_block[block_count++] = new StageBlock(3, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 4:
						stage_block[block_count++] = new StageBlock(4, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
						break;

					}

					if (enemy_count < ENEMYMAXNUM)
					{

						if (mapio->GetMapData(i, j) == 2)
						{
							enemy[enemy_count++] = new Enemy(j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
						}

					}

				}
			}

			game_state = PLAY;
		}

		break;
	case TUTORIAL:
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			game_state = EDITOR;
		}
		//ワールド座標ースクリーン座標の原点してオブジェクトのスクリーン座標を出す計算
		location_x = world_x - screen_origin_position.x;
		location_y = world_y - screen_origin_position.y;



		//プレイヤー
		if (player != nullptr)
		{
			if (play_start_flg == true)
			{
				player->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
				player->Update(this);
			}
			else
			{

			}

		}

		//カメラとUIのアップデート
		if (player != nullptr) {

			UpdateCamera(player->GetWorldLocation());
		}

		for (int j = 0; j < block_count; j++)
		{
			if (stage_block[j] != nullptr)
			{
				stage_block[j]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
			}
		}

		screen_origin_position = {
		camera_pos.x - SCREEN_WIDTH / 2.0f,
		camera_pos.y - SCREEN_HEIGHT / 2.0f
		};

		break;
	case POSE:
		if (input.CheckBtn(XINPUT_BUTTON_START) == TRUE)
		{
			game_state = PLAY;
		}
		break;
	case GOAL:

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
#endif

		//ワールド座標ースクリーン座標の原点してオブジェクトのスクリーン座標を出す計算
		location_x = world_x - screen_origin_position.x;
		location_y = world_y - screen_origin_position.y;

		//押されたらポーズへ
		if (input.CheckBtn(XINPUT_BUTTON_START) == TRUE)
		{
			game_state = POSE;
		}

		// 歩行エネミーとプレイヤーの当たり判定
		for (int i = 0; i < ENEMYMAXNUM; i++)
		{
			if (enemy[i] != nullptr)
			{
				if (enemy[i]->GetHp() > 0)
				{
					if (player != nullptr)
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
									enemy[i]->SetStarDrawFlg(true);
									enemy[i]->SetPlayerWorldLocation(player->GetWorldLocation());
									enemy_damage_once = true;
								}
								else
								{
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
		}

		//ダイナマイトと歩行エネミーの当たり判定
		if (player != nullptr)
		{
			for (int i = 0; i < DYNAMITE_MAXNUM; i++)
			{
				if (dynamite[i] != nullptr)
				{
					for (int j = 0; j < ENEMYMAXNUM; j++) {
						if (enemy[j] != nullptr) {
							//ダイナマイトとエネミーと当たってるかのチェック
							if (dynamite[i]->GetDynamite() == false)
							{
								if (dynamite[i]->HitCheck(enemy[j]->GetWorldLocation(), enemy[j]->GetWidth(), enemy[j]->GetHeight()) == true)
								{
									dynamite[i]->SetDynamite(true);

								}
							}

							//ダイナマイトの爆発とエネミーの当たり判定
							if (dynamite[i]->Getdamage_flg() == true)
							{
								if (dynamite[i]->HitCheck(enemy[j]->GetWorldLocation(), enemy[j]->GetWidth(), enemy[j]->GetHeight()) == true)
								{
									dynamite[i]->SetEnemyX(enemy[j]->GetWorldLocation().x);
									dynamite[i]->DamageCalculation();

									enemy[j]->SetKnockBackStartFlg(true);
									enemy[j]->SetStarDrawFlg(true);
									enemy[j]->SetPlayerWorldLocation(player->GetWorldLocation());
									enemy[j]->Damege(dynamite[i]->GetAttack());





									//	check_abs = fabsf(dynamite[i]->GetWorldLocation().x - enemy[j]->GetWorldLocation().x);

									//	//爆発の中心座標から近いかとおいかでダメージが変わる
									//	if (fabsf(dynamite[i]->GetWorldLocation().x - enemy[j]->GetWorldLocation().x) < 35)
									//	{
									//		enemy[j]->Damege(30);
									//		// 歩行エネミーのノックバック処理
									//		enemy[j]->SetKnockBackStartFlg(true);
									//		enemy[j]->SetPlayerWorldLocation(player->GetWorldLocation());

									//	}
									//}
									////爆発の中心座標から近いかとおいかでダメージが変わる
									//if (fabsf(dynamite[i]->GetWorldLocation().x - enemy[j]->GetWorldLocation().x) < 100)
									//{
									//	enemy[j]->Damege(20);
									//	// 歩行エネミーのノックバック処理
									//	enemy[j]->SetKnockBackStartFlg(true);
									//	enemy[j]->SetPlayerWorldLocation(player->GetWorldLocation());

									//}
									//else if (fabsf(dynamite[i]->GetWorldLocation().x - enemy[j]->GetWorldLocation().x) < 200)
									//{
									//	enemy[j]->Damege(10);
									//}
								}
							}
						}
					}
				}
			}

			for (int i = 0; i < ENEMYMAXNUM; i++)
			{
				// エネミー更新処理
				if (enemy[i] != nullptr)
				{
					if (enemy[i]->GetWorldLocation().x > screen_origin_position.x - 100 && enemy[i]->GetWorldLocation().x < screen_origin_position.x + SCREEN_WIDTH + 100)
					{
						enemy[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
						enemy[i]->Update(this);
					}

					// エネミー削除処理
					if (enemy[i]->GetDeleteFlg() == true)
					{
						if (player != nullptr)
						{
							player->SetEnemyHit(false);
						}
						delete enemy[i];
						enemy[i] = nullptr;
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

			// 転がるエネミーが画面外に行ったら削除
			if (rolling_enemy != nullptr)
			{
				if (player != nullptr)
				{
					if (rolling_enemy->GetLocation().x > player->GetLocation().x + SCREEN_WIDTH)
					{
						delete rolling_enemy;
						rolling_enemy = nullptr;
					}
				}
			}

			// 歩行エネミーの宝石生成処理
			for (int i = 0; i < ENEMYMAXNUM; i++)
			{
				if (enemy[i] != nullptr)
				{
					if (enemy[i]->GetGemDropFlg() == true)
					{
						if (walk_gem[i] == nullptr)
						{
							walk_gem[i] = new Gem(enemy[i]->GetWorldLocation(), walk_gem_score);
							walk_gem[i]->SetPlayerWorldLocation(player->GetWorldLocation());
							enemy[i]->SetGemDropFlg(false);
						}
					}
				}
			}

			// 歩行エネミーの宝石更新処理
			for (int i = 0; i < ENEMYMAXNUM; i++)
			{
				//walk i=2番目でif文入った
				if (walk_gem[i] != nullptr)
				{
					walk_gem[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
					walk_gem[i]->Update(this);
				}
			}

			// 歩行エネミーの宝石とプレイヤーの当たり判定
			for (int i = 0; i < ENEMYMAXNUM; i++)
			{
				if (player != nullptr && walk_gem[i] != nullptr)
				{
					if (player->HitCheck(walk_gem[i]->GetWorldLocation(), walk_gem[i]->GetWidth(), walk_gem[i]->GetHeight()) == true)
					{
						score->SetScore(walk_gem[i]->GetGemScore());
						delete walk_gem[i];
						walk_gem[i] = nullptr;
					}
				}
			}

			// 転がるエネミーの宝石生成処理
			if (rolling_enemy != nullptr)
			{
				if (rolling_enemy->GetGemDropFlg() == true)
				{
					if (roll_gem == nullptr)
					{
						roll_gem = new Gem(rolling_enemy->GetWorldLocation(), roll_gem_score);
						roll_gem->SetFromRollingEnemyFlg(true);
						roll_gem->SetPlayerWorldLocation(player->GetWorldLocation());
					}
				}
			}

			// 転がるエネミーの宝石更新処理
			if (roll_gem != nullptr)
			{
				roll_gem->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
				roll_gem->Update(this);
			}

			// 転がるエネミーの宝石とプレイヤーの当たり判定
			if (player != nullptr && roll_gem != nullptr)
			{
				if (player->HitCheck(roll_gem->GetWorldLocation(), roll_gem->GetWidth(), roll_gem->GetHeight()) == true)
				{
					score->SetScore(roll_gem->GetGemScore());
					delete roll_gem;
					roll_gem = nullptr;
				}
			}


			// 転がるエネミーとプレイヤーの当たり判定
			if (rolling_enemy != nullptr)
			{
				if (rolling_enemy->GetHp() > 0)
				{
					if (player != nullptr)
					{

						// 転がるエネミーとの当たり判定
						if (player->HitCheck(rolling_enemy->GetWorldLocation(), rolling_enemy->GetWidth(), rolling_enemy->GetHeight()) == true)
						{
							checkhit = true;
						}
						else
						{
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
									enemy[j]->SetHitEnemyX(enemy[i]->GetWorldLocation().x);
									enemy[i]->SetHitEnemyX(enemy[j]->GetWorldLocation().x);
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

			// 歩行エネミーとプレイヤーの当たり判定
			for (int i = 0; i < ENEMYMAXNUM; i++)
			{
				if (enemy[i] != nullptr)
				{
					if (enemy[i]->GetHp() > 0)
					{
						// 歩行エネミーとの当たり判定
						if (player->HitCheck(enemy[i]->GetWorldLocation(), enemy[i]->GetWidth(), enemy[i]->GetHeight()) == true)
						{
							checkhit = true;
						}
						else
						{
							checkhit = false;
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
							}
						}
					}
				}


				//プレイヤーの攻撃
				if (ac != nullptr)
				{
					ac->Update(this, player);
				}

				for (int i = 0; i < DYNAMITE_MAXNUM; i++)
				{
					if (dynamite[i] != nullptr)
					{
						dynamite[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
						dynamite[i]->Update();

						if (dynamite[i]->Getdeath_flg() == true)
						{
							dynamite[i] = nullptr;
						}
					}


					//ダイナマイト作成
					if (player->GetAtkDynamite() == true)
					{
						if (dynamite[i] == nullptr)
						{
							dynamite[i] = new Dynamite(player->GetWorldLocation(), player->GetDirection());
							player->SetAtkDynamite(false);
						}
					}
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


			//カメラとUIのアップデート
			if (player != nullptr) {

				UpdateCamera(player->GetWorldLocation());

				//UIアップデート
				if (ui != nullptr)
				{
					ui->Update(player->GetHp(), player->GetDynaNum());
				}
			}

			screen_origin_position = {
				camera_pos.x - SCREEN_WIDTH / 2.0f,
				camera_pos.y - SCREEN_HEIGHT / 2.0f
			};

			for (int j = 0; j < block_count; j++)
			{
				if (stage_block[j] != nullptr)
				{
					stage_block[j]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

					if (player != nullptr)
					{

						if (stage_block[j]->GetBlockNum() == 3)
						{
							if (stage_block[j]->HitCheck(player->GetWorldLocation(), player->GetWidth(), player->GetHeight()) == true)
							{
								game_state = GOAL;
							}
						}

						if (stage_block[j]->GetBlockNum() == 4)
						{

							stage_block[j]->Update();

							//プレイヤが右向きだったら
							if (player->GetDirection() == 0)
							{
								player->HitCheckB(stage_block[j]->GetVertex(), stage_block[j]->GetWorldLocation());
							}

							//つるはしを振るってる時だけ
							if (player->GetAttacking() == true)
							{
								//ダメージを一回だけ与える
								if (rock_damage_once == false)
								{
									//つるはしとエネミーと当たってるかのチェック
									if (ac->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()) == true) {
										stage_block[j]->SetDamage(10);
										stage_block[j]->SetShakeFlg(true);
										rock_damage_once = true;
									}
								}
							}
							else
							{
								//プレイヤーがつるはし振ってなかったら
								rock_damage_once = false;
							}

							if (stage_block[j]->GetHp() <= 0)
							{
								stage_block[j] = nullptr;
							}


						}



					}


				}
			}


			if (player != nullptr && mapio != nullptr)
			{
				mapio->SetPlayerLocal(player->GetLocation().x);
				mapio->SetPlayerWorld(player->GetWorldLocation().x);
			}

			break;
	default:
		break;

		}

	}

}

void GameMainScene::Draw() const
{
	// 背景画像描画（仮）
	DrawGraph(location_x, location_y, back_img, FALSE);

	//DrawFormatString(0, 0, 0xffffff, "screen_origin_position.x: %f", screen_origin_position.x);
	//fp.display_fps();

	//if (checkhit == true)
	//{
	//	DrawFormatString(0, 10, 0xffffff, "hit");
	//}
	
	if (game_state == TUTORIAL)
	{

		//プレイヤー描画
		if (player != nullptr)
		{
			player->Draw();
		}
		//プレイヤー攻撃描画
		if (ac != nullptr) {
			if (ac->GetAttackFlg() == true)
			{
				ac->Draw();
			}
		}


		for (int j = 0; j < block_count; j++)
		{
			if (stage_block[j] != nullptr)
			{
				stage_block[j]->Draw();
			}
		}

		//if (ui != nullptr)
		//{
		//	ui->Draw();
		//}


	}
	else
	{

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
	if (ac != nullptr)
	{
		if (ac->GetAttackFlg() == true)
		{
			ac->Draw();
		}
	}

	for (int j = 0; j < block_count; j++)
	{
		if (stage_block[j] != nullptr)
		{
			stage_block[j]->Draw();
		}
	}

	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		// 歩行エネミーの宝石描画処理
		if (walk_gem[i] != nullptr)
		{
			walk_gem[i]->Draw();
		}
	}
	
	if (roll_gem != nullptr)
	{
		// 転がるエネミーの宝石描画処理
		roll_gem->Draw();
	}

	if (ui != nullptr)
	{
		ui->Draw();
	}

	if (score != nullptr)
	{
		score->Draw();
	}

	//ダイナマイト描画
	for (int i = 0; i < DYNAMITE_MAXNUM; i++)
	{
		if (dynamite[i] != nullptr)
		{
			dynamite[i]->Draw();
			DrawFormatString(300 * i , 0, 0xff0000, "tmp_abs: %f", dynamite[i]->GetTmpAbs());
		}
	}

	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		// エネミー描画処理
		if (enemy[i] != nullptr)
		{
			if (enemy[i]->GetWorldLocation().x > screen_origin_position.x - 100 && enemy[i]->GetWorldLocation().x < screen_origin_position.x + SCREEN_WIDTH + 100)
			{
				enemy[i]->Draw();
			}
		}
	}

	}
#ifdef DEBUG

	//DrawFormatString(300, 180, 0xffffff, "abs: %f", check_abs);
	//DrawFormatString(300, 180, 0xffffff, "camerax: %f", camera_pos.x);
	//DrawFormatString(300, 200, 0xffffff, "cameray: %f", camera_pos.y);
	//DrawFormatString(300, 220, 0xffffff, "screen_origin_position.x: %f", screen_origin_position.x);
	//DrawFormatString(300, 240, 0xffffff, "screen_origin_position.y: %f", screen_origin_position.y);
	//DrawFormatString(400, 150, 0xffffff, "enemyhit = %d", enemyhit);
	//DrawFormatString(30, 300, 0xffffff, "m_mode: %d", map_mode);
	DrawFormatString(30, 300, 0xffffff, "e_cnt: %d", enemy_count);


	switch (game_state)
	{
	case EDITOR:
		DrawFormatString(400, 100, 0xffffff, "EDITOR_NOW");
		mapio->Draw();

		break;
	case TUTORIAL:
		DrawFormatString(400, 100, 0xffffff, "TUTORIAL_NOW");
		break;
	case POSE:
		DrawFormatString(400, 100, 0xffffff, "POSE_NOW");
		break;
		
	case GOAL:
		DrawFormatString(400, 100, 0xffffff, "GOAL!!");
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
	if (camera_pos.x - WINDOW_HALFX <= 0.0f)
	{
		camera_pos.x = WINDOW_HALFX;
	}
	else if (camera_pos.x + WINDOW_HALFX >= FIELD_WIDTH)
	{
		//ワールド右端に到達したらカメラが移動しないように
		camera_pos.x = FIELD_WIDTH - WINDOW_HALFX;
	}


	//Y軸のステージの内外判定

	//ワールドの底に到達したらカメラが移動しないように
	if (camera_pos.y - WINDOW_HALFY <= 0.0f)
	{
		camera_pos.y = WINDOW_HALFY;
	}
	else if (camera_pos.y + WINDOW_HALFY >= FIELD_HEIGHT)
	{
		//ワールドのてっぺんに到達したらカメラが移動しないように
		camera_pos.y = FIELD_HEIGHT - WINDOW_HALFY;
	}

}



void GameMainScene::ShakeCamera(bool set_true, int set_num)
{
	if (set_num == 1)
	{
		shake_x1 = 5;
		shake_x2 = 10;
		if (set_true == true)
		{
			//画面の揺れ
			switch (shake_cnt)
			{
			case 0:
				screen_origin_position.x += shake_x1;
				break;
			case 10:
				screen_origin_position.x -= shake_x2;
				break;
			case 20:
				screen_origin_position.x = 0;
				break;
			case 30:
				screen_origin_position.x += shake_x1;
				break;
			case 40:
				screen_origin_position.x -= shake_x2;
				break;
			case 50:
				screen_origin_position.x = 0;
				shake_cnt = 0;
				break;
			}
			shake_cnt++;
		}
		else
		{
			shake_cnt = 0;
		}

	}
	else
	{
		if (set_true == true)
		{
			shake_x1 = 20;
			shake_x2 = 40;
			//画面の揺れ
			switch (shake_cnt)
			{
			case 0:
				screen_origin_position.x += shake_x1;
				break;
			case 10:
				screen_origin_position.x -= shake_x2;
				break;
			case 20:
				screen_origin_position.x = 0;
				break;
			case 30:
				screen_origin_position.x += shake_x1;
				break;
			case 40:
				screen_origin_position.x -= shake_x2;
				break;
			case 50:
				screen_origin_position.x = 0;
				shake_cnt = 0;
				break;
			}
			shake_cnt++;
		}
		else
		{
			shake_cnt = 0;
		}
	}
}


AbstractScene* GameMainScene::Change()
{
	//if (change == TRUE) {
	//	return new GameOverScene;
	//}
	return this;
}