#pragma once
#include "GameMainScene.h"
#include <vector>
#include "DxLib.h"
#include "stdio.h"
#include "Define.h"
#include "padinput.h"
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

class GameMainScene;
enum class StageNum;

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
	//vector<vector<int>>  map_array[map_blockmax_y][map_blockmax_x];
	

	FILE* fp;
	int map_get;

	int mouse_x;
	int mouse_y;

	float world_mouse_x;
	float world_mouse_y;

	float p_localx;
	float p_worldx;

	float now_abs_x;
	float now_abs_y;

	int add_x;

	int map_data_num;//0:何もなし 1:マップチップ　2:エネミー 3:ゴール

	float posx;
	float posy;
	float local_posx;
	float world_posx;
	float local_posy;
	float world_posy;

	int stage_num;


public:
	MapIo();
	~MapIo();

	void LoadMapData(StageNum set_num);//マップデータ読込
	void InputTest(GameMainScene* gamemain);//エディタテスト
	void SaveMapData(StageNum set_num);//マップデータ保存
	void Draw() const;
	int GetMapData(int j, int i) { return map_array[j][i]; }
	//vector<vector<int>> GetMapData(int j, int i) { return map_array[j][i]; }

	void SetPlayerLocal(float set_localx) { p_localx = set_localx; }
	void SetPlayerWorld(float set_worldx) { p_worldx = set_worldx; }

	void SetOriginPos(float set_origin_posx, float set_origin_posy) { posx = set_origin_posx; posy = set_origin_posy; }
	void SetLocalPos(float set_local_posx, float set_local_posy) { local_posx = set_local_posx; local_posy = set_local_posy; }
	void SetWorldPos(float set_world_posx, float set_world_posy) { world_posx = set_world_posx; world_posy = set_world_posy; }

	void SetStageNum(int set_stage_num) { stage_num = set_stage_num; }
};

