#include "GameMainScene.h"


//画面の中央を座標に入れる
static cameraposition camera_pos{ SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f };

static cameraposition screen_origin_position =
{
	camera_pos.x - SCREEN_WIDTH / 2.0f,
	camera_pos.y - SCREEN_HEIGHT / 2.0f
};


GameMainScene::GameMainScene(bool set_flg)
{
	// 読み込みたいステージ
	stage_num = stage2;

	retry_flg = set_flg;
	checkhit = false;
	block_cnt = 0;
	check_cnt = 0;
	//check_abs = 0;

	respawn_x = 100.0f;
	respawn_y = 0.0f;

	mapio = new MapIo;
	fade = new BlackOut;

	fragile_wall = new FragileWall * [FRAGILE_WALL_MAXNUM];
	cage_door = new CageDoor * [CAGE_DOOR_MAXNUM];
	cage = new Cage * [CAGE_DOOR_MAXNUM];
	magma = new Magma * [MAGMA_MAXMUN];
	falling_floor = new FallingFloor * [FALLING_FLOOR_MAXNUM];
	geyser = new Geyser * [GEYSER_MAXNUM];
	lift = new Lift * [LIFT_MAXNUM];
	rock = new Rock * [ROCK_MAXNUM];

	//オブジェクトにNullを代入
	SetObjectNull();
	

	//プレイヤー生成
	if (retry_flg == false)
	{
		player = new Player(0.0f);
		p_notback_flg = false;
	}
	else
	{
		if (stage_num == stage1) {
			player = new Player(2200.0f);
			p_notback_flg = true;
		}
		else {
			//プレイヤーのリスタート位置を入れる
			player = new Player(2200.0f);
			p_notback_flg = false;
		}
	}

	enemy = new Enemy * [ENEMYMAXNUM];
	rolling_enemy = new RollingEnemy * [ROLLING_ENEMY_MAXNUM];
	stage_block = new StageBlock * [map_blockmax_y * map_blockmax_x];

	ui = new UI((int)player->GetHp(), player->GetDynaNum());
	ac = new AttackCheck;

	walk_gem = new Gem * [ENEMYMAXNUM];
	roll_gem = new Gem * [ROLLING_ENEMY_MAXNUM];
	score = new Score;



	dynamite = new Dynamite * [DYNAMITE_MAXNUM];
	enemy_damage_once = false;
	rock_damage_once = false;
	player_damage_once = false;
	////back.png
	//back_img[0] = LoadGraph("images/Backimg/backimg0.png", TRUE);
	//back_img[1] = LoadGraph("images/Backimg/backimg01.png", TRUE);
	back_img[0] = LoadGraph("images/Backimg/backimg.png", TRUE);
	back_img[1] = LoadGraph("images/Backimg/backimg.png", TRUE);
	//back_img[9] = LoadGraph("images/Backimg/backimgGoal.png", TRUE);
	back_img[9] = LoadGraph("images/Backimg/backimgGoal01.png", TRUE);
	goal_img = LoadGraph("images/Ending/ending8.png", TRUE);
	death_img = LoadGraph("images/Backimg/death.png", TRUE);
	pose_img = LoadGraph("images/UI/pose.png", TRUE);
	//back_img = LoadGraph("images/background_test.png", TRUE);



	//game_state = RESPAWN;

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
	//rock_count = 0;
	rolling_enemy_cnt = 0;



	mapio->LoadMapData(stage_num);
	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		enemy[i] = nullptr;
		walk_gem[i] = nullptr;
	}

	//ローリングエネミーとジェム
	for (int i = 0; i < ROLLING_ENEMY_MAXNUM; i++)
	{
		rolling_enemy[i] = nullptr;
		roll_gem[i] = nullptr;
	}


	if (retry_flg == false)
	{
		//リトライじゃなかったら
		game_state = TUTORIAL;

		if (mapio != nullptr)
		{
			//stage_block = new StageBlock(this->mapio);

			for (int i = 0; i < map_blockmax_y; i++)
			{
				for (int j = 0; j < map_blockmax_x; j++)
				{
					map_old_array[i][j] = mapio->GetMapData(i, j);

					switch (mapio->GetMapData(i, j))
					{
					case 1:
						stage_block[block_count++] = new StageBlock(1, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 2:
						enemy[enemy_count++] = new Enemy((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2, false);
						break;
					case 3:
						stage_block[block_count++] = new StageBlock(3, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 4:
						rock[object_num.rock_cnt++] = new Rock((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						//stage_block[block_count++] = new StageBlock(4, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 5:
						stage_block[block_count++] = new StageBlock(5, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 6:
						stage_block[block_count++] = new StageBlock(6, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 7:
						stage_block[block_count++] = new StageBlock(7, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 8:
						enemy[enemy_count++] = new Enemy((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2, true);
						break;
					case 9:
						rolling_enemy[rolling_enemy_cnt++] = new RollingEnemy((float)j * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 10:
						stage_block[block_count++] = new StageBlock(10, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 11:
						stage_block[block_count++] = new StageBlock(11, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 12:
						fragile_wall[object_num.fragile_wall_cnt++] = new FragileWall((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 13:
						magma[object_num.magma_cnt++] = new Magma((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 14:
						falling_floor[object_num.falling_floor_cnt++] = new FallingFloor((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 15:
						geyser[object_num.geyser_cnt++] = new Geyser((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 16:
						cage_door[object_num.cage_door_cnt] = new CageDoor((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						cage[object_num.cage_cnt++] = new Cage(cage_door[object_num.cage_door_cnt++]->GetWorldLocation());
						break;
					case 17:
						lift[object_num.lift_cnt++] = new Lift((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 18:
						stage_block[block_count++] = new StageBlock(18, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					case 19:
						stage_block[block_count++] = new StageBlock(19, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
						break;
					}
				}
			}
		}
	}
	else
	{
		//リトライして来たら
		game_state = PLAY;
		
		ResetMap();
	}
	//game_state = PLAY;

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


	shake_cnt = 0;
	shake_x1 = 0;
	shake_x2 = 0;
	shake_flg = false;

	play_start_flg = false;

	clear_alpha = 0;
	clear_flg = false;
	gameover_flg = false;

	// サウンド読込
	main_bgm = LoadSoundMem("sounds/bgm/gamemain.mp3");
	volume = 150;
	fadein_sound = LoadSoundMem("sounds/se/player/drop3.mp3");

	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, main_bgm);
	ChangeVolumeSoundMem(volume, fadein_sound);
	camera_resetx.x = 0;
	camera_resetflg = false;
	camera_old_x = 0;

	img_extrate = 5;

	//円形フェードイン用の描画対象にできる画像を作成
	ScreenHandle = MakeScreen(1280, 720, TRUE);
	//円形フェードインの円のサイズをセット
	CircleSize = 700;
	fadein_flg = false;
	alpha = 255;
	black_flg = false;

	p_life_num = 2;
	gameover_anim_cnt = 0;
	fadein_snd_flg = true;

	start_pause_se = LoadSoundMem("sounds/se/pause/pause.mp3");
	unpause_se = LoadSoundMem("sounds/se/pause/unpause.mp3");
	ChangeVolumeSoundMem(140, start_pause_se);
	ChangeVolumeSoundMem(210, unpause_se);

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
	delete fragile_wall;
	delete cage;
	delete cage_door;
	delete magma;
	delete falling_floor;

	// 画像削除
	DeleteGraph(back_img[0]);
	DeleteGraph(back_img[9]);

	// サウンド削除
	DeleteSoundMem(main_bgm);
	DeleteSoundMem(fadein_sound);
	DeleteSoundMem(start_pause_se);
	DeleteSoundMem(unpause_se);
}

void GameMainScene::ResetMap()
{

	mapio->LoadMapData(stage_num);

	SetObjectNull();

	score = nullptr;
	for (int j = 0; j < block_count; j++)
	{
		if (stage_block[j] != nullptr)
		{
			stage_block[j] = nullptr;
		}
	}

	//エネミー削除
	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		enemy[i] = nullptr;
		walk_gem[i] = nullptr;
	}

	for (int i = 0; i < ROLLING_ENEMY_MAXNUM; i++)
	{
		rolling_enemy[i] = nullptr;
		roll_gem[i] = nullptr;
	}

	for (int i = 0; i < DYNAMITE_MAXNUM; i++)
	{
		dynamite[i] = nullptr;
	}

	//オブジェクトにnullを代入
	for (int i = 0; i < FRAGILE_WALL_MAXNUM; i++)
	{
		fragile_wall[i] = nullptr;
	}
	for (int i = 0; i < CAGE_DOOR_MAXNUM; i++)
	{
		cage_door[i] = nullptr;
		cage[i] = nullptr;
	}
	for (int i = 0; i < MAGMA_MAXMUN; i++)
	{
		magma[i] = nullptr;
	}
	for (int i = 0; i < FALLING_FLOOR_MAXNUM; i++)
	{
		falling_floor[i] = nullptr;
	}
	for (int i = 0; i < GEYSER_MAXNUM; i++)
	{
		geyser[i] = nullptr;
	}
	for (int i = 0; i < LIFT_MAXNUM; i++)
	{
		lift[i] = nullptr;
	}

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
				stage_block[block_count++] = new StageBlock(1, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
				break;
			case 3:
				stage_block[block_count++] = new StageBlock(3, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
				break;
			case 4:
				rock[object_num.rock_cnt++] = new Rock((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
				//stage_block[block_count++] = new StageBlock(4, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
				break;
			case 6:
				stage_block[block_count++] = new StageBlock(6, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
				break;
			case 10:
				stage_block[block_count++] = new StageBlock(10, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
				break;
			case 11:
				stage_block[block_count++] = new StageBlock(11, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
				break;
			case 12:
				fragile_wall[0] = new FragileWall((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
				break;
			case 13:
				magma[0] = new Magma((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
				break;
			case 14:
				falling_floor[0] = new FallingFloor((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
				break;
			case 15:
				geyser[0] = new Geyser((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
				break;
			case 16:
				cage_door[0] = new CageDoor((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
				cage[0] = new Cage(cage_door[0]->GetWorldLocation());
				break;
			case 17:
				lift[object_num.lift_cnt++] = new Lift((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
				break;
			case 18:
				stage_block[block_count++] = new StageBlock(18, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
				break;
			case 19:
				stage_block[block_count++] = new StageBlock(19, (float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2);
				break;
			}

			if (enemy_count < ENEMYMAXNUM)
			{
				if (mapio->GetMapData(i, j) == 2)
				{
					enemy[enemy_count] = new Enemy((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2, false);
					enemy[enemy_count++]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
				}

				if (mapio->GetMapData(i, j) == 8)
				{
					enemy[enemy_count] = new Enemy((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2, true);
					enemy[enemy_count++]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
				}
			}

			if (rolling_enemy_cnt < ROLLING_ENEMY_MAXNUM)
			{
				if (mapio->GetMapData(i, j) == 9)
				{
					rolling_enemy[rolling_enemy_cnt] = new RollingEnemy((float)j * BLOCKSIZE + BLOCKSIZE / 2);
					rolling_enemy[rolling_enemy_cnt++]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
				}
			}
		}
	}

	for (int j = 0; j < block_count; j++)
	{
		if (stage_block[j] != nullptr)
		{
			stage_block[j]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
		}
	}
	score = new Score;
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

	if (p_life_num < 0)
	{
		StopSoundMem(main_bgm);
	}
	else
	{
		// ゲームメインbgmループ再生
		if (CheckSoundMem(main_bgm) == FALSE)
		{
			PlaySoundMem(main_bgm, DX_PLAYTYPE_LOOP);
		}
	}

	switch (game_state)
	{
	case EDITOR:

		mapio->InputTest(this);
		mapio->SetOriginPosx(screen_origin_position.x);

		//ワールド座標ースクリーン座標の原点してオブジェクトのスクリーン座標を出す計算
		location_x = world_x - screen_origin_position.x;
		location_y = world_y - screen_origin_position.y;

		if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE)
		{
			screen_origin_position.x += 5;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) == TRUE)
		{
			screen_origin_position.x -= 5;
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


		//右スティック押し込み
		if (input.CheckBtn(XINPUT_BUTTON_RIGHT_THUMB) == TRUE || CheckHitKey(KEY_INPUT_P) == TRUE)
		{
			//Inputを保存
			mapio->SaveMapData(stage_num);
			block_count = 0;
			enemy_count = 0;
			//rock_count = 0;
			rolling_enemy_cnt = 0;

			//マップチップに反映する
			ResetMap();
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
			// ポーズ解除se
			PlaySoundMem(unpause_se, DX_PLAYTYPE_BACK);

			game_state = PLAY;
		}
		break;


	case GOAL:

		if (stage_num == stage1) {
			stage_num = stage2;
			p_notback_flg = false;
			ResetMap();
			clear_alpha = 0;
			game_state = PLAY;
		}
		else {
			if (clear_alpha++ > 300)
			{
				clear_flg = true;
			}
		}

		break;


	case RESPAWN:
		//ワールド座標ースクリーン座標の原点してオブジェクトのスクリーン座標を出す計算
		location_x = world_x - screen_origin_position.x;
		location_y = world_y - screen_origin_position.y;

		if (p_life_num < 0)
		{
			if (fadein_snd_flg == true)
			{
				fadein_snd_flg = false;
				PlaySoundMem(fadein_sound, DX_PLAYTYPE_BACK);
			}

			if (CircleSize <= 64 && black_flg == false)
			{
				//gameover_flg = true;
				if (gameover_anim_cnt++ > 30)
				{
					CircleSize -= 8;
					if (CircleSize <= -6)
					{
						gameover_flg = true;
					}
				}
			}
			else
			{
				CircleSize -= 8;
			}
		}
		else
		{
			if (fadein_snd_flg == true)
			{
				fadein_snd_flg = false;
				PlaySoundMem(fadein_sound, DX_PLAYTYPE_BACK);
			}

			if (CircleSize <= -6 && black_flg == false)
			{
				fadein_flg = false;
				CircleSize = 700;
				delete player;
				player_damage_once = false;
				player = nullptr;

				//gameover_flg = true;
				black_flg = true;
				player = new Player(respawn_x);

				UpdateCamera(player->GetWorldLocation());
				player->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

				//残機数を渡す
				if (ui != nullptr)
				{
					ui->SetLifeNum(p_life_num);
				}
				ResetMap();
			}
			else
			{
				CircleSize -= 8;
			}

			if (black_flg == true)
			{
				if (player != nullptr)
				{
					player->RespawnAnimUpdate();
				}
				alpha -= 5;

				if (player->GetStartFlg() == true)
				{
					volume = 150;
					ChangeVolumeSoundMem(volume, main_bgm);
					game_state = PLAY;
					fadein_snd_flg = true;
					black_flg = false;
					alpha = 255;
					CircleSize = 700;
				}
			}
		}
		break;


	case PLAY:

		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			game_state = EDITOR;
		}

		if (CheckHitKey(KEY_INPUT_N) == TRUE) {
			game_state = GOAL;
		}

		if (retry_flg == true && fade != nullptr)
		{
			if (fade->GetFadein() == false)
			{
				fade->Fadein();
			}
			else
			{
				fade = nullptr;
			}
		}

		//ワールド座標ースクリーン座標の原点してオブジェクトのスクリーン座標を出す計算
		location_x = world_x - screen_origin_position.x;
		location_y = world_y - screen_origin_position.y;

		//リフトアップデート
		LiftUpDate();
		LiftHitStop();
		PlayerHitLift();

		//押されたらポーズへ
		if (input.CheckBtn(XINPUT_BUTTON_START) == TRUE)
		{
			// ポーズ開始se
			PlaySoundMem(start_pause_se, DX_PLAYTYPE_BACK);
			game_state = POSE;
		}
		

		//エネミー更新
		EnemyUpDate();

		//ダイナマイトと敵の当たり判定
		DynamiteHitEnemy();

		//宝石生成処理
		GemGenerate();

		//宝石更新処理
		GemUpDate();

		//プレイヤーと宝石の当たり判定
		PlayerHitGem();

		//つるはしと敵の当たり判定
		PickaxeHitEnemy();

		//エネミー同士の当たり判定
		EnemyHitEnemy();

		//プレイヤーがエネミーに当たったときの被弾処理
		PlayerHitEnemy();

		//プレイヤー更新処理
		PlayerUpDate();

		//リスポーン位置更新
		PlayerHitRespawn();

		if (stage_num == stage2)
		{
			// 脆い壁更新処理
			FragileWallUpdate();

			// 檻の更新処理
			CageUpdate();

			// 檻のドアの更新処理
			CageDoorUpdate();

			// マグマの更新処理
			MagmaUpdete();

			// 落ちる床の更新処理
			FallingFloorUpdate();

			// 間欠泉の更新処理
			GeyserUpdete();

			// ダイナマイトと脆い壁の当たり判定処理
			DynamiteHitFragileWall();

			// プレイヤーと脆い壁の当たり判定処理
			PlayerHitFragileWall();

			// プレイヤーと壊れる岩の当たり判定処理
			PlayerHitRock();

			// プレイヤーと檻のドアの当たり判定処理
			PlayerHitCageDoor();

			// プレイヤーが檻の中にいるのか調べる
			CheckPlayerInCage();

			// 檻のドアへの攻撃判定
			AttackCageDoor();

			// プレイヤーとマグマの当たり判定処理
			PlayerHitMagma();

			// プレイヤーと落ちる床の当たり判定
			PlayerHitFallingFloor();

			// つるはしと落ちる床の当たり判定
			PickaxeHitFallingFloor();

			// 落ちる床とマグマの当たり判定
			FallingFloorHitMagma();

			// プレイヤーと間欠泉の当たり判定
			PlayerHitGeyser();

			// つるはしと間欠泉の当たり判定
			PickaxeHitGeyser();
		}

		//カメラとUIのアップデート
		if (player != nullptr)
		{
			UpdateCamera(player->GetWorldLocation());

			//UIアップデート
			if (ui != nullptr)
			{
				ui->SetLifeNum(p_life_num);
				ui->Update((int)player->GetHp(), player->GetDynaNum());
				if (player->GetHp() <= 0)
				{
					ui->Update(0, 0);
				}
			}
		}



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

					/*
					if (stage_block[j]->GetBlockNum() == 4)
					{

						stage_block[j]->Update();

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
					*/
				}
			}
		}


		//岩アップデート
		RockUpdate();
		EnemyHitRock();
		DynamiteHitRock();
		PickaxeHitRock();


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
				fadein_flg = true;
				p_life_num--;
				p_notback_flg = true;
				volume = 50;
				ChangeVolumeSoundMem(volume, main_bgm);
				game_state = RESPAWN;
			}
		}

		PlayerHitBlock();

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
		DrawGraph((int)location_x + 1280 * i, (int)location_y, back_img[1], FALSE);
	}

	DrawGraph((int)location_x + 1280 * 8, (int)location_y, back_img[9], FALSE);
	DrawGraph((int)location_x + 1280, (int)location_y, back_img[0], FALSE);

	for (int j = 0; j < block_count; j++)
	{
		if (stage_block[j] != nullptr)
		{
			stage_block[j]->DrawKanban();
		}
	}

	//リフト描画
	for (int i = 0; i < LIFT_MAXNUM; i++)
	{
		if (lift[i] != nullptr)
		{
			lift[i]->Draw();
		}
	}

	//岩描画
	for (int i = 0; i < object_num.rock_cnt; i++)
	{
		if (rock[i] != nullptr)
		{
			rock[i]->Draw();
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
			//if (ac->GetAttackFlg() == true)
			//{
			ac->Draw();
			//}
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
			//player->Draw();
			if (checkhit == true)
			{
				DrawFormatString(player->GetLocation().x, player->GetLocation().y - 80, 0xffffff, "true");
			}
			DrawFormatString(player->GetLocation().x, player->GetLocation().y - 100, 0xffffff, "bcnt:%d", block_cnt);
			DrawFormatString(player->GetLocation().x, player->GetLocation().y - 120, 0xffffff, "0:%d,1:%d,2:%d", checkhit_block[0], checkhit_block[1], checkhit_block[2]);
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
				walk_gem[i]->Draw();
			}
		}

		for (int i = 0; i < ROLLING_ENEMY_MAXNUM; i++)
		{
			if (roll_gem[i] != nullptr)
			{
				// 転がるエネミーの宝石描画処理
				roll_gem[i]->Draw();
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

		if (stage_num == stage2)
		{
			// 脆い壁描画
			for (int i = 0; i < FRAGILE_WALL_MAXNUM; i++)
			{
				if (fragile_wall[i] != nullptr)
				{
					fragile_wall[i]->Draw();
				}			
			}

			for (int i = 0; i < CAGE_DOOR_MAXNUM; i++)
			{			
				// 檻の描画
				if (cage[i] != nullptr)
				{
					cage[i]->Draw();
				}

				// 檻のドアの描画
				if (cage_door[i] != nullptr)
				{
					cage_door[i]->Draw();
				}
			}

			// 落ちる床の描画
			for (int i = 0; i < FALLING_FLOOR_MAXNUM; i++)
			{
				if (falling_floor[i] != nullptr)
				{
					falling_floor[i]->Draw();
				}

			}

			// マグマの描画
			for (int i = 0; i < MAGMA_MAXMUN; i++)
			{
				if (magma[i] != nullptr)
				{
					magma[i]->Draw();
				}
			}

			// 間欠泉の描画
			for (int i = 0; i < GEYSER_MAXNUM; i++)
			{
				if (geyser[i] != nullptr)
				{
					geyser[i]->Draw();
				}
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

	if (p_life_num < 0)
	{
		//プレイヤー描画
		if (player != nullptr)
		{
			player->Draw();
		}
	}

	if (fadein_flg == true)
	{
		//DrawGraph(location_x, location_y, death_img, FALSE);
		if (player != nullptr)
		{
			//DrawRotaGraph(player->GetLocation().x, 700, img_extrate, 0, death_img, TRUE, 0);

			SetDrawScreen(ScreenHandle);
			DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
			if (CircleSize >= 1)
			{
				SetDrawBlendMode(DX_BLENDMODE_SRCCOLOR, 0);
				DrawCircle((int)player->GetLocation().x, (int)player->GetLocation().y + 40, CircleSize, GetColor(0, 0, 0), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			}
		}

		SetDrawScreen(DX_SCREEN_BACK);
		DrawGraph(0, 0, ScreenHandle, TRUE);
	}

	if (black_flg == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha);
		DrawGraph(0, 0, death_img, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (game_state == GOAL)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)clear_alpha);
		DrawGraph(0, 0, goal_img, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (game_state == POSE)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawGraph(0, 0, death_img, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawGraph(550, 350, pose_img, FALSE);
	}

	if (retry_flg == true && fade != nullptr)
	{
		if (fade->GetFadein() == false)
		{
			fade->Draw_Fadein();
		}
	}

	//プレイヤー描画
	if (player != nullptr)
	{
		player->Draw();
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
	//DrawFormatString(30, 300, 0xffffff, "p_life_num:%d",p_life_num );


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
		//DrawFormatString(400, 100, 0xffffff, "POSE_NOW");
		break;
	case GOAL:
		//DrawFormatString(400, 100, 0xffffff, "GOAL!!");
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

	screen_origin_position = { camera_pos.x - SCREEN_WIDTH / 2.0f,camera_pos.y - SCREEN_HEIGHT / 2.0f };


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
					//if (player->GetDirection() == 0)
					//{
					// プレイヤーと岩が当たっていたら
					//if (player->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()) == true)
					//{
					//	// プレイヤーの歩行を止める
					//	player->HitCheckB(stage_block[j]->GetVertex());
					//}
					//}

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

					if (stage_block[j]->GetHp() <= 0 && stage_block[j]->GetDeleteFlg() == true)
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
						if (dynamite[i]->Getdamage_flg() == true && stage_block[j]->GetHp() > 0)
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

					if (stage_block[j]->GetDeleteFlg() == true)
					{
						stage_block[j] = nullptr;
					}
				}
			}
		}
	}

	// プレイヤーと壊れる岩の当たり判定処理
	PlayerHitRock();

	//プレイヤーの攻撃
	if (ac != nullptr) {
		ac->Update(this, player);
		//ac->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

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
		if (camera_resetflg == true && player->GetTutoAnimDynaFlg() == false)
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

		if (camera_resetflg == false && player->GetTutoAnimDynaFlg() == false) {
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




}

void GameMainScene::EnemyDamage(int enemynum, float damage)
{
	enemy[enemynum]->Damage(damage);
	// 歩行エネミーのノックバック処理
	enemy[enemynum]->SetKnockBackStartFlg(true);
	enemy[enemynum]->SetStarDrawFlg(true);
	enemy[enemynum]->SetPlayerWorldLocation(player->GetWorldLocation());


}

void GameMainScene::PlayerDamage()
{
	if (player_damage_once == false) {
		player_damage_once = true;
		player->SetDamageFlg(player_damage_once);
		player->SetDamage(10);


		//HPeffect
		if (ui != nullptr)
		{
			ui->SetBreakHpFlg(true);
		}
	}
}

void GameMainScene::GemGenerate()
{

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


	// 転がるエネミーの宝石生成処理
	for (int i = 0; i < ROLLING_ENEMY_MAXNUM; i++)
	{
		if (rolling_enemy[i] != nullptr)
		{
			if (rolling_enemy[i]->GetGemDropFlg() == true)
			{
				if (player != nullptr && roll_gem[i] == nullptr)
				{
					roll_gem[i] = new Gem(rolling_enemy[i]->GetWorldLocation(), roll_gem_score);
					roll_gem[i]->SetFromRollingEnemyFlg(true);
					roll_gem[i]->SetPlayerWorldLocation(player->GetWorldLocation());
				}
			}
		}
	}



}

void GameMainScene::GemUpDate()
{
	// 歩行エネミーの宝石更新処理
	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		if (walk_gem[i] != nullptr)
		{
			walk_gem[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
			walk_gem[i]->Update(this);
		}
	}

	// 転がるエネミーの宝石更新処理
	for (int i = 0; i < ROLLING_ENEMY_MAXNUM; i++)
	{
		if (roll_gem[i] != nullptr)
		{
			roll_gem[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
			roll_gem[i]->Update(this);
		}
	}
}

void GameMainScene::EnemyHitEnemy()
{

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
					}
				}
			}
		}
	}

}

void GameMainScene::EnemyUpDate()
{

	// エネミー更新処理
	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
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

			if (rolling_enemy[i]->GetWorldLocation().x > screen_origin_position.x - 100 && rolling_enemy[i]->GetWorldLocation().x < screen_origin_position.x + SCREEN_WIDTH + 30)
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
				if (rolling_enemy[i]->GetWorldLocation().x < camera_pos.x - SCREEN_WIDTH / 2 - 100)
				{
					delete rolling_enemy[i];
					rolling_enemy[i] = nullptr;
				}
			}
		}
	}
}

void GameMainScene::PlayerUpDate()
{

	//プレイヤー
	if (player != nullptr)
	{
		player->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
		player->Update(this);
	}

	//プレイヤーの攻撃
	if (player != nullptr && ac != nullptr)
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
		if (player != nullptr && player->GetAtkDynamite() == true)
		{
			if (dynamite[i] == nullptr)
			{
				dynamite[i] = new Dynamite(player->GetWorldLocation(), player->GetDirection());
				player->SetAtkDynamite(false);
			}
		}
	}

}

void GameMainScene::PlayerHitGem()
{

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


	// 転がるエネミーの宝石とプレイヤーの当たり判定
	for (int i = 0; i < ROLLING_ENEMY_MAXNUM; i++)
	{
		if (player != nullptr && roll_gem[i] != nullptr)
		{
			if (roll_gem[i]->GetPlaySoundFlg() == true)
			{
				if (player->HitCheck(roll_gem[i]->GetWorldLocation(), roll_gem[i]->GetWidth(), roll_gem[i]->GetHeight()) == true)
				{
					roll_gem[i]->PlayGetSound();
					score->SetScore(roll_gem[i]->GetGemScore());
				}
			}

			if (roll_gem[i]->GetDeleteFlg() == true)
			{
				delete roll_gem[i];
				roll_gem[i] = nullptr;
			}
		}
	}

}

void GameMainScene::PlayerHitEnemy()
{
	//プレイヤーと歩行の敵との当たり判定
	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		if (player != nullptr && enemy[i] != nullptr) {
			//もしプレイヤーとエネミーが当たったら
			if (player->HitCheck(enemy[i]->GetWorldLocation(), enemy[i]->GetWidth(), enemy[i]->GetHeight()) == true)
			{
				//敵のHPが0より大きかったら
				if (enemy[i]->GetHp() > 0)
				{
					//プレイヤーに一回だけダメージを与える
					PlayerDamage();
				}
			}
		}
	}

	//プレイヤーと転がる敵との当たり判定
	for (int i = 0; i < ROLLING_ENEMY_MAXNUM; i++)
	{
		if (player != nullptr && rolling_enemy[i] != nullptr) {
			//プレイヤーと転がる敵が当たったら
			if (player->HitCheck(rolling_enemy[i]->GetWorldLocation(), rolling_enemy[i]->GetWidth(), rolling_enemy[i]->GetHeight()) == true)
			{
				//敵のHPが0より大きかったら
				if (rolling_enemy[i]->GetHp() > 0)
				{
					//プレイヤーに一回だけダメージを与える
					PlayerDamage();
				}
			}

		}
	}
}

void GameMainScene::PickaxeHitEnemy()
{

	// 歩行エネミーとつるはしの当たり判定
	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		//歩行エネミーがNULLではないかつHPが0より大きかったら
		if (enemy[i] != nullptr && enemy[i]->GetHp() > 0)
		{
			//つるはしを振るってる時だけ
			if (player != nullptr && player->GetAttacking() == true)
			{
				//ダメージを一回だけ与える
				if (enemy_damage_once == false)
				{
					//つるはしとエネミーと当たってるかのチェック
					if (ac->HitCheck(enemy[i]->GetWorldLocation(), enemy[i]->GetWidth(), enemy[i]->GetHeight()) == true) {

						EnemyDamage(i, player->GetAttack());
						enemy_damage_once = true;
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

	// 転がるエネミーとつるはしの当たり判定
	for (int i = 0; i < ROLLING_ENEMY_MAXNUM; i++)
	{
		if (rolling_enemy[i] != nullptr)
		{
			if (rolling_enemy[i]->GetHp() > 0)
			{
				if (player != nullptr)
				{

					//つるはしを振るってる時だけ
					if (player->GetAttacking() == true)
					{
						//ダメージを一回だけ与える
						if (enemy_damage_once == false)
						{
							//つるはしとエネミーと当たってるかのチェック
							if (ac->HitCheck(rolling_enemy[i]->GetWorldLocation(), rolling_enemy[i]->GetWidth(), rolling_enemy[i]->GetHeight()) == true) {

								rolling_enemy[i]->Damage(10);
								enemy_damage_once = true;
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

}

void GameMainScene::DynamiteHitEnemy()
{
	//ダイナマイトと歩行エネミーの当たり判定
	for (int i = 0; i < DYNAMITE_MAXNUM; i++)
	{
		if (dynamite[i] != nullptr)
		{
			for (int j = 0; j < ENEMYMAXNUM; j++)
			{

				if (enemy[j] != nullptr && enemy[j]->GetHp() > 0)
				{
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

							EnemyDamage(j, dynamite[i]->GetAttack());
						}
					}

				}
			}
		}
	}


	//ダイナマイトとローリングエネミーの当たり判定
	for (int i = 0; i < DYNAMITE_MAXNUM; i++)
	{
		if (dynamite[i] != nullptr)
		{
			for (int j = 0; j < ROLLING_ENEMY_MAXNUM; j++) {
				if (rolling_enemy[j] != nullptr && rolling_enemy[j]->GetHp() > 0) {
					//ダイナマイトとエネミーと当たってるかのチェック
					if (dynamite[i]->GetDynamite() == false)
					{
						if (dynamite[i]->HitCheck(rolling_enemy[j]->GetWorldLocation(), rolling_enemy[j]->GetWidth(), rolling_enemy[j]->GetHeight()) == true)
						{
							dynamite[i]->SetDynamite(true);
							rolling_enemy[j]->Damage(dynamite[i]->GetAttack());
						}
					}
					//ダイナマイトの爆発とエネミーの当たり判定
					if (dynamite[i]->Getdamage_flg() == true)
					{
						if (dynamite[i]->HitCheck(rolling_enemy[j]->GetWorldLocation(), rolling_enemy[j]->GetWidth(), rolling_enemy[j]->GetHeight()) == true)
						{
							dynamite[i]->SetEnemyX(rolling_enemy[j]->GetWorldLocation().x);
							dynamite[i]->DamageCalculation();

						}
					}

				}
			}
		}
	}

}

//プレイヤーと床ブロックの当たり判定
void GameMainScene::PlayerHitBlock()
{
	//範囲内にいくつブロックが当たってるか数える
	for (int i = 0; i < block_count; i++)
	{
		if (player != nullptr && stage_block[i] != nullptr && stage_block[i]->GetBlockNum() == 1)
		{
			//プレイヤーを中心に128*128の範囲内にブロックが何個あるのか数える
			if (stage_block[i]->HitCheck(player->GetWorldLocation(), player->GetWidth() + 78.0f, 128.0f) == true)
			{
				//何番目のブロックが範囲内にあるのか格納する
				block_num[block_cnt] = i;
				block_cnt++;
			}

		}
	}


	for (int i = 0; i < block_cnt; i++)
	{
		if (player != nullptr && stage_block[block_num[i]] != nullptr && stage_block[block_num[i]]->GetBlockNum() == 1)
		{
			//もし範囲内のブロックと当たっていたら
			if (stage_block[block_num[i]]->HitCheck(player->GetWorldLocation(), player->GetWidth(), player->GetHeight()) == true)
			{
				player->HitCheckB(stage_block[block_num[i]]->GetVertex());
				//落ちれない状態にする
				player->SetFallFlg(false);
				//当たったブロックの上部の座標をプレイヤーの着地座標にいれる（プレイヤーの画像分ずらしている）
				player->SetLimitY(stage_block[block_num[i]]->GetLocation().y - (stage_block[block_num[i]]->GetHeight() / 2 + 5) - player->GetHeight() / 2);
				checkhit_block[i] = true;
			}
			else
			{
				checkhit_block[i] = false;
			}

		}
	}

	//もし範囲内のブロックに当たっていなかったら
	if (checkhit_block[0] == false && checkhit_block[1] == false && checkhit_block[2] == false)
	{
		//プレイヤーを落ちる状態にする
		player->SetFallFlg(true);
	}

	//初期化する
	for (int i = 0; i < block_cnt; i++)
	{
		checkhit_block[i] = false;
		block_num[i] = 0;
	}
	block_cnt = 0;

}

//オブジェクトにNullを入れる
void GameMainScene::SetObjectNull()
{
	object_num.cage_cnt = 0;
	object_num.cage_door_cnt = 0;
	object_num.falling_floor_cnt = 0;
	object_num.fragile_wall_cnt = 0;
	object_num.geyser_cnt = 0;
	object_num.lift_cnt = 0;
	object_num.magma_cnt = 0;
	object_num.rock_cnt = 0;

	for (int i = 0; i < FRAGILE_WALL_MAXNUM; i++)
	{
		fragile_wall[i] = nullptr;
	}
	for (int i = 0; i < CAGE_DOOR_MAXNUM; i++)
	{
		cage_door[i] = nullptr;
		cage[i] = nullptr;
	}
	for (int i = 0; i < MAGMA_MAXMUN; i++)
	{
		magma[i] = nullptr;
	}
	for (int i = 0; i < FALLING_FLOOR_MAXNUM; i++)
	{
		falling_floor[i] = nullptr;
	}
	for (int i = 0; i < GEYSER_MAXNUM; i++)
	{
		geyser[i] = nullptr;
	}
	for (int i = 0; i < LIFT_MAXNUM; i++)
	{
		lift[i] = nullptr;
	}
	for (int i = 0; i < ROCK_MAXNUM; i++)
	{
		rock[i] = nullptr;
	}
}

// 脆い壁更新処理
void GameMainScene::FragileWallUpdate()
{
	for (int i = 0; i < FRAGILE_WALL_MAXNUM; i++)
	{
		if (fragile_wall[i] == nullptr) continue;

		// カメラから見た座標の設定
		fragile_wall[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

		// 更新
		fragile_wall[i]->Update();

		if (fragile_wall[i]->GetDeleteFlg() == true)
		{
			// 脆い壁の削除
			delete fragile_wall[i];
			fragile_wall[i] = nullptr;
		}
	}
}

// ダイナマイトと脆い壁の当たり判定処理
void GameMainScene::DynamiteHitFragileWall()
{
	for (int i = 0; i < FRAGILE_WALL_MAXNUM; i++)
	{
		if (fragile_wall[i] != nullptr)
		{
			for (int j = 0; j < DYNAMITE_MAXNUM; j++)
			{
				if (dynamite[j] != nullptr)
				{
					// ダイナマイト本体との当たり判定
					if (dynamite[j]->GetDynamite() == false)
					{
						if (dynamite[j]->HitCheck(fragile_wall[i]->GetWorldLocation(), fragile_wall[i]->GetWidth(), fragile_wall[i]->GetHeight()) == true)
						{
							dynamite[j]->SetDynamite(true);
							fragile_wall[i]->Damage(dynamite[j]->GetAttack());
						}
					}
				}
			}
		}
	}
}

// プレイヤーと脆い壁の当たり判定処理
void GameMainScene::PlayerHitFragileWall()
{
	if (player == nullptr) return;
	for (int i = 0; i < FRAGILE_WALL_MAXNUM; i++)
	{
		if (fragile_wall[i] == nullptr) continue;

		// プレイヤーが脆い壁に当たっていたら
		if (player->HitCheck(fragile_wall[i]->GetWorldLocation(), fragile_wall[i]->GetWidth(), fragile_wall[i]->GetHeight()) == true)
		{
			// プレイヤーの歩行を止める
			player->HitCheckB(fragile_wall[i]->GetVertex());
		}
	}
}

// プレイヤーと壊れる岩の当たり判定処理
void GameMainScene::PlayerHitRock()
{
	for (int i = 0; i < object_num.rock_cnt; i++)
	{
		if (player != nullptr && rock[i] != nullptr)
		{
			// プレイヤーと岩が当たっていたら
			if (player->HitCheck(rock[i]->GetWorldLocation(), rock[i]->GetWidth(), rock[i]->GetHeight()) == true)
			{
				// プレイヤーの歩行を止める
				player->HitCheckB(rock[i]->GetVertex());
			}
		}
	}


}

//敵と岩の当たり判定
void GameMainScene::EnemyHitRock()
{

	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		if (enemy[i] != nullptr && enemy[i]->GetHp() > 0)
		{
			for (int j = 0; j < object_num.rock_cnt; j++)
			{
				if (rock[j]!=nullptr && enemy[i]->HitCheck(rock[j]->GetWorldLocation(), rock[j]->GetWidth(), rock[j]->GetHeight()) == true)
				{
					if (enemy[i]->GetIsKnockBack() == true)
					{
						// ノックバックしている敵に当たったら自身もノックバックを開始する
						enemy[i]->SetKnockBackStartFlg(true);
					}
					else
					{
						// 当たっていたら２体とも進行方向を反対に変更する
						enemy[i]->SetHitEnemyX(rock[j]->GetWorldLocation().x);
						enemy[i]->ChangeDirection();
					}
				}
			}
		}
	}


}

void GameMainScene::DynamiteHitRock()
{
	//ダイナマイトが岩と当たってるかのチェック
			//ダメージを一回だけ与える
	for (int i = 0; i < DYNAMITE_MAXNUM; i++)
	{

		for (int j = 0; j < object_num.rock_cnt; j++)
		{
			if (dynamite[i] != nullptr && dynamite[i]->GetDynamite() == false && rock[j] != nullptr && rock[j]->GetHp()>0)
			{
				//ダイナマイトと岩が当たったか？
				if (dynamite[i]->HitCheck(rock[j]->GetWorldLocation(), rock[j]->GetWidth(),rock[j]->GetHeight()) == true)
				{
					dynamite[i]->SetDynamite(true);

				}
				
			}

			//ダイナマイトの爆発と岩の当たり判定
			if (dynamite[i] != nullptr && dynamite[i]->Getdamage_flg() == true && rock[j] != nullptr)
			{
				if (dynamite[i]->HitCheck(rock[j]->GetWorldLocation(), rock[j]->GetWidth(), rock[j]->GetHeight()) == true)
				{
					dynamite[i]->SetEnemyX(rock[j]->GetWorldLocation().x);
					dynamite[i]->DamageCalculation();
					rock[j]->SetDamage(30);
					rock[j]->SetShakeFlg(true);
				}
			}
		}
		
	}


}

//つるはしと岩の当たり判定
void GameMainScene::PickaxeHitRock()
{
	for (int i = 0; i < object_num.rock_cnt; i++)
	{
		if (rock[i] != nullptr && player != nullptr)
		{
			//つるはしを振るってる時だけ
			if (player->GetAttacking() == true)
			{
				//ダメージを一回だけ与える
				if (rock_damage_once == false)
				{
					//つるはしと岩と当たってるかのチェック
					if (ac->HitCheck(rock[i]->GetWorldLocation(), rock[i]->GetWidth(), rock[i]->GetHeight()) == true) {
						rock[i]->SetDamage(10);
						rock[i]->SetShakeFlg(true);
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

//岩アップデート
void GameMainScene::RockUpdate()
{

	//岩を消す処理
	for (int i = 0; i < object_num.rock_cnt; i++)
	{
		if (rock[i] != nullptr)
		{
			rock[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
			rock[i]->Update();
		}

		if (rock[i] != nullptr&& rock[i]->GetDeleteFlg() == true)
		{
			rock[i] = nullptr;
		}
	}
}

//リフトアップデート
void GameMainScene::LiftUpDate()
{
	for (int i = 0; i < LIFT_MAXNUM; i++)
	{
		//リフトテスト後で消す
		if (lift[i] != nullptr)
		{
			lift[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
			lift[i]->SetScreenPos(screen_origin_position.x, screen_origin_position.y);
			if (ac != nullptr && player != nullptr)
			{
				lift[i]->Update(ac, player);
			}
		}
	}
}

//プレイヤーとリフトの当たり判定
void GameMainScene::PlayerHitLift()
{
	for (int i = 0; i < LIFT_MAXNUM; i++)
	{
		if (lift[i] != nullptr && player != nullptr)
		{

			if (player->HitCheck(lift[i]->GetWorldLocation(), lift[i]->GetWidth(), lift[i]->GetHeight()) == true) {
				//lift[0]->SetCanMove(true);
				player->SetY(lift[i]->GetWorldLocation().y);

			}
			else if (player->GetLimitY() > player->GetWorldLocation().y)
			{
				//当たってないかつプレイヤーがlimitの値より上に居たら
				//プレイヤーが落ちる
				player->SetFallFlg(true);
			}
		}
	}
}

//リフトとリフトとめる奴の判定
void GameMainScene::LiftHitStop()
{
	for (int i = 0; i < LIFT_MAXNUM; i++)
	{
		for (int j = 0; j < block_count; j++)
		{
			if (lift[i] != nullptr && stage_block[j] != nullptr && stage_block[j]->GetBlockNum()==18)
			{
				if (lift[i]->HitCheck(stage_block[j]->GetWorldLocation(), stage_block[j]->GetWidth(), stage_block[j]->GetHeight()))
				{
					lift[i]->SetUpMaxY(stage_block[j]->GetWorldLocation().y);
				}
			}
		}
	}

}

// 檻の更新処理
void GameMainScene::CageUpdate()
{
	for (int i = 0; i < CAGE_DOOR_MAXNUM; i++)
	{
		if (cage[i] == nullptr) continue;

		// カメラから見た座標の設定
		cage[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

		cage[i]->Update();
	}
}

// 檻のドアの更新処理
void GameMainScene::CageDoorUpdate()
{
	for (int i = 0; i < CAGE_DOOR_MAXNUM; i++)
	{
		if (cage_door[i] == nullptr) continue;

		// カメラから見た座標の設定
		cage_door[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

		cage_door[i]->Update();
	}
}

// プレイヤーと檻のドアの当たり判定
void GameMainScene::PlayerHitCageDoor()
{
	if (player == nullptr) return;

	for (int i = 0; i < CAGE_DOOR_MAXNUM; i++)
	{
		if (cage_door[i] == nullptr) continue;

		// プレイヤーが閉まっている檻のドアに当たっていたら
		if (cage_door[i]->GetOpenFlg() == false && player->HitCheck(cage_door[i]->GetWorldLocation(), cage_door[i]->GetWidth(), cage_door[i]->GetHeight()) == true)
		{
			// プレイヤーの歩行を止める
			player->HitCheckB(cage_door[i]->GetVertex());
		}
	}
}

// プレイヤーが檻の中にいるのか調べる
void GameMainScene::CheckPlayerInCage()
{
	if (player == nullptr) return;

	for (int i = 0; i < CAGE_DOOR_MAXNUM; i++)
	{
		if (cage_door[i] == nullptr) continue;

		// プレイヤーが檻の中にいたら
		if (player->HitCheck(cage[i]->GetWorldLocation(), cage[i]->GetWidth(), cage[i]->GetHeight()) == true)
		{
			// 檻が透ける
			cage[i]->SetInsideFlg(true);

			// プレイヤーが檻の端についたら歩行を止める
			player->CheckEdgeCage(cage[i]->GetVertex().left_x);
		}
		else
		{
			// 檻が透けない
			cage[i]->SetInsideFlg(false);
		}
	}
}

// 檻のドアへの攻撃判定
void GameMainScene::AttackCageDoor()
{
	for (int i = 0; i < CAGE_DOOR_MAXNUM; i++)
	{
		if (player != nullptr && cage_door[i] != nullptr)
		{
			for (int i = 0; i < DYNAMITE_MAXNUM; i++)
			{
				if (dynamite[i] != nullptr)
				{
					// ダイナマイト本体との当たり判定
					if (dynamite[i]->GetDynamite() == false)
					{
						if (dynamite[i]->HitCheck(cage_door[i]->GetWorldLocation(), cage_door[i]->GetWidth(), cage_door[i]->GetHeight()) == true)
						{
							dynamite[i]->SetDynamite(true);
							cage_door[i]->Damage(dynamite[i]->GetAttack());
						}
					}
				}
			}

			//つるはしを振るってる時だけ
			if (player->GetAttacking() == true)
			{
				//ダメージを一回だけ与える
				if (enemy_damage_once == false)
				{
					//つるはしとエネミーと当たってるかのチェック
					if (ac->HitCheck(cage_door[i]->GetWorldLocation(), cage_door[i]->GetWidth(), cage_door[i]->GetHeight()) == true)
					{
						cage_door[i]->Damage(player->GetAttack());
						enemy_damage_once = true;
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

// マグマの更新処理
void GameMainScene::MagmaUpdete()
{
	for (int i = 0; i < MAGMA_MAXMUN; i++)
	{
		if (magma[i] == nullptr) continue;

		// カメラから見た座標の設定
		magma[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

		magma[i]->Update();
	}
}

// プレイヤーとマグマの当たり判定処理
void GameMainScene::PlayerHitMagma()
{
	if (player == nullptr)			return;

	for (int i = 0; i < MAGMA_MAXMUN; i++)
	{
		if (magma[i] == nullptr)	continue;
		if (magma[i]->GetAnyDamageFlg() == false) continue;

		// プレイヤーがマグマに当たっていたら
		if (player->HitCheck(magma[i]->GetWorldLocation(), magma[i]->GetWidth(), magma[i]->GetHeight()) == true)
		{
			//プレイヤーに一回だけダメージを与える
			PlayerDamage();
		}
	}
}

// 落ちる床の更新処理
void GameMainScene::FallingFloorUpdate()
{
	for (int i = 0; i < FALLING_FLOOR_MAXNUM; i++)
	{
		if (falling_floor[i] == nullptr) continue;

		// カメラから見た座標の設定
		falling_floor[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

		falling_floor[i]->Update();
	}
}

// プレイヤーと落ちる床の当たり判定
void GameMainScene::PlayerHitFallingFloor()
{
	if (player == nullptr)					return;

	for (int i = 0; i < FALLING_FLOOR_MAXNUM; i++)
	{
		if (falling_floor[i] == nullptr)	continue;

		// プレイヤーが落ちる床に当たったら
		if (player->HitCheck(falling_floor[i]->GetWorldLocation(), falling_floor[i]->GetWidth(), falling_floor[i]->GetHeight()) == true)
		{
			// プレイヤーの落下を止める
			player->HitCheckB(falling_floor[i]->GetVertex());
		}
	}
}

// つるはしと落ちる床の当たり判定
void GameMainScene::PickaxeHitFallingFloor()
{
	if (player == nullptr)					return;
	if (ac == nullptr)						return;
	//プレイヤーがつるはし振っていない
	if (player->GetAttacking() == false)	return;

	for (int i = 0; i < FALLING_FLOOR_MAXNUM; i++)
	{
		if (falling_floor[i] == nullptr)				continue;
		if (falling_floor[i]->GetFallingFlg() == true)	continue;

		//つるはしと落ちる床が当たっていたら
		if (ac->HitCheck(falling_floor[i]->GetWorldLocation(), falling_floor[i]->GetWidth(), falling_floor[i]->GetHeight()) == true)
		{
			// 落下開始
			falling_floor[i]->StartFalling();
		}
	}
}

// 落ちる床とマグマの当たり判定
void GameMainScene::FallingFloorHitMagma()
{
	for (int i = 0; i < FALLING_FLOOR_MAXNUM; i++)
	{
		if (falling_floor[i] == nullptr)					continue;
		if (falling_floor[i]->GetTouchedMagma() == true)	continue;

		for (int j = 0; j < MAGMA_MAXMUN; j++)
		{
			if (magma[j] == nullptr)					continue;

			// 落ちる床がマグマに当たっていなかったら
			if (falling_floor[i]->HitCheck(magma[j]->GetWorldLocation(), magma[j]->GetWidth(), magma[j]->GetHeight()) == false)
			{
				// ループの初めに戻る
				continue;
			}

			if (magma[j]->GetAnyDamageFlg() == true)
			{
				// マグマのダメージを無効にする
				magma[j]->NullificationDamage();
				continue;
			}

			// 落ちる床の中心座標がマグマの中心座標以上になったら
			if (falling_floor[i]->GetWorldLocation().y >= magma[j]->GetWorldLocation().y)
			{
				// 落ちる床の落下を止める
				falling_floor[i]->StopFalling();
			}
		}
	}
}

// 間欠泉の更新処理
void GameMainScene::GeyserUpdete()
{
	for (int i = 0; i < GEYSER_MAXNUM; i++)
	{
		if (geyser[i] == nullptr) continue;

		// カメラから見た座標の設定
		geyser[i]->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

		geyser[i]->Update();
	}
}

// プレイヤーと間欠泉の当たり判定
void GameMainScene::PlayerHitGeyser()
{
	if (player == nullptr)			return;

	for (int i = 0; i < GEYSER_MAXNUM; i++)
	{
		if (geyser[i] == nullptr)	continue;

		// プレイヤーが落ちる床に当たったら
		if (player->HitCheck(geyser[i]->GetWorldLocation(), geyser[i]->GetWidth(), geyser[i]->GetHeight()) == true)
		{
			// プレイヤーの落下を止める
			// player->HitCheckB(geyser[i]->GetVertex());
			player->SetY(geyser[i]->GetWorldLocation().y - geyser[i]->GetHeight() / 2);
		}
	}
}

// つるはしと間欠泉の当たり判定
void GameMainScene::PickaxeHitGeyser()
{
	if (player == nullptr)								return;
	if (ac == nullptr)									return;
	//つるはしを振っていない
	if (player->GetAttacking() == false)				return;

	for (int i = 0; i < GEYSER_MAXNUM; i++)
	{
		if (geyser[i] == nullptr)						continue;
		// 間欠泉から水が止まっていなかったら
		if (geyser[i]->GetStopWaterFlg() == false)		continue;

		//つるはしと間欠泉が当たっていたら
		if (ac->HitCheck(geyser[i]->GetWorldLocation(), geyser[i]->GetWidth(), geyser[i]->GetHeight()) == true)
		{
			// 間欠泉から水が噴き出る
			geyser[i]->WaterComesOut();
		}
	}
}

//プレイヤーとリスポーンブロックの当たり判定
void GameMainScene::PlayerHitRespawn()
{
	for (int i = 0; i < block_count; i++)
	{
		if (player!=nullptr && stage_block[i] != nullptr && stage_block[i]->GetBlockNum() == 18)
		{
			if (player->HitCheck(stage_block[i]->GetWorldLocation(), stage_block[i]->GetWidth(), stage_block[i]->GetHeight()) == true)
			{
				respawn_x = stage_block[i]->GetWorldLocation().x;
				respawn_y = stage_block[i]->GetWorldLocation().y;
			}
		}
	}
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
		return new GameOverScene();
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