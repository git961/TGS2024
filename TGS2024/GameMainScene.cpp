﻿#include "GameMainScene.h"


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

	player = new Player(0.0f);

	enemy = new Enemy * [ENEMYMAXNUM];
	rolling_enemy = new RollingEnemy*[ROLLING_ENEMY_MAXNUM];
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


	game_state = TUTORIAL;
	//game_state = PLAY;

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
	rolling_enemy_cnt = 0;

	mapio->LoadMapData();
	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		enemy[i] = nullptr;
	}

	for (int i = 0; i < ROLLING_ENEMY_MAXNUM; i++)
	{
		rolling_enemy[i] = nullptr;
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
					enemy[enemy_count++] = new Enemy(j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2,false);
					break;
				case 3:
					stage_block[block_count++] = new StageBlock(3, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
					break;
				case 4:
					stage_block[block_count++] = new StageBlock(4, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
					break;
				case 5:
					stage_block[block_count++] = new StageBlock(5, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
					break;
				case 6:
					stage_block[block_count++] = new StageBlock(6, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
					break;
				case 7:
					stage_block[block_count++] = new StageBlock(7, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
					break;
				case 8:
					enemy[enemy_count++] = new Enemy(j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2,true);
					break;
				case 9:
					rolling_enemy[rolling_enemy_cnt++] = new RollingEnemy(j * BLOCKSIZE + BLOCKSIZE / 2);
					break;
				case 10:
					stage_block[block_count++] = new StageBlock(10, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
					break;
				case 11:
					stage_block[block_count++] = new StageBlock(11, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
					break;
				}


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

	clear_flg = false;
	gameover_flg = false;

	// サウンド読込
	main_bgm = LoadSoundMem("sounds/bgm/gamemain.mp3");
	volume = 150;

	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, main_bgm);
	camera_resetx.x = 0;
	camera_resetflg = false;
	camera_old_x = 0;
}


GameMainScene::~GameMainScene()
{
	delete[] enemy;
	delete stage_block;
	delete player;
	delete mapio;
	delete ac;
	delete[] rolling_enemy;
	delete[] walk_gem;
	delete roll_gem;
	delete score;

	// 画像削除
	DeleteGraph(back_img);

	// サウンド削除
	DeleteSoundMem(main_bgm);
}

void GameMainScene::Update()
{
	input.InputUpdate();
	//fp.fpsUpdate();

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
		if (volume != 150)
		{
			volume = 150;
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
		mapio->SetOriginPosx(screen_origin_position.x);

		//ワールド座標ースクリーン座標の原点してオブジェクトのスクリーン座標を出す計算
		location_x = world_x - screen_origin_position.x;
		location_y = world_y - screen_origin_position.y;

		if (CheckHitKey(KEY_INPUT_D) == TRUE)
		{
			screen_origin_position.x+=5;
		}
		if (CheckHitKey(KEY_INPUT_A) == TRUE)
		{
			screen_origin_position.x-=5;
		}

		if (mapio != nullptr)
		{
			mapio->SetOriginPosx(screen_origin_position.x);
			mapio->SetLocalPosx(location_x);
			mapio->SetWorldPosx(world_x);
		}

		for (int j = 0; j < block_count; j++)
		{
			if (stage_block[j] != nullptr)
			{
				stage_block[j]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
			}
		}

		

		for (int i = 0; i < ENEMYMAXNUM; i++)
		{
			enemy[i] = nullptr;
		}

		for (int i = 0; i < ROLLING_ENEMY_MAXNUM; i++)
		{
			rolling_enemy[i] = nullptr;
		}

		//右スティック押し込み
		if (input.CheckBtn(XINPUT_BUTTON_RIGHT_THUMB) == TRUE || CheckHitKey(KEY_INPUT_P) == TRUE)
		{
			//Inputを保存
			mapio->SaveMapData();
			block_count = 0;
			enemy_count = 0;
			rolling_enemy_cnt = 0;

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
					case 5:
						stage_block[block_count++] = new StageBlock(5, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 6:
						stage_block[block_count++] = new StageBlock(6, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 7:
						stage_block[block_count++] = new StageBlock(7, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 10:
						stage_block[block_count++] = new StageBlock(10, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 11:
						stage_block[block_count++] = new StageBlock(11, j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2);
						break;

					}

					if (enemy_count < ENEMYMAXNUM)
					{

						if (mapio->GetMapData(i, j) == 2)
						{
							enemy[enemy_count++] = new Enemy(j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2,false);
						}

						if (mapio->GetMapData(i, j) == 8)
						{
							enemy[enemy_count++] = new Enemy(j * BLOCKSIZE + BLOCKSIZE / 2, i * BLOCKSIZE + BLOCKSIZE / 2, true);

						}
					}

					if (rolling_enemy_cnt < ROLLING_ENEMY_MAXNUM)
					{
						if (mapio->GetMapData(i, j) == 9)
						{
							rolling_enemy[rolling_enemy_cnt++] = new RollingEnemy(j * BLOCKSIZE + BLOCKSIZE / 2);
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
		
		Tutorial();

		break;
	case POSE:
		if (input.CheckBtn(XINPUT_BUTTON_START) == TRUE)
		{
			game_state = PLAY;
		}
		break;
	case GOAL:
		clear_flg = true;
		break;
	case PLAY:
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			game_state = EDITOR;
		}

#ifdef DEBUG
		//if (rolling_enemy == nullptr)
		//{
		//	// 転がるエネミーが消えたら新しく出現させる
		//	//rolling_enemy = new RollingEnemy;
		//}
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


	
			}
		}

		//ダイナマイトと歩行エネミーの当たり判定
			for (int i = 0; i < DYNAMITE_MAXNUM; i++)
			{
				if (dynamite[i] != nullptr)
				{
					for (int j = 0; j < ENEMYMAXNUM; j++) {
						if (enemy[j] != nullptr&&enemy[j]->GetHp() > 0) {
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
						if (enemy[i]->GetFallEndFlg() == false) {
							enemy[i]->SetPlayerWorldLocation(player->GetWorldLocation());
						}
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
			for (int i = 0; i < ROLLING_ENEMY_MAXNUM; i++)
			{
				if (rolling_enemy[i] != nullptr)
				{
					rolling_enemy[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

					if (rolling_enemy[i]->GetWorldLocation().x > screen_origin_position.x-100  && rolling_enemy[i]->GetWorldLocation().x < screen_origin_position.x + SCREEN_WIDTH+30)
					{
						rolling_enemy[i]->Update(this);
					}
					if (rolling_enemy[i]->GetDeleteFlg() == true)
					{
						delete rolling_enemy[i];
						rolling_enemy[i] = nullptr;
					}
				}
			
				// 転がるエネミーが画面外に行ったら削除
				if (rolling_enemy[i] != nullptr)
				{
					if (player != nullptr)
					{
						//if (rolling_enemy[i]->GetLocation().x < player->GetLocation().x + SCREEN_WIDTH)
						if(rolling_enemy[i]->GetWorldLocation().x<camera_pos.x-SCREEN_WIDTH/2-100)
						{
							delete rolling_enemy[i];
							rolling_enemy[i] = nullptr;
						}
					}
				}
			}



			// 歩行エネミーの宝石生成処理
			for (int i = 0; i < ENEMYMAXNUM; i++)
			{
				if (player != nullptr && enemy[i] != nullptr)
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
					if (walk_gem[i]->GetPlaySoundFlg() == true)
					{
						if (player->HitCheck(walk_gem[i]->GetWorldLocation(), walk_gem[i]->GetWidth(), walk_gem[i]->GetHeight()) == true)
						{
							walk_gem[i]->PlayGetSound();
							score->SetScore(walk_gem[i]->GetGemScore());
						}
					}

					if (walk_gem[i]->GetDeleteFlg() == true)
					{
						delete walk_gem[i];
						walk_gem[i] = nullptr;
					}
				}
			}

			for (int i = 0; i < ROLLING_ENEMY_MAXNUM; i++)
			{
				// 転がるエネミーの宝石生成処理
				if (rolling_enemy[i] != nullptr)
				{
					if (rolling_enemy[i]->GetGemDropFlg() == true)
					{
						if (player != nullptr && roll_gem == nullptr)
						{
							roll_gem = new Gem(rolling_enemy[i]->GetWorldLocation(), roll_gem_score);
							roll_gem->SetFromRollingEnemyFlg(true);
							roll_gem->SetPlayerWorldLocation(player->GetWorldLocation());
						}
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
				if (roll_gem->GetPlaySoundFlg() == true)
				{
					if (player->HitCheck(roll_gem->GetWorldLocation(), roll_gem->GetWidth(), roll_gem->GetHeight()) == true)
					{
						roll_gem->PlayGetSound();
						score->SetScore(roll_gem->GetGemScore());
					}
				}

				if (roll_gem->GetDeleteFlg() == true)
				{
					delete roll_gem;
					roll_gem = nullptr;
				}
			}

			// 転がるエネミーとつるはしの当たり判定
			for (int i = 0; i < ROLLING_ENEMY_MAXNUM; i++)
			{
				if (rolling_enemy[i] != nullptr)
				{
					if (rolling_enemy[i]->GetHp() > 0)
					{
						if (player != nullptr)
						{

							// 転がるエネミーとの当たり判定
							if (player->HitCheck(rolling_enemy[i]->GetWorldLocation(), rolling_enemy[i]->GetWidth(), rolling_enemy[i]->GetHeight()) == true)
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
									if (ac->HitCheck(rolling_enemy[i]->GetWorldLocation(), rolling_enemy[i]->GetWidth(), rolling_enemy[i]->GetHeight()) == true) {//checkhit = true;
										rolling_enemy[i]->Damege(10);
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

				for (int i = 0; i < ROLLING_ENEMY_MAXNUM; i++)
				{
					if (rolling_enemy[i] != nullptr) {
						if (player->HitCheck(rolling_enemy[i]->GetWorldLocation(), rolling_enemy[i]->GetWidth(), rolling_enemy[i]->GetHeight() == true))
						{
							if (rolling_enemy[i]->GetHp() > 0)
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

				////プレイヤーの死亡処理
				//if (player->GetDeathFlg() == true)
				//{
				//	delete player;
				//	player_damage_once = false;
				//	player = nullptr;
				//	// ゲームオーバー判定
				//	gameover_flg = true;
				//	player = new Player();
				//}
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
					/*
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
					*/


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
									//つるはしと岩と当たってるかのチェック
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

						}
					}


				}

				/*
				//エネミーとブロックの当たり判定
				if (stage_block[j] != nullptr)
				{
					stage_block[j]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

					for (int i = 0; i < ENEMYMAXNUM; i++)
					{
						if (enemy[i] != nullptr)
						{
							if (stage_block[j]->GetBlockNum() == 1)
							{

								if (enemy[i]->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()) == true)
								{
									enemy[i]->HitCheckup(stage_block[j]->GetVertex(), stage_block[j]->GetWorldLocation());
								}
								
							}

							//エネミーの下のブロックの番号が1じゃなかったら
							if (enemy[i]->GetWorldLocation().y < stage_block[j]->GetWorldLocation().y-10)
							{
								if (stage_block[j]->GetBlockNum()!=1)
								{
									enemy[i]->SetGroundFlg(false);
								}

							}
							
						}
					}
				}
				*/	
			}

			/*
			//ダイナマイトと岩ブロックの当たり判定
			for (int j = 0; j < block_count; j++)
			{
				if (stage_block[j] != nullptr)
				{
					if (stage_block[j]->GetBlockNum() == 4)
					{
						//ダメージを一回だけ与える
						if (rock_damage_once == false)
						{
							for (int i = 0; i < DYNAMITE_MAXNUM; i++)
							{
								if (dynamite[i] != nullptr)
								{
									//ダイナマイトが岩と当たってるかのチェック
									if (dynamite[i]->GetDynamite() == false&&stage_block[j]!=nullptr)
									{
										if (dynamite[i]->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()) == true)
										{
											dynamite[i]->SetDynamite(true);

										}
									}
									//ダイナマイトの爆発とエネミーの当たり判定
									if (dynamite[i]->Getdamage_flg() == true)
									{
										if (dynamite[i]->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()) == true)
										{
											dynamite[i]->SetEnemyX(stage_block[j]->GetWorldLocation().x);
											dynamite[i]->DamageCalculation();
											stage_block[j]->SetDamage(30);
											stage_block[j]->SetShakeFlg(true);

											rock_damage_once = true;
										}
									}
								}

								if (stage_block[j] != nullptr)
								{
									if (stage_block[j]->GetHp() <= 0)
									{
										stage_block[j] = nullptr;
									}
								}

							}
						}
					}
				}
			}
			*/
			//ダメージを一回だけ与える

		for (int i = 0; i < DYNAMITE_MAXNUM; i++)
		{
			if (dynamite[i] != nullptr)
			{
				for (int j = 0; j < block_count; j++)
				{

					if (stage_block[j] != nullptr)
					{
						if (stage_block[j]->GetBlockNum() == 4)
						{
								//ダイナマイトが岩と当たってるかのチェック
								if (dynamite[i]->GetDynamite() == false && stage_block[j] != nullptr)
								{
									if (dynamite[i]->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()) == true)
									{
										dynamite[i]->SetDynamite(true);

									}
								}
								//ダイナマイトの爆発とエネミーの当たり判定
								if (dynamite[i]->Getdamage_flg() == true)
								{
									if (dynamite[i]->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()) == true)
									{
										dynamite[i]->SetEnemyX(stage_block[j]->GetWorldLocation().x);
										dynamite[i]->DamageCalculation();
										stage_block[j]->SetDamage(30);
										stage_block[j]->SetShakeFlg(true);

										//rock_damage_once = true;
									}
								}


							
						}
					}

				}

			}
		}
			
		for (int j = 0; j < block_count; j++)
		{
			if (stage_block[j] != nullptr)
			{
				if (stage_block[j]->GetBlockNum()==4 && stage_block[j]->GetHp() <= 0)
				{
					stage_block[j] = nullptr;
				}
			}

		}

			//エネミーと岩ブロックの当たり判定
			for (int j = 0; j < block_count; j++)
			{
				if (stage_block[j] != nullptr&& stage_block[j]->GetBlockNum() == 4)
				{
					stage_block[j]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

	
						for (int i = 0; i < ENEMYMAXNUM; i++)
						{
							if (enemy[i] != nullptr && enemy[i]->GetHp() > 0)
							{
								if (enemy[i]->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()) == true)
								{
									if (enemy[i]->GetIsKnockBack() == true)
									{
										// ノックバックしている敵に当たったら自身もノックバックを開始する
										enemy[i]->SetKnockBackStartFlg(true);
									}
									else
									{
										// 当たっていたら２体とも進行方向を反対に変更する
										enemy[i]->SetHitEnemyX(stage_block[j]->GetWorldLocation().x);
										enemy[i]->ChangeDirection();
									}
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

			if (score != nullptr)
			{
				score->Update();
			}

			if (player != nullptr)
			{
				//プレイヤーの死亡処理
				if (player->GetDeathFlg() == true)
				{
					delete player;
					player_damage_once = false;
					player = nullptr;
					gameover_flg = true;
					player = new Player(2000.0f);
					//player->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
				}
			}
			break;
	default:
		break;

		

	}

}

void GameMainScene::Draw() const
{
	// 背景画像描画（仮）
	for (int i = 0; i < 8; i++)
	{
		DrawGraph(location_x+1280*i, location_y, back_img, FALSE);
	}

	//DrawFormatString(0, 0, 0xffffff, "screen_origin_position.x: %f", screen_origin_position.x);
	//fp.display_fps();

	//if (checkhit == true)
	//{
	//	DrawFormatString(0, 10, 0xffffff, "hit");
	//}
	for (int j = 0; j < block_count; j++)
	{
		if (stage_block[j] != nullptr)
		{
			stage_block[j]->DrawKanban();
		}

	}
	
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

		//ダイナマイト描画
		for (int i = 0; i < DYNAMITE_MAXNUM; i++)
		{
			if (dynamite[i] != nullptr)
			{
				dynamite[i]->Draw();
				//DrawFormatString(300 * i, 0, 0xff0000, "tmp_abs: %f", dynamite[i]->GetTmpAbs());
			}
		}




		if (ui != nullptr)
		{
			if (player != nullptr)
			{
				ui->DrawTutorial(player);
			}
		}


	}
	else
	{

		//プレイヤー描画
		if (player != nullptr)
		{
			player->Draw();
		}

	//プレイヤー攻撃描画
	if (ac != nullptr)
	{
		if (ac->GetAttackFlg() == true)
		{
			ac->Draw();
		}
	}


	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		// 歩行エネミーの宝石描画処理
		if (walk_gem[i] != nullptr)
		{
			if (walk_gem[i]->GetPlaySoundFlg() == true)
			{
				walk_gem[i]->Draw();
			}
		}
	}
	


	if (roll_gem != nullptr)
	{
		if (roll_gem->GetPlaySoundFlg() == true)
		{
			// 転がるエネミーの宝石描画処理
			roll_gem->Draw();
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

	for (int i = 0; i < ROLLING_ENEMY_MAXNUM; i++)
	{
		if (rolling_enemy[i] != nullptr)
		{
			// 転がるエネミー描画
			rolling_enemy[i]->Draw();
		}
	}

	//ステージブロック描画
	for (int j = 0; j < block_count; j++)
	{
		if (stage_block[j] != nullptr)
		{
			stage_block[j]->Draw();
		}

	}

	//ダイナマイト描画
	for (int i = 0; i < DYNAMITE_MAXNUM; i++)
	{
		if (dynamite[i] != nullptr)
		{
			dynamite[i]->Draw();
			//DrawFormatString(300 * i , 0, 0xff0000, "tmp_abs: %f", dynamite[i]->GetTmpAbs());
		}
	}

	if (ui != nullptr)
	{
		ui->Draw();
	}

	if (score != nullptr)
	{
		score->Draw();
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
	//DrawFormatString(30, 300, 0xffffff, "e_cnt: %d", enemy_count);


	switch (game_state)
	{
	case EDITOR:
		DrawFormatString(400, 100, 0xffffff, "EDITOR_NOW");
		mapio->Draw();

		break;
	case TUTORIAL:
		//DrawFormatString(400, 100, 0xffffff, "TUTORIAL_NOW");
		break;
	case POSE:
		DrawFormatString(400, 100, 0xffffff, "POSE_NOW");
		break;
		
	case GOAL:
		DrawFormatString(400, 100, 0xffffff, "GOAL!!");
		break;
	case PLAY:
		//DrawFormatString(400, 100, 0xffffff, "PLAY_NOW");
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

void GameMainScene::Tutorial()
{
	//ワールド座標ースクリーン座標の原点してオブジェクトのスクリーン座標を出す計算
	location_x = world_x - screen_origin_position.x;
	location_y = world_y - screen_origin_position.y;

	//プレイヤー
	if (player != nullptr)
	{
			player->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

			player->TutorialAnimUpdate();

			if (player->GetStartFlg() == true)
			{
				game_state = PLAY;
			}
		
		if (ui != nullptr)
		{
			ui->UpdateTutorial(player);
		}
	}

	for (int j = 0; j < block_count; j++)
	{
		if (stage_block[j] != nullptr)
		{
			stage_block[j]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

			if (player != nullptr)
			{


				if (stage_block[j]->GetBlockNum() == 6)
				{
					
					if (player->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()) == true)
					{
						player->SetMoveStop(true);
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

				for (int i = 0; i < DYNAMITE_MAXNUM; i++)
				{
					if (dynamite[i] != nullptr)
					{
						//ダイナマイトが岩と当たってるかのチェック
						if (dynamite[i]->GetDynamite() == false)
						{
							if (dynamite[i]->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()) == true)
							{
								dynamite[i]->SetDynamite(true);

							}
						}

						//ダイナマイトの爆発とエネミーの当たり判定
						if (dynamite[i]->Getdamage_flg() == true&& stage_block[j]->GetHp() > 0)
						{
							if (dynamite[i]->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()) == true)
							{
								dynamite[i]->SetEnemyX(stage_block[j]->GetWorldLocation().x);
								dynamite[i]->DamageCalculation();
								stage_block[j]->SetDamage(30);
								stage_block[j]->SetShakeFlg(true);
								rock_damage_once = true;

							}
						}
					}
				}
			}


		}

		//わけないと４番目壊した時GetBlockNumでエラーが起きるため
		if (stage_block[j] != nullptr)
		{
			stage_block[j]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
			if (stage_block[j]->GetBlockNum() == 5)
			{
				//プレイヤが右向きだったら
				if (player->GetDirection() == 0)
				{
					if (player->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()) == true)
					{
						player->SetMoveStop(true);
						stage_block[j] = nullptr;
					}
				}
			}

		}

		if (stage_block[j] != nullptr)
		{
			stage_block[j]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

			if (player != nullptr)
			{
				stage_block[j]->Update();


				if (stage_block[j]->GetBlockNum() == 7)
				{

					if (player->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()) == true)
					{
						stage_block[j]->SetUp(true);

					}

				}
			}
		}
	}

	//プレイヤーの攻撃
	if (ac != nullptr) {
		ac->Update(this, player);
	}

	//ダイナマイト
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

	//カメラとUIのアップデート
	
	if (player != nullptr) {
		if (player->GetTutoAnimDynaFlg() == true)
		{
			camera_resetflg = true;
			if (dynamite[0] != nullptr)
			{
				UpdateCamera(dynamite[0]->GetWorldLocation());
				camera_resetx = dynamite[0]->GetWorldLocation();
			}

		}

		//元のプレイヤーの位置までカメラを戻す
		if (camera_resetflg == true&& player->GetTutoAnimDynaFlg() == false)
		{
			camera_resetx.x += -10;
			UpdateCamera(camera_resetx);
			if (camera_old_x > camera_resetx.x)
			{
				camera_resetflg = false;
				//とりあえず仮
				//game_state = PLAY;
			}
		}
		
		if(camera_resetflg==false && player->GetTutoAnimDynaFlg() == false) {
			UpdateCamera(player->GetWorldLocation());
			camera_old_x = player->GetWorldLocation().x;
		}
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

}


AbstractScene* GameMainScene::Change()
{
	if (gameover_flg == true)
	{
		// ゲームメインbgm停止
		if (CheckSoundMem(main_bgm) == TRUE)
		{
			StopSoundMem(main_bgm);
		}

		// プレイヤーの残機が0になったら
		return new GameOverScene(score->GetScore());
	}

	if (clear_flg == true)
	{
		// ゲームメインbgm停止
		if (CheckSoundMem(main_bgm) == TRUE)
		{
			StopSoundMem(main_bgm);
		}

		// ゴールに触れたら
		return new GameClearScene(score->GetScore());
	}

	return this;
}