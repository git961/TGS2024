#include "StageBlock.h"


StageBlock::StageBlock(int set_block_num,float set_x, float set_y)
{
	height = BLOCKSIZE;
	width= BLOCKSIZE;

	world.x = set_x;
	world.y = set_y;
	location.x = set_x;
	location.y = set_y;
	block_num = set_block_num;

	//if (block_num == 1) {
	//	block_img = LoadGraph("images/Stage/block.png");
	//}
	//else {
	//	block_img = LoadGraph("images/Stage/Goal.png");
	//}


	switch (block_num)
	{
	case 1:
		block_img = LoadGraph("images/Stage/block.png");
		break;
	case 3:
		block_img = LoadGraph("images/Stage/Goal.png");
		break;
	case 4:
		block_img = LoadGraph("images/Stage/rock.png");
		hp = 30;
		shake_cnt = 0;
		shakex = 0;
		shake_flg = false;
		break;
	case 5:
		block_img = LoadGraph("images/Stage/fukuro.png");
		break;
	}

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
	if(block_num==4){
		if (shake_flg == true)
		{
			shake_cnt++;
			switch (shake_cnt)
			{
			case 1:
				shakex = -5;
				break;
			case 3:
				shakex = 5;
				break;
			case 5:
				shake_cnt = 0;
				shake_flg = false;
				break;
			default:
				shakex = 0;
				break;
			}
			world.x += shakex;
		}
	}
		
	
}

void StageBlock::Draw() const
{
	//DrawBox(world.x, world.y, width, world.x + 20, world.y + 20,TRUE);
	//DrawBox(location.x-BLOCK_HALFSIZE, location.y-BLOCK_HALFSIZE, location.x + BLOCK_HALFSIZE, location.y + BLOCK_HALFSIZE,0xffffff,TRUE);
	DrawRotaGraph(location.x, location.y, 1, 0,block_img, TRUE, 0);


	//DrawCircle(box_vertex.upper_leftx, box_vertex.upper_lefty, 2, 0xff00ff, TRUE);
	//DrawCircle(box_vertex.lower_leftx, box_vertex.lower_lefty, 2, 0xff00ff, TRUE);
	//DrawCircleAA(location.x, location.y, 1, 0xff00ff, true);			// 中心座標


}
