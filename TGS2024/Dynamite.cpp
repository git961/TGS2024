#include "Dynamite.h"

Dynamite::Dynamite(World set_xy,int set_direction)
{
	width = 60;
	height = 50;
	location.x = set_xy.x;
	location.y = set_xy.y;
	world.x = set_xy.x;
	world.y = set_xy.y;
	move_x = 3;
	rotation = 0;
	dynamite_img = LoadGraph("images/Player/dynamite.png");
	LoadDivGraph("images/Player/explosion.png", 3, 3, 1, 128,128, explosion_img);

	direction = set_direction;
	dynamite_flg = false;
	damage_flg = false;
	dynamite_death = false;
	explosion_cnt = 0;
	explosion_num = 0;
}

Dynamite::~Dynamite()
{
}

void Dynamite::Update()
{
	if (dynamite_flg == false)
	{
		if (direction == 0) {
			world.x += move_x;
			rotation += 0.3;
		}
		else {
			world.x -= move_x;
			rotation -= 0.3;
		}
	}
	else if (dynamite_flg == true)
	{
		explosion_cnt++;
		switch (explosion_cnt)
		{
		case 0:
			explosion_num = 0;
			break;
		case 5:
			explosion_num = 1;
			break;
		case 10:
			explosion_num = 2;
			width = 150;
			height = 128;
			damage_flg = true;
			break;
		case 11:
			damage_flg = false;
			break;
		case 25:
			dynamite_death = true;
			break;
		default:
			break;
		}
	}


	

}

void Dynamite::Draw() const
{
	DrawBoxAA(world.x - width / 2, world.y - height / 2, world.x + width / 2, world.y + height / 2, 0x00ffff, false);

	if (dynamite_flg == false)
	{
		DrawRotaGraph(location.x, location.y, 1, rotation, dynamite_img, TRUE, direction);
	}
	else
	{
		DrawRotaGraph(location.x, location.y, 1, 0, explosion_img[explosion_num], TRUE, direction);

	}
}
