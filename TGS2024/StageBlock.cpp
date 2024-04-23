#include "StageBlock.h"


StageBlock::StageBlock(float set_x, float set_y)
{
	height = BLOCKSIZE;
	width= BLOCKSIZE;

	world.x = set_x;
	world.y = set_y;
	location.x = set_x;
	location.y = set_y;
	/*
	for (int i = 0; i < map_blockmax_y; i++)
	{
		for (int j = 0; j < map_blockmax_x; j++)
		{

			//stage_blockdata[i][j] = mapio->GetMapData(i, j);
			//if (stage_blockdata[i][j] != 0)
			//{
			//	block_world.x[j]= j * BLOCKSIZE+BLOCKSIZE/2;
			//	block_world.y[i]=i * BLOCKSIZE+BLOCKSIZE / 2;

			//	////右下のx座標＝中心ｘ＋ボックスの半分X
				//block_vertex.lower_rightx[j] = block_world.x[j] + BLOCKSIZE / 2;
				//block_vertex.lower_righty[i] = block_world.y[i] + BLOCKSIZE / 2;
				//////左上の座標をセット
				//block_vertex.upper_leftx[j] = block_world.x[j] - BLOCKSIZE / 2;
				//block_vertex.upper_lefty[i] = block_world.y[i] - BLOCKSIZE / 2;

			//}
			//stage_blockdata[j][i] = stagearraydata[j][i];

		}
	}*/
	SetVertex();
}

StageBlock::~StageBlock()
{
}

void StageBlock::Update()
{
}

void StageBlock::Draw() const
{
	//DrawBox(world.x, world.y, width, world.x + 20, world.y + 20,TRUE);
	DrawBox(location.x-BLOCK_HALFSIZE, location.y-BLOCK_HALFSIZE, location.x + BLOCK_HALFSIZE, location.y + BLOCK_HALFSIZE,0xffffff,TRUE);


}
