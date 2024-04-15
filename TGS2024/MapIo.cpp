#include "MapIo.h"

MapIo::MapIo()
{
	map_array[map_blockmax_x][map_blockmax_y];

	fp = NULL;
	count = 0;
}

MapIo::~MapIo()
{
}

void MapIo::LoadMapData()
{
	//ファイル読込
	fopen_s(&fp, "stage/stage1.csv", "r");

	for (int i = 0; i < map_blockmax_y; i++)
	{
		for (int j = 0; j < map_blockmax_x; j++)
		{
			if (fscanf_s(fp, "%d,", &map_array[i][j]) != EOF) {
				count++;
			}
		}
	}


	fclose(fp);
}

void MapIo::InputTest(GameMainScene* gamemain)
{
	GetMousePoint(&mouse_x, &mouse_y);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT)!=0){
		//押されてる
		for (int i = 0; i < map_blockmax_y; i++)
		{
			for (int j = 0; j < map_blockmax_x; j++)
			{
				//もしこの範囲に居たら
				//ワールド座標とマウスの座標を比べる
				if (j-1*64<mouse_x&&j*64>mouse_x) {
					if (j - 1 * 64 < mouse_y&&i * 64 > mouse_y)
					{
						
						map_array[i][j] = 1;
					}
				}
			}
		}

	}
	else
	{
		//押されていない
	}



}
