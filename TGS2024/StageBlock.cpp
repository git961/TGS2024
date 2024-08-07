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
		//block_img = LoadGraph("images/Stage/rock.png");
		LoadDivGraph("images/Stage/rock.png", 7, 7, 1, 64, 64, rock_img);
		hp = 30;
		shake_cnt = 0;
		shakex = 0;
		shake_flg = false;
		rock_num = 0;
		delete_flg = false;
		delete_cnt = 0;

		LoadDivGraph("images/Stage/fragment.png", 4, 4, 1, 64, 64, fragment_img);

		for (int i = 0; i < 4; i++)
		{
			fragment[i].x = 0.0f;
			fragment[i].y = 0.0f;
			fragment[i].timer = 0;
			fragment[i].count = 0;
			fragment[i].is_draw = false;

			// 初速度の設定
			//v0[i] = rand() % 5 + 1;
			v0[i] = 0.0f;

			// 発射角度の設定
			//fragment[i].degree = rand() % 90;
			fragment[i].degree = 0.0;

			if (i < 2)
			{
				fragment[i].degree += 270;
			}

			fragment[i].radian = (double)DEGREE_RADIAN(fragment[i].degree);

			mvx[i] = 0.0f;
			mvy[i] = 0.0f;
		}

		gravity = 980.0f;
		start_x = 0.0f;
		start_y = 0.0f;
		sum_t = 0.0167f;
		t = 0.0167f;

		gem_drop = false;
		effect_flg = false;

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
	// box_vertexの値を更新し続ける
	SetVertex();

	if(block_num==4){
		if (shake_flg == true)
		{
			shake_cnt++;
			switch (shake_cnt)
			{
			case 1:
				effect_flg = true;
				FragmentSet();
				shakex = -5;
				if (hp > 0) {
					rock_num++;
				}
				break;
			case 3:
				shakex = 5;
				break;
			case 10:
				shake_cnt = 0;

				shake_flg = false;
				break;
			default:
				shakex = 0;
				break;
			}
			world.x += shakex;

		}

		if (effect_flg == true)
		{
			FragmentEffect();
		}

		if (hp <= 0) {

			switch (delete_cnt)
			{
			case 0:
				rock_num++;
				break;
			case 3:
				rock_num++;
				break;
			case 6:
				rock_num++;
				break;
			case 9:
				rock_num++;
				break;
			case 15:
				delete_flg = true;
				break;
			}
			delete_cnt++;
		}
	}

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
	
	if (block_num == 4)
	{
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, rock_img[rock_num], TRUE, 0);
		if (shake_flg == true)
		{
			for (int i = 0; i < 4; i++)
			{
				// 破片描画
				DrawRotaGraph((int)fragment[i].x, (int)fragment[i].y, 1.0, 0.0, fragment_img[i], TRUE, direction);
			}
		}
	}

	//DrawCircle(box_vertex.upper_leftx, box_vertex.upper_lefty, 2, 0xff00ff, TRUE);
	//DrawCircle(box_vertex.lower_leftx, box_vertex.lower_lefty, 2, 0xff00ff, TRUE);
	//DrawCircle(location.x, location.y, 2, 0xffffff, true);			// 中心座標
	//DrawCircle(location.x, location.y - height / 2, 2, 0xffffff, true);			// 中心座標
	if (block_num == 1)
	{
		//DrawFormatString(location.x, location.y - 60, 0xffffff, "%.0f", location.y - height / 2);
		//DrawBox((int)location.x - width / 2, (int)location.y - height / 2, (int)location.x + width / 2, (int)location.y + height / 2, 0x00ffff, FALSE);
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


// 石の破片エフェクトの処理
void StageBlock::FragmentEffect()
{
	for (int i = 0; i < 4; i++)
	{
		if (fragment[i].is_draw == false)
		{
			srand((unsigned int)time(NULL));			// 現在時刻の情報で初期化
			for (int i = 0; i < 4; i++)
			{
				// 初速度の設定
				//v0[i] = 300.0f;
				v0[i] = rand() % 200 + 300;

				// 発射角度の設定
				fragment[i].degree = rand() % 45 + 45;

				if (i < 2)
				{
					fragment[i].degree += 45;
				}

				fragment[i].radian = (double)DEGREE_RADIAN(fragment[i].degree);
			}

			fragment[i].x = location.x;
			fragment[i].y = location.y - height / 2;				// 画像の中心


		}

		start_x = location.x;
		start_y = location.y - height / 2;				// 画像の中心

		if (fragment[i].y < 608.f)
		{
			// 地面についていない間は値の計算を行う
			mvx[i] = v0[i] * cosf((float)fragment[i].radian) * sum_t;
			mvy[i] = -v0[i] * sinf((float)fragment[i].radian) * sum_t + (gravity * sum_t * sum_t) / 2;

			fragment[i].y = start_y + mvy[i];
		}
		else
		{
			fragment[i].y = 608.0f;

		}

		fragment[i].x = start_x + mvx[i];

		sum_t += t;

		if (fragment[i].is_draw == false)
		{
			fragment[i].is_draw = true;
		}
	}


	if (fragment[0].y==608.0f&& fragment[1].y == 608.0f&& fragment[2].y == 608.0f&& fragment[3].y == 608.0f)
	{
		effect_flg = false;
		if (hp < 0)
		{
			// 宝石を落とす
			//gem_drop = true;
		}
	}
}

void StageBlock::FragmentSet()
{
	for (int i = 0; i < 4; i++)
	{
		fragment[i].x = 0.0f;
		fragment[i].y = 0.0f;
		fragment[i].timer = 0;
		fragment[i].count = 0;
		fragment[i].is_draw = false;

		// 初速度の設定
		//v0[i] = rand() % 5 + 1;
		v0[i] = 0.0f;

		// 発射角度の設定
		//fragment[i].degree = rand() % 90;
		fragment[i].degree = 0.0;

		if (i < 2)
		{
			fragment[i].degree += 270;
		}

		fragment[i].radian = (double)DEGREE_RADIAN(fragment[i].degree);

		mvx[i] = 0.0f;
		mvy[i] = 0.0f;
	}
	gravity = 980.0f;
	start_x = 0.0f;
	start_y = 0.0f;
	sum_t = 0.0167f;
	t = 0.0167f;
}
