#pragma once
#include "ObjectBase.h"
#include "MapIo.h"
#include "Define.h"

class MapIo;

struct blockworld
{
	int x[map_blockmax_x*map_blockmax_y];
	int y[map_blockmax_x * map_blockmax_y];
};
struct blocklocal
{
	int x[map_blockmax_x*map_blockmax_y];
	int y[map_blockmax_x * map_blockmax_y];
};

struct Blockvertex
{
	//右下
	float lower_rightx[map_blockmax_x * map_blockmax_y];
	float lower_righty[map_blockmax_x * map_blockmax_y];

	//左上
	float upper_leftx[map_blockmax_x * map_blockmax_y];
	float upper_lefty[map_blockmax_x * map_blockmax_y];
};

struct block_effect
{
	float x;
	float y;
	double degree;      // 画像の角度（デグリー）
	double radian;      // 画像の角度（ラジアン）
	int timer;          // 描画時間
	int count;          // 三角関数用
	bool is_draw;       // 描画するか？
};

class StageBlock
	:public CharacterBase
{
private:
	Blockvertex block_vertex;
	int stage_blockdata[map_blockmax_y][map_blockmax_x];
	int block_num;//1:ステージブロック　3:Goal
	int block_img;
	int rock_img[7];
	int rock_num;

	int fragment_img[4];

	float shakex;
	int shake_cnt;
	bool shake_flg;

	float helx, hely;//helmetのｘｙ
	float frames;
	bool can_jump;
	float radperframe;
	float angle;
	bool is_up;
	int delete_cnt;//消すまでのカウント

	bool effect_flg;
	block_effect fragment[4]={0};
	float v0[4];                      // 斜方投射時の初速度
	float gravity;                    // 重力
	float start_x;
	float start_y;
	float sum_t;
	float t;
	float mvx[4];
	float mvy[4];
	bool gem_drop;

	bool delete_flg;

public:
	int direction;

	StageBlock(int set_block_num,float set_x,float set_y);
	~StageBlock();

	void Update();
	void Draw() const;
	void DrawKanban() const;
	void FragmentEffect();                      // 石の破片エフェクトの処理
	void FragmentSet();

	int GetBlockNum() { return block_num; }

	void SetDamage(float damage) { hp = hp - damage; }
	void SetShakeFlg(bool set_flg) { shake_flg=set_flg; }
	float GetHp() { return hp; }
	void SetUp(bool set_flg) { is_up = set_flg; }
	bool GetDeleteFlg() { return delete_flg; }

	//ブロックのlocationとスクリーンの原点を引いてスクリーン座標上の位置に変換
	//void SetBlockLocalPosition(float set_origin_posx, float set_origin_posy)
	//{
	//	//ワールド座標ースクリーン座標の原点してオブジェクトのスクリーン座標を出す計算
	//	for (int i = 0; i < map_blockmax_y; i++)
	//	{
	//		for (int j = 0; j < map_blockmax_x; j++)
	//		{
	//			location.x[j] = block_world.x[j] - set_origin_posx;
	//			block_local.y[i] = block_world.y[i] - set_origin_posy;
	//		}
	//	}
	//};


};

