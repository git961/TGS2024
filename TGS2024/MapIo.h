#pragma once
#include "GameMainScene.h"
#include <vector>
#include "DxLib.h"
#include "stdio.h"
#include "Define.h"
#include "padinput.h"


class GameMainScene;


class MapIo
{
private:
	Input input;

	int count;
	//const int map_blockmax_x=FIELD_WIDTH/64;
	//const int map_blockmax_y =FIELD_HEIGHT/64;
	//int block_num= map_blockmax_x * map_blockmax_y;

	//int *map_data = new int[block_num];

	int map_array[map_blockmax_y][map_blockmax_x];
	//真ん中の座標を手に居れる
	int stage_block_pos[map_blockmax_x][map_blockmax_y];

	FILE* fp;
	int map_get;

	int mouse_x;
	int mouse_y;

	int add_x;

	int map_data_num;//0:何もなし 1:マップチップ　2:エネミー

public:
	MapIo();
	~MapIo();

	void LoadMapData();//マップデータ読込
	void InputTest(GameMainScene* gamemain);//エディタテスト
	void SaveMapData();//マップデータ保存
	void Draw() const;
	int GetMapData(int j, int i) { return map_array[j][i]; }
};

