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
}

Lift::~Lift()
{
}

void Lift::Update()
{
	if (world.y > limit_y)
	{
		world.y = world.y - move_y;
	}
	else {
		world.y = 200;
	}
}

void Lift::Draw() const
{
	DrawFormatString((int)location.x, (int)location.y, 0xFFFFFF, "y:%f", world.y);
	DrawGraph((int)location.x, (int)location.y, lift_img, TRUE);
}
