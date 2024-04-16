#pragma once
#include "ObjectBase.h"
#include "MapIo.h"
#include "Define.h"

class MapIo;

struct blockworld
{
	int x[map_blockmax_x];
	int y[map_blockmax_y];
};

class StageBlock
	:public ObjectBase
{
private:
	blockworld block_world;
	int stage_blockdata[map_blockmax_y][map_blockmax_x];

public:
	StageBlock(MapIo *mapio);
	~StageBlock();

	void Update();
	void Draw() const;

	void CreateBlock();


};

