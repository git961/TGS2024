#include "FallingRock.h"

FallingRock::FallingRock()
{
	rock_img = LoadGraph("images/Animscene/Bigrock.png");
	LoadDivGraph("images/Animscene/rockeffect.png", 4, 4, 1, 1024, 512, rock_effect_img);

	rock_state = 0;

	anim_cnt=0;
	rock_img_num = 0;
	world.x = 350;
	world.y = -500;
	location.x = 350;
	location.y = -500;
	speed = 1;
	angle = 0;
	degree = 0;
	landing_flg = false;
	black_out_flg = false;

	shake_x1 = 5;
	shake_x2 = 10;
	rocks_fall_sound = LoadSoundMem("sounds/se/op/rocks_fall.mp3");
	roll_sound = LoadSoundMem("sounds/se/op/roll.mp3");
	// サウンドの音量設定
	ChangeVolumeSoundMem(255, rocks_fall_sound);
	ChangeVolumeSoundMem(255, roll_sound);

}

FallingRock::~FallingRock()
{
	// サウンド削除
	DeleteSoundMem(rocks_fall_sound);
	DeleteSoundMem(roll_sound);

}

void FallingRock::Update()
{
	//落下

	switch (rock_state)
	{
	case 0:
		if (world.y < 390)
		{
			world.y += 2;
		}
		else
		{
			world.y = 390;
			rock_state = 1;
			landing_flg = true;

		}
	break;
	case 1:
		//岩落ちる音
		if (CheckSoundMem(rocks_fall_sound) == FALSE)
		{
			PlaySoundMem(rocks_fall_sound, DX_PLAYTYPE_BACK);
		}

		//地面に着地したら
		anim_cnt++;
		switch (anim_cnt)
		{
		case 1:
			rock_img_num = 0;
			break;
		case 30:
			rock_img_num = 1;
			degree += 0.5;
			world.x += speed;

			break;
		case 60:
			rock_img_num = 2;
			degree += 0.5;
			world.x += speed;

			break;
		case 90:
			rock_img_num = 3;
			degree += 0.5;
			world.x += speed;

			break;
		case 120:
			rock_state = 2;
			degree += 0.5;

			break;

		default:
			break;
		}
		angle = DEGREE_RADIAN(degree);

		break;
	case 2:
		
		//転がる音
		if (CheckSoundMem(roll_sound) == FALSE)
		{
			PlaySoundMem(roll_sound, DX_PLAYTYPE_BACK);
		}

		landing_flg = false;
		black_out_flg = true;
		//転がる右回り

		if (degree < 360)
		{
			degree += 0.5;
		}
		else
		{
			degree = 0;
		}

		// 画像の角度
		angle = DEGREE_RADIAN(degree);
		// 移動処理
		world.x += speed;

		break;
	}
	




	

}

void FallingRock::Draw() const
{

	DrawRotaGraph((int)location.x, (int)location.y, 1.0, angle, rock_img, TRUE, FALSE);

	if (rock_state == 1)
	{
		DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0, rock_effect_img[rock_img_num], TRUE, FALSE);
	}

	//DrawFormatString(300, 180, 0xffffff, "camerax: %f", location.x);
	//DrawFormatString(300, 200, 0xffffff, "cameray: %f", location.y);

}
