#include "StageBlock.h"


StageBlock::StageBlock(MapIo *mapio)
{

	height = BLOCKSIZE;
	width= BLOCKSIZE;

	for (int i = 0; i < map_blockmax_y; i++)
	{
		for (int j = 0; j < map_blockmax_x; j++)
		{
			stage_blockdata[j][i] = mapio->GetMapData(j, i);
			if (stage_blockdata[j][i] != 0)
			{
				block_world.x[j]= j * BLOCKSIZE+BLOCKSIZE/2;
				block_world.y[i]=i * BLOCKSIZE+BLOCKSIZE / 2;
			}
			//stage_blockdata[j][i] = stagearraydata[j][i];

		}
	}

}

StageBlock::~StageBlock()
{
}

void StageBlock::Update()
{
}

void StageBlock::Draw() const
{
}

void StageBlock::CreateBlock()
{
	//for (int i = 0; i < map_blockmax_y; i++)
	//{
	//	for (int j = 0; j < map_blockmax_x; j++)
	//	{
	//		if (stage_blockdata[j][i] != 0)
	//		{

	//		}
	//	}
	//}
}
