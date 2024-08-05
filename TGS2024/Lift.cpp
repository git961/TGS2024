#include "Lift.h"

Lift::Lift(float set_x,float set_y)
{
	switch_object = new Switch(set_x, set_y);
	lift_img = LoadGraph("images/Stage/Gimmick/Lift.png");
	world.x = set_x;
	world.y = set_y;
	location.x = set_x;
	location.y = set_y;
	move_y = 5.0f;
	limit_y = 200;
	screen_position_x = 0.0f;
	screen_position_y = 0.0f;

	width = 192;
	height = 40;

	canmove_flg = false;
}

Lift::~Lift()
{
}

void Lift::Update(AttackCheck* ac)
{
	

	//もし動けたら
	if (canmove_flg == true)
	{
		//上まで上がる
		if (world.y > limit_y)
		{
			world.y = world.y - move_y;
		}
	}

	if (switch_object != nullptr)
	{
		switch_object->SetLocalPosition(screen_position_x, screen_position_y);
		//つるはしとボタンが当たってるかのチェック
		if (ac->HitCheck(switch_object->GetWorldLocation(), switch_object->GetWidth(), switch_object->GetHeight()) == true)
		{ 
			canmove_flg = true;
		}
		switch_object->Update();
	}
}

void Lift::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1,0, lift_img, TRUE);
	DrawBox((int)location.x - width / 2, (int)location.y - height / 2, (int)location.x + width / 2, (int)location.y + height / 2,0x00ffff,FALSE);
	DrawFormatString((int)location.x, (int)location.y, 0xFFFFFF, "y:%f", world.y);

	if (switch_object != nullptr)
	{
		switch_object->Draw();
	}
}
