#include "MapIo.h"

MapIo::MapIo()
{
	//map_array[map_blockmax_x][map_blockmax_y]={0};

	fp = NULL;
	count = 0;
	add_x = 0;
	map_data_num = 1;
	p_localx = 0.0f;
	p_worldx = 0.0f;
	world_mouse_x = 0.0f;
	world_posx = 0.0f;
	local_posx = 0.0f;
	map_get = 0;
	mouse_x = 0;
	mouse_y = 0;
	now_abs = 0.0f;
	posx = 0.0f;
	stage_num = stage1;
}

MapIo::~MapIo()
{
}

void MapIo::LoadMapData(int set_stage_num)
{
	stage_num = set_stage_num;

	if (stage_num == stage1)
	{
		//ファイルを読込モードで開く
		fopen_s(&fp, "stage/stage1.csv", "r");
	}
	else if (stage_num == stage2)
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


	if (CheckHitKey(KEY_INPUT_1) == TRUE)
	{
		map_data_num = 1;
	}

	if (CheckHitKey(KEY_INPUT_2) == TRUE)
	{
		map_data_num = 2;
	}

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

	//リスポーン位置更新ブロック
	if (CheckHitKey(KEY_INPUT_F) == TRUE)
	{
		map_data_num = 18;
	}

	now_abs = fabsf(mouse_x - local_posx);

	//マウスがプレイヤーの右に居たら
	/*if (mouse_x > p_localx)
	{
		world_mouse_x = p_worldx+now_abs;
	}

	if (mouse_x < p_localx)
	{
		world_mouse_x = p_worldx - now_abs;
	}*/


	if (mouse_x > local_posx)
	{
		world_mouse_x = world_posx + now_abs;
	}

	if (mouse_x < local_posx)
	{
		world_mouse_x = world_posx - now_abs;
	}


	//ブロック追加
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		//押されてる
		//i=ｙ座標
		for (int i = 0; i < map_blockmax_y; i++)
		{
			//j=ｘ座標
			for (int j = 0; j < map_blockmax_x; j++)
			{
				//もしこの範囲に居たら
				//ワールド座標とマウスの座標を比べる
				if (j * BLOCKSIZE < world_mouse_x && j * BLOCKSIZE + BLOCKSIZE >world_mouse_x) {
					if (i * BLOCKSIZE < mouse_y && i * BLOCKSIZE + BLOCKSIZE > mouse_y)
					{
						map_array[i][j] = map_data_num;

						//j*BLOCKSIZE=左上の座標＋幅/２すれば真ん中のY
						//i*BLOCKSIZE=左上の座標＋幅/２すれば真ん中のY
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
					if (i * BLOCKSIZE < mouse_y && i * BLOCKSIZE + BLOCKSIZE > mouse_y)
					{
						map_array[i][j] = 0;
					}
				}
			}
		}

	}


}

void MapIo::SaveMapData(int set_stage_num)
{
	stage_num = set_stage_num;

	if (stage_num == stage1)
	{
		//ファイルを書き込みモードで開く
		fopen_s(&fp, "stage/teststage.csv", "w");
	}
	else if (stage_num == stage2)
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

	for (int i = 0; i < map_blockmax_y; i++)
	{
		for (int j = 0; j < map_blockmax_x; j++)
		{
			switch (map_array[i][j])
			{
			case 1:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE, 0xffffff, FALSE);
				break;
			case 2:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE, 0xfff000, FALSE);
				break;
			case 3:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE, 0xffff00, FALSE);
				break;
			case 4:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE, 0x00fff0, FALSE);
				break;
			case 8:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE, 0xff0000, FALSE);
				break;
			case 9:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE, 0x008000, FALSE);
				break;
			case 12:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE, 0xf5deb3, FALSE);
				break;
			case 13:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE, 0xdc143c, FALSE);
				break;
			case 14:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE, 0xb0c4de, FALSE);
				break;
			case 15:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE, 0x4169e1, FALSE);
				break;
			case 16:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE, 0xffd700, FALSE);
				break;
			case 17:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE, 0xd2691e, FALSE);
				break;
			case 18:
				DrawBox(j * BLOCKSIZE - (int)posx, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE - (int)posx, i * BLOCKSIZE + BLOCKSIZE, 0x008000, FALSE);
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

	DrawFormatString(40, 40, 0xffffff, "add_x:%d", add_x);
	
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
		DrawFormatString(40, 200, 0xffffff, "PUT_RespawnBlock");
		break;
	}
	
}
