#pragma once
#include "GameMainScene.h"
#include <vector>
#include "DxLib.h"
#include "stdio.h"
#include "Define.h"
#include "padinput.h"
#include <math.h>

class GameMainScene;

enum StageNum
{
	stage1,
	stage2
};

class MapIo
{
private:
	Input input;

	int count;
	//const int map_blockmax_x=FIELD_WIDTH/64;
	//const int map_blockmax_y =FIELD_HEIGHT/64;
	//int block_num= map_blockmax_x * map_blockmax_y;

	//int *map_data = new int[block_num];

	int map_array[map_blockmax_y][map_blockmax_x]={0};
	//真ん中の座標を手に居れる
	int stage_block_pos[map_blockmax_x][map_blockmax_y]={0};

	FILE* fp;
	int map_get;

	int mouse_x;
	int mouse_y;

	float world_mouse_x;

	float p_localx;
	float p_worldx;

	float now_abs;

	int add_x;

	int map_data_num;//0:何もなし 1:マップチップ　2:エネミー 3:ゴール

	float posx;
	float local_posx;
	float world_posx;
		//キャラのlocationとスクリーンの原点を引いてスクリーン座標上の位置に変換
	//void SetLocalPosition(float set_origin_posx, float set_origin_posy)
	//{
	//	//ワールド座標ースクリーン座標の原点してオブジェクトのスクリーン座標を出す計算
	//	location.x= world.x - set_origin_posx;
	//	location.y = world.y - set_origin_posy;
	//};

	int stage_num;				// 開きたいステージファイル判別用

	int lift_num;//リフトの番号数える用
	float lift_up_max[LIFT_MAXNUM]={0.0f};
	bool put_liftupmax;//リフトマックスを置くか？

public:
	MapIo();
	~MapIo();

	void LoadMapData(int set_stage_num);//マップデータ読込
	void InputTest(GameMainScene* gamemain);//エディタテスト
	void SaveMapData(int set_stage_num);//マップデータ保存
	void Draw() const;
	int GetMapData(int j, int i) { return map_array[j][i]; }

	void SetLiftUpMax();

	void SetPlayerLocal(float set_localx) { p_localx = set_localx; }
	void SetPlayerWorld(float set_worldx) { p_worldx = set_worldx; }

	void SetOriginPosx(float set_origin_posx) { posx = set_origin_posx; }
	void SetLocalPosx(float set_local_posx) { local_posx = set_local_posx; }
	void SetWorldPosx(float set_world_posx) { world_posx = set_world_posx; }

};

