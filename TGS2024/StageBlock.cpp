#include "StageBlock.h"


void StageBlock::Finalize()
{
	DeleteGraph(block_img);
}



StageBlock::StageBlock(int set_block_num,float set_x, float set_y)
{
	height = BLOCKSIZE;
	width= BLOCKSIZE;

	world.x = set_x;
	world.y = set_y;
	location.x = set_x;
	location.y = set_y;
	block_num = set_block_num;
	angle = 0;
	block_img = 0;
	can_jump = true;
	delete_cnt = 0;
	delete_flg = false;
	direction = false;
	effect_flg = false;

	switch (block_num)
	{
	case 1:
		block_img = LoadGraph("images/Stage/block.png");
		break;
	case 3:
		//block_img = LoadGraph("images/Stage/Goal.png");
		break;
	case 4:
		break;
	case 5:
		block_img = LoadGraph("images/Stage/fukuro.png");
		break;
	case 6:
		block_img = LoadGraph("images/Stage/kanban1.png");
		break;
	case 7:
		block_img = LoadGraph("images/UI/helmet.png");
		angle = 0;
		is_up = false;
		hely = location.y;
		helx = location.x;
		frames = 0;
		radperframe = 2.0f * (float)M_PI / 40.0f;
		can_jump = true;
		delete_flg = false;
		delete_cnt=0;
		break;
	case 10:
		block_img = LoadGraph("images/Stage/kanban2.png");
		break;
	case 11:
		block_img = LoadGraph("images/Stage/kanban3.png");
		break;
	}

	SetVertex();
}

StageBlock::~StageBlock()
{
	DeleteGraph(block_img);
}

void StageBlock::Update()
{
	// box_vertexの値を更新し続ける
	SetVertex();

	if (is_up==true)
	{
		if (can_jump == true)
		{
			//hely -= 10;
			//angle += 0.3;
			world.x = helx;
			helx += 2;
			hely =- 200.0f * (float)sin(radperframe * frames) + 608.0f;
			frames += 1;
			if (sin(radperframe * frames)>=0.9)
			{
				can_jump = false;
			}
		}
		else
		{

			if (hely <= 543)
			{
				hely += 3;
				world.x=2026;
			}
			else {
				if (delete_cnt++ > 30)
				{
					delete_flg = true;
				}
			}
		}

	}
}

void StageBlock::Draw() const
{
	//DrawBox(world.x, world.y, width, world.x + 20, world.y + 20,TRUE);
	//DrawBox(location.x-BLOCK_HALFSIZE, location.y-BLOCK_HALFSIZE, location.x + BLOCK_HALFSIZE, location.y + BLOCK_HALFSIZE,0xffffff,TRUE);

	if (block_num == 7)
	{
		DrawRotaGraph((int)location.x, (int)hely + 10, 1, angle, block_img, TRUE, 0);
	}
	else if (block_num != 6&& block_num != 10 && block_num != 11&&block_num!=4&&block_num!=3)
	{
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, block_img, TRUE, 0);
	}
	
	//DrawCircle(box_vertex.upper_leftx, box_vertex.upper_lefty, 2, 0xff00ff, TRUE);
	//DrawCircle(box_vertex.lower_leftx, box_vertex.lower_lefty, 2, 0xff00ff, TRUE);
	//DrawCircle(location.x, location.y, 2, 0xffffff, true);			// 中心座標
	//DrawCircle(location.x, location.y - height / 2, 2, 0xffffff, true);			// 中心座標
	if (block_num == 1)
	{
		//DrawFormatString(location.x, location.y - 60, 0xffffff, "%.0f", location.y - height / 2);
	DrawBox((int)location.x - width / 2, (int)location.y - height / 2, (int)location.x + width / 2, (int)location.y + height / 2, 0x00ffff, FALSE);
	//DrawCircleAA(location.x, location.y, 1, 0xff00ff, true);			// 中心座標
	
	//DrawBox((int)box_vertex.right_x, (int)box_vertex.upper_y, (int)box_vertex.left_x, (int)box_vertex.lower_y, 0x00ffff, FALSE);

	}
}

void StageBlock::DrawKanban() const
{
	if (block_num == 6||block_num==10||block_num==11)
	{
		DrawRotaGraph((int)location.x, (int)location.y - 60, 1, 0, block_img, TRUE, 0);
	}
}

