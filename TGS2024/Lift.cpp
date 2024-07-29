#include "Lift.h"

Lift::Lift(float set_x,float set_y)
{
	lift_img = LoadGraph("images/Stage/Gimmick/Lift.png");
	world.x = set_x;
	world.y = set_y;
	location.x = set_x;
	location.y = set_y;
	move_y = 5.0f;
	limit_y = 200;

	width = 192;
	height = 40;

	canmove_flg = false;
}

Lift::~Lift()
{
}

void Lift::Update()
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
}

void Lift::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1,0, lift_img, TRUE);
	DrawBox((int)location.x - width / 2, (int)location.y - height / 2, (int)location.x + width / 2, (int)location.y + height / 2,0x00ffff,FALSE);
	DrawFormatString((int)location.x, (int)location.y, 0xFFFFFF, "y:%f", world.y);
}
