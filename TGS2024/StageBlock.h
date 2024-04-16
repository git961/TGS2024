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

class StageBlock
	:public ObjectBase
{
private:
	blockworld block_world;
	blocklocal block_local;
	int stage_blockdata[map_blockmax_y][map_blockmax_x];
public:
	int direction;

	StageBlock(MapIo *mapio);
	~StageBlock();

	void Update();
	void Draw() const;

	//ブロックのlocationとスクリーンの原点を引いてスクリーン座標上の位置に変換
	void SetBlockLocalPosition(float set_origin_posx, float set_origin_posy)
	{
		//ワールド座標ースクリーン座標の原点してオブジェクトのスクリーン座標を出す計算
		for (int i = 0; i < map_blockmax_y; i++)
		{
			for (int j = 0; j < map_blockmax_x; j++)
			{
				block_local.x[j] = block_world.x[j] - set_origin_posx;
				block_local.y[i] = block_world.y[i] - set_origin_posy;
			}
		}
	};


	bool CheckHitBlock(int i, int j, Vec2 opponent, float opponent_width, float opponent_height);

	//0:当たってない　1:上　2:右 3:左 4:下 を返す
	int GetHitDirection() { return direction; }


};

