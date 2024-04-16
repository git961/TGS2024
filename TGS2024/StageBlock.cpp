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

bool StageBlock::CheckHitBlock(int i, int j, Vec2 opponent, float opponent_width, float opponent_height)
{
	if (stage_blockdata[j][i] == 0)
	{
		return false;
	}
	
		float my_center_x = width / 2;
		float my_center_y = height / 2;
		//x座標の相手と自分の距離を絶対値で測る
		distance_x = fabs(block_world.x[j] - opponent.x);
		//2つの幅/2を足す
		two_widths = my_center_x + opponent_width / 2;


		//y座標の相手と自分の距離を絶対値で測る
		distance_y = fabs(block_world.y[i] - opponent.y);
		//2つの高さ/2を足す
		two_heights = my_center_y + opponent_height / 2;

		//もし距離の絶対値より幅が大きかったらヒット
		if (distance_x < two_widths && distance_y < two_heights)
		{
			return true;
		}
		else
		{
			return false;
		}

}
