#pragma once
#include "ObjectBase.h"
#include "MapIo.h"
#include "Define.h"

class MapIo;
enum class ObjectType;

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



class StageBlock
	:public CharacterBase
{
private:
	Blockvertex block_vertex;

	int stage_blockdata[map_blockmax_y][map_blockmax_x];
	int block_num;//1:ステージブロック　3:Goal
	int block_img;

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

	bool gem_drop;

	bool delete_flg;

protected:
	ObjectType object_type;

public:
	int direction;

	StageBlock(int set_block_num,float set_x,float set_y);
	~StageBlock();
	void Finalize();

	void Update(GameMainScene* gamemain) override;
	void Draw() const override;
	void HitReaction(ObjectBase* character) override;
	void DrawKanban() const;


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

