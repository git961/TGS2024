#include "Dynamite.h"

Dynamite::Dynamite(World set_xy,int set_direction)
{
	direction = set_direction;

	width = 60;
	height = 50;
	if (direction == false)
	{
		location.x = set_xy.x+20.0f;
		location.y = set_xy.y-15.0f;
		world.x = set_xy.x+20.0f;
		world.y = set_xy.y - 15.0f;
	}
	else {
		location.x = set_xy.x-20;
		location.y = set_xy.y - 15.0f;
		world.x = set_xy.x-20;
		world.y = set_xy.y - 15.0f;
	}
	move_x = 5;
	rotation = 0;
	dynamite_img = LoadGraph("images/Player/dynamite.png");
	LoadDivGraph("images/Player/explosion.png", 3, 3, 1, 128,128, explosion_img);

	dynamite_flg = false;
	damage_flg = false;
	dynamite_death = false;
	move_stop_flg = false;
	explosion_cnt = 0;
	explosion_num = 0;

	attack = 40.0f;
	enemy_x = 0.0f;
	tmp_abs = 0.0f;
	bomb_sound = LoadSoundMem("sounds/se/player/bomb.mp3");
	// サウンドの音量設定
	ChangeVolumeSoundMem(200, bomb_sound);

}

Dynamite::~Dynamite()
{	
	//画像削除
	DeleteGraph(dynamite_img);
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(explosion_img[i]);
	}

	// サウンド削除
	DeleteSoundMem(bomb_sound);
}

void Dynamite::Update(GameMainScene* gamemain)
{
	if (dynamite_flg == false)
	{
		if (direction == 0) {
			world.x += move_x;
			rotation += 0.3f;
		}
		else {
			world.x -= move_x;
			rotation -= 0.3f;
		}
	}
	else if (dynamite_flg == true)
	{
		if (CheckSoundMem(bomb_sound) == FALSE)
		{
			PlaySoundMem(bomb_sound, DX_PLAYTYPE_BACK);
		}

		if (move_stop_flg == false)
		{
			if (direction == 0) {
				world.x += move_x + 3.0f;
			}
			else {
				world.x -= move_x - 3.0f;
			}
		}
		else {
			if (direction == 0) {
				world.x += move_x;
			}
			else {
				world.x -= move_x;
			}
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
			move_stop_flg = true;
			explosion_num = 2;
			width = 300;
			height = 256;
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
	//DrawBoxAA(world.x - width / 2, world.y - height / 2, world.x + width / 2, world.y + height / 2, 0x00ffff, false);

	if (dynamite_flg == false)
	{
		DrawRotaGraph((int)location.x, (int)location.y, 1, rotation, dynamite_img, TRUE, direction);
	}
	else
	{
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, explosion_img[explosion_num], TRUE, direction);

	}
}

void Dynamite::HitReaction(ObjectType set_type)
{
}

// ダメージの計算
void Dynamite::DamageCalculation()
{
	// 敵との距離
	tmp_abs = fabsf(world.x - enemy_x);

	if (tmp_abs < 50)
	{
		attack = 40;
	}
	else if (tmp_abs < 100)
	{
		attack = 40;
	}
	else if (tmp_abs < 200)
	{
		attack = 40;
	}
}
