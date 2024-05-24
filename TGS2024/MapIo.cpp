#include "MapIo.h"

MapIo::MapIo()
{
	map_array[map_blockmax_x][map_blockmax_y];

	fp = NULL;
	count = 0;
	add_x = 0;
	map_data_num = 1;
	p_localx = 0;
	p_worldx = 0;
	world_mouse_x = 0;
}

MapIo::~MapIo()
{
}

void MapIo::LoadMapData()
{
	//ファイルを読込モードで開く
	fopen_s(&fp, "stage/stage1.csv", "r");

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

void MapIo::InputTest(GameMainScene* gamemain)
{
	input.InputUpdate();

	GetMousePoint(&mouse_x, &mouse_y);

	//小さいほう
	if (input.CheckBtn(XINPUT_BUTTON_RIGHT_SHOULDER) == TRUE)
	{
		add_x += 1280;

	}
	//小さいほう
	if (input.CheckBtn(XINPUT_BUTTON_LEFT_SHOULDER) == TRUE)
	{
		if (add_x > 0)
		{
			add_x -= 1280;
		}
	}
	//1280

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


	now_abs = fabsf(mouse_x - p_localx);
	//マウスがプレイヤーの右に居たら
	if (mouse_x > p_localx)
	{
		world_mouse_x = p_worldx+now_abs;
	}

	if (mouse_x < p_localx)
	{
		world_mouse_x = p_worldx - now_abs;
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

void MapIo::SaveMapData()
{
	//ファイルを書き込みモードで開く
	fopen_s(&fp, "stage/stage1.csv", "w");

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

void MapIo::Draw() const
{

	for (int i = 0; i < map_blockmax_y; i++)
	{
		for (int j = 0; j < map_blockmax_x; j++)
		{
			if (map_array[i][j] == 1)
			{
				DrawBox(j * BLOCKSIZE, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE, i * BLOCKSIZE + BLOCKSIZE, 0xffffff, FALSE);
			}
			else if (map_array[i][j] == 2)
			{
				DrawBox(j * BLOCKSIZE, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE, i * BLOCKSIZE + BLOCKSIZE, 0x000000, FALSE);
			}
			else if (map_array[i][j] == 3)
			{
				DrawBox(j * BLOCKSIZE, i * BLOCKSIZE, j * BLOCKSIZE + BLOCKSIZE, i * BLOCKSIZE + BLOCKSIZE, 0xffff00, FALSE);
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
		DrawFormatString(40, 80, 0xffffff, "PUT_MAPChip");

		break;
	case 2:
		DrawFormatString(40, 80, 0xffffff, "PUT_ENEMY");
		break;
	case 3:
		DrawFormatString(40, 80, 0xffffff, "PUT_Goal");
		break;
	}

}
