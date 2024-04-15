#pragma once
#include "GameMainScene.h"
#include <vector>
#include "DxLib.h"
#include "stdio.h"

class GameMainScene;

#define map_blockmax_x 2560 / 64
#define map_blockmax_y 720 / 64
class MapIo
{
private:

	int count;
	//const int map_blockmax_x=FIELD_WIDTH/64;
	//const int map_blockmax_y =FIELD_HEIGHT/64;
	//int block_num= map_blockmax_x * map_blockmax_y;

	//int *map_data = new int[block_num];

	int map_array[map_blockmax_y][map_blockmax_x];
	
	FILE* fp;
	int map_get;

	int mouse_x;
	int mouse_y;

public:
	MapIo();
	~MapIo();

	void LoadMapData();
	void InputTest(GameMainScene *gamemain);//エディタテスト

};

