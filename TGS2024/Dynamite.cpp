#include "Dynamite.h"

Dynamite::Dynamite(World set_xy,int set_direction)
{
	width = 60;
	height = 50;
	location.x = set_xy.x;
	location.y = set_xy.y+20;
	world.x = set_xy.x;
	world.y = set_xy.y+20;
	move_x = 5;
	rotation = 0;
	dynamite_img = LoadGraph("images/Player/dynamite.png");
	LoadDivGraph("images/Player/explosion.png", 3, 3, 1, 128,128, explosion_img);

	direction = set_direction;
	dynamite_flg = false;
	damage_flg = false;
	dynamite_death = false;
	explosion_cnt = 0;
	explosion_num = 0;

	attack = 30;
	enemy_x = 0.0f;
	tmp_abs = 0.0f;

	tuto_anim_dynaflg = false;
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
		if (direction == 0) {
			world.x += move_x+3;
		}
		else {
			world.x -= move_x;
		}
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
			width = 200;
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

void Dynamite::TutoUpdate()
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
		if (direction == 0) {
			world.x += move_x + 3;
		}
		else {
			world.x -= move_x;
		}
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
			width = 200;
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

// ダメージの計算
void Dynamite::DamageCalculation()
{
	// 敵との距離
	tmp_abs = fabsf(world.x - enemy_x);

	if (tmp_abs < 35)
	{
		attack = 30;
	}
	else if (tmp_abs < 100)
	{
		attack = 20;
	}
	else if (tmp_abs < 200)
	{
		attack = 10;
	}
}
