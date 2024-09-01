#include "Lift.h"
/*
Lift::Lift(float set_x,float set_y)
{
	switch_object = new Switch(set_x, set_y);
	lift_img = LoadGraph("images/Stage/Gimmick/Lift.png");
	world.x = set_x;
	world.y = set_y;
	location.x = set_x;
	location.y = set_y;
	move_y = 5.0f;
	
	up_max_y = 200;
	down_max_y = 600.0f;
	screen_position_x = 0.0f;
	screen_position_y = 0.0f;

	width = 192;
	height = 40;

	canmove_flg = false;
	down_flg = false;
	anim_start_flg = false;
	anim_cnt = 0;
	img_num = 0;
}
*/
Lift::~Lift()
{
	delete switch_object;
	DeleteGraph(lift_img);
}

void Lift::Update(AttackCheck* ac,Player* player)
{
	
	

	//もし動ける状態で上に上がれたら
	if (canmove_flg == true && down_flg == false)
	{
		//上のMaxYまで上がる
		if (world.y >= up_max_y)
		{
			world.y = world.y - move_y;
			if (switch_object != nullptr)
			{
				switch_object->SetY(world.y);
			}
		}
		else
		{
			//上まで上がり切ったら動きを止めて下に下がれるようにする
			down_flg = true;
			canmove_flg = false;
			switch_object->SetImgNum(0);
		}

	}
	//もし動けて、下に下がれたら
	if (canmove_flg == true && down_flg == true)
	{

		//下まで下がる
		if (world.y < down_max_y)
		{
			world.y = world.y + move_y;
			if (switch_object != nullptr)
			{
				switch_object->SetY(world.y);
			}
		}
		else
		{
			//下まで下がり切ったら、動きを止めて下に下がれなくする
			down_flg = false;
			canmove_flg = false;
			switch_object->SetImgNum(0);
		}

	}

	

	if (switch_object != nullptr)
	{
		switch_object->SetLocalPosition(screen_position_x, screen_position_y);
		//つるはしとボタンが当たってるかのチェック
		if (ac->GetAttackFlg()==true && switch_object->HitCheck(ac->GetWorldLocation(), ac->GetWidth(), ac->GetHeight()) == true)
		{ 
			anim_start_flg = true;
		}
		switch_object->Update();
	}


	UpAnim();
	DownAnim();

}

void Lift::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1,0, lift_img, TRUE);
	DrawBox((int)location.x - width / 2, (int)location.y - height / 2, (int)location.x + width / 2, (int)location.y + height / 2,0x00ffff,FALSE);
	//DrawFormatString((int)location.x, (int)location.y-60, 0xFFFFFF, "y:%f", world.y);
	DrawFormatString((int)location.x, (int)location.y-60, 0xFFFFFF, "count:%d",anim_cnt);
	DrawFormatString((int)location.x, (int)location.y, 0xFFFFFF, "Canmove:%d,down_flg:%d", canmove_flg,down_flg);

	if (switch_object != nullptr)
	{
		switch_object->Draw();
	}
}

void Lift::Initialize(float set_x, float set_y)
{
	//switch_object = new Switch(set_x, set_y);
	lift_img = LoadGraph("images/Stage/Gimmick/Lift.png");
	world.x = set_x;
	world.y = set_y;
	location.x = set_x;
	location.y = set_y;
	move_y = 5.0f;

	up_max_y = 200;
	down_max_y = 600.0f;
	screen_position_x = 0.0f;
	screen_position_y = 0.0f;

	width = 192;
	height = 40;

	canmove_flg = false;
	down_flg = false;
	anim_start_flg = false;
	anim_cnt = 0;
	img_num = 0;

}

void Lift::UpAnim()
{
	//スイッチ上がるアニメーション
	if (anim_start_flg == true && down_flg==false)
	{
		anim_cnt++;
		switch (anim_cnt)
		{
		case 10:
			switch_object->SetImgNum(1);
			break;
		case 20:
			switch_object->SetImgNum(2);
			break;
		case 25:
			canmove_flg = true;
			anim_start_flg = false;
			anim_cnt = 0;
			break;
		default:
			break;
		}
	}
}

void Lift::DownAnim()
{
	//スイッチ下がるアニメーション
	if (anim_start_flg == true && down_flg == true)
	{
		anim_cnt++;
		switch (anim_cnt)
		{
		case 10:
			switch_object->SetImgNum(3);
			break;
		case 20:
			switch_object->SetImgNum(4);
			break;
		case 25:
			canmove_flg = true;
			anim_start_flg = false;
			anim_cnt = 0;
			break;
		default:
			break;
		}
	}

}

