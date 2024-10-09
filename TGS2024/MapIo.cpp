#include "MapIo.h"

MapIo::MapIo()
{
	//map_array[map_blockmax_x][map_blockmax_y]={0};

	for (int i = 0; i < map_blockmax_y; i++)
	{
		for (int j = 0; j < map_blockmax_x; j++)
		{
			map_array[i][j] = 0;
		}
	}


	fp = NULL;
	count = 0;
	add_x = 0;
	map_data_num = 1;
	p_localx = 0.0f;
	p_worldx = 0.0f;
	world_mouse_x = 0.0f;
	world_mouse_y = 0.0f;
	world_posx = 0.0f;
	local_posx = 0.0f;
	world_posy = 0.0f;
	local_posy = 0.0f;
	map_get = 0;
	mouse_x = 0;
	mouse_y = 0;
	now_abs_x = 0.0f;
	now_abs_y = 0.0f;
	posx = 0.0f;
	posy = 0.0f;
	//stage_num = StageNum::stage1;


}

MapIo::~MapIo()
{
	fp = NULL;
}

void MapIo::LoadMapData(StageNum set_num)
{

	if (set_num==StageNum::stage1)
	{
		//ファイルを読込モードで開く
		fopen_s(&fp, "stage/stage1.csv", "r");
	}
	else if (set_num == StageNum::stage2)
	{
		//ファイルを読込モードで開く
		fopen_s(&fp, "stage/stage2.csv", "r");
	}

	if (fp)
	{
		for (int i = 0; i < map_blockmax_y; i++)
		{
			for (int j = 0; j < map_blockmax_x; j++)
			{
				//ファイル読込
				if (fscanf_s(fp, "%d,", &map_array[i][j]) != EOF) {
					count++;
				}
			}
		}

		fclose(fp);
	}


}

void MapIo::InputTest(GameMainScene* gamemain)
{
	input.InputUpdate();

	GetMousePoint(&mouse_x, &mouse_y);

	//床ブロック
	if (CheckHitKey(KEY_INPUT_1) == TRUE)
	{
		map_data_num = 1;
	}

	if (CheckHitKey(KEY_INPUT_2) == TRUE)
	{
		map_data_num = 2;
	}

	//ゴール
	if (CheckHitKey(KEY_INPUT_3) == TRUE)
	{
		map_data_num = 3;
	}

	//岩
	if (CheckHitKey(KEY_INPUT_4) == TRUE)
	{
		map_data_num = 4;
	}

	//袋:チュートリアル用
	if (CheckHitKey(KEY_INPUT_5) == TRUE)
	{
		map_data_num = 5;
	}
	//看板:チュートリアル用
	if (CheckHitKey(KEY_INPUT_6) == TRUE)
	{
		map_data_num = 6;
	}

	//ヘルメット:チュートリアル用
	if (CheckHitKey(KEY_INPUT_7) == TRUE)
	{
		map_data_num = 7;
	}

	//落下してくる敵用
	if (CheckHitKey(KEY_INPUT_8) == TRUE)
	{
		map_data_num = 8;
	}

	//落下してくる敵用
	if (CheckHitKey(KEY_INPUT_9) == TRUE)
	{
		map_data_num = 9;
	}

	//看板:チュートリアル用
	if (CheckHitKey(KEY_INPUT_T) == TRUE)
	{
		map_data_num = 10;
	}
	//看板:チュートリアル用
	if (CheckHitKey(KEY_INPUT_Y) == TRUE)
	{
		map_data_num = 11;
	}

	//もろい壁
	if (CheckHitKey(KEY_INPUT_U) == TRUE)
	{
		map_data_num = 12;
	}

	//マグマ
	if (CheckHitKey(KEY_INPUT_I) == TRUE)
	{
		map_data_num = 13;
	}

	//落ちる床
	if (CheckHitKey(KEY_INPUT_O) == TRUE)
	{
		map_data_num = 14;
	}

	//間欠泉
	if (CheckHitKey(KEY_INPUT_A) == TRUE)
	{
		map_data_num = 15;
	}

	//檻
	if (CheckHitKey(KEY_INPUT_S) == TRUE)
	{
		map_data_num = 16;
	}

	//リフト
	if (CheckHitKey(KEY_INPUT_D) == TRUE)
	{
		map_data_num = 17;
	}

	//リフト上上限ブロック
	if (CheckHitKey(KEY_INPUT_F) == TRUE)
	{
		map_data_num = 18;
	}

	//リスポーン位置更新ブロック
	if (CheckHitKey(KEY_INPUT_G) == TRUE)
	{
		map_data_num = 19;
	}

	//あしなが岩
	if (CheckHitKey(KEY_INPUT_H) == TRUE)
	{
		map_data_num = 20;
	}

	//Hard岩（ダイナマイトじゃないと壊れない岩
	if (CheckHitKey(KEY_INPUT_J) == TRUE)
	{
		map_data_num = 21;
	}

	//つるはし攻撃で転がる岩
	if (CheckHitKey(KEY_INPUT_K) == TRUE)
	{
		map_data_num = 22;
	}

	//グリーン宝石
	if (CheckHitKey(KEY_INPUT_L) == TRUE)
	{
		map_data_num = 23;
	}

	now_abs_x = fabsf(mouse_x - local_posx);
	now_abs_y = fabsf(mouse_y - local_posy);


	if (mouse_y > local_posy)
	{
		world_mouse_y = world_posy + now_abs_y;
	}

	if (mouse_y < local_posy)
	{
		world_mouse_y = world_posy - now_abs_y;
	}

	//mouse_x(マウスの座標)-local_posx(カメラ左端の座標)でマウスのworld座標を出す
	world_mouse_x = fabs(mouse_x - local_posx);

	//ブロック追加
	//マウスが左クリックされたら
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

		for (int i = 0; i < map_blockmax_y; i++)
		{
			//j=ｘ座標
			for (int j = 0; j < map_blockmax_x; j++)
			{
				//j*BLOCKSIZE=ブロックのx座標 i*BLOCKSIZE=ブロックのy座標
				//もしこのブロック座標範囲にマウスが居たら
				if (j * BLOCKSIZE < world_mouse_x && j * BLOCKSIZE + BLOCKSIZE >world_mouse_x) {
					if (i * BLOCKSIZE < world_mouse_y && i * BLOCKSIZE + BLOCKSIZE > world_mouse_y)
					{
						map_array[i][j] = map_data_num;
					}
				}
			}
		}

	}


	//ブロック消去
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		//押されていない
		for (int i = 0; i < map_blockmax_y; i++)
		{
			for (int j = 0; j < map_blockmax_x; j++)
			{
				//もしこの範囲に居たら
				//ワールド座標とマウスの座標を比べる
				if (j * BLOCKSIZE < world_mouse_x && j * BLOCKSIZE + BLOCKSIZE >world_mouse_x) {
					if (i * BLOCKSIZE <world_mouse_y && i * BLOCKSIZE + BLOCKSIZE > world_mouse_y)
					{
						map_array[i][j] = 0;
					}
				}
			}
		}

	}


}

void MapIo::SaveMapData(StageNum set_num)
{


	if (set_num == StageNum::stage1)
	{
		//ファイルを書き込みモードで開く
		fopen_s(&fp, "stage/stage1.csv", "w");
	}
	else if (set_num == StageNum::stage2)
	{
		//ファイルを書き込みモードで開く
		fopen_s(&fp, "stage/stage2.csv", "w");
	}

	if (fp)
	{
		for (int i = 0; i < map_blockmax_y; i++)
		{
			for (int j = 0; j < map_blockmax_x; j++)
			{
				//ファイル書き込み
				//ファイルポインタ、%dで書き込み,map_arrayを入力
				fprintf_s(fp, "%d,", map_array[i][j]);

			}
		}

		fclose(fp);
	}
}

void MapIo::Draw() const
{
	//DrawFormatString(mouse_x, mouse_y, 0xffffff, "x: %f", world_mouse_x);
	//DrawFormatString(mouse_x,mouse_y +20, 0xffffff, "y: %f", world_mouse_y);


	for (int i = 0; i < map_blockmax_y; i++)
	{
		for (int j = 0; j < map_blockmax_x; j++)
		{
			switch (map_array[i][j])
			{
			case 1:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE- (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0xffffff, FALSE);
				break;
			case 2:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0xfff000, FALSE);
				break;
			case 3:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0xffff00, FALSE);
				break;
			case 4:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE- (int)posy, 0x00fff0, FALSE);
				break;
			case 8:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0xff0000, FALSE);
				break;
			case 9:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0x008000, FALSE);
				break;
			case 12:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0xf5deb3, FALSE);
				break;
			case 13:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0xdc143c, FALSE);
				break;
			case 14:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0xb0c4de, FALSE);
				break;
			case 15:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0x4169e1, FALSE);
				break;
			case 16:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0xffd700, FALSE);
				break;
			case 17:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0xd2691e, FALSE);
				break;
			case 18:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0x1d86d1, FALSE);
				break;
			case 19:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0x008000, FALSE);
				break;
			case 20:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0xff1493, FALSE);
				break;
			case 21:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0xb22222, FALSE);
				break;
			case 22:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0x778899, FALSE);
				break;
			case 23:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE - (int)posy, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE - (int)posy, 0xfff0f5, FALSE);
				break;
			}
		}
	}

	for (int i = 0; i < map_blockmax_y; i++)
	{
		for (int j = 0; j < map_blockmax_x; j++)
		{
			//もしこの範囲に居たら
			//ワールド座標とマウスの座標を比べる

			if (j * BLOCKSIZE < mouse_x && j * BLOCKSIZE + BLOCKSIZE > mouse_x) {
				if (i * BLOCKSIZE < mouse_y && i * BLOCKSIZE + BLOCKSIZE > mouse_y)
				{
					DrawBox(j * BLOCKSIZE, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE, i * BLOCKSIZE + BLOCKSIZE, 0xffffff, FALSE);
				}
			}
		}
	}
	
	switch (map_data_num)
	{
	case 1:
		DrawFormatString(40, 200, 0xffffff, "PUT_MAPChip");

		break;
	case 2:
		DrawFormatString(40, 200, 0xffffff, "PUT_ENEMY");
		break;
	case 3:
		DrawFormatString(40, 200, 0xffffff, "PUT_Goal");
		break;
	case 4:
		DrawFormatString(40, 200, 0xffffff, "PUT_ROCK");
		break;
	case 8:
		DrawFormatString(40, 200, 0xffffff, "PUT_FALL_ENEMY");
		break;
	case 9:
		DrawFormatString(40, 200, 0xffffff, "PUT_ROLLING_ENEMY");
		break;
	case 12:
		DrawFormatString(40, 200, 0xffffff, "PUT_FragileWall");
		break;
	case 13:
		DrawFormatString(40, 200, 0xffffff, "PUT_Magma");
		break;
	case 14:
		DrawFormatString(40, 200, 0xffffff, "PUT_FallingFloor");
		break;
	case 15:
		DrawFormatString(40, 200, 0xffffff, "PUT_Geyser");
		break;
	case 16:
		DrawFormatString(40, 200, 0xffffff, "PUT_CageDoor");
		break;
	case 17:
		DrawFormatString(40, 200, 0xffffff, "PUT_LIFT");
		break;
	case 18:
		DrawFormatString(40, 200, 0xffffff, "PUT_LIFTUPMAX");
		break;
	case 19:
		DrawFormatString(40, 200, 0xffffff, "PUT_RespawnBlock");
		break;
	case 20:
		DrawFormatString(40, 200, 0xffffff, "PUT_LongLegsEnemy");
		break;
	case 21:
		DrawFormatString(40, 200, 0xffffff, "PUT_HardEnemy");
		break;
	case 22:
		DrawFormatString(40, 200, 0xffffff, "PUT_ReboundEnemy");
		break;
	case 23:
		DrawFormatString(40, 200, 0xffffff, "PUT_GreenGem");
		break;
	}
	
}
