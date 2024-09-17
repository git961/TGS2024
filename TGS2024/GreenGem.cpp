#include "GreenGem.h"

GreenGem::GreenGem(float set_x, float set_y, int set_score)
{
	world.x = set_x;
	world.y = set_y;
	location.x = set_x;
	location.y = set_y;

	gem_img[0] = LoadGraph("images/Gem/GreenGem.png");
	LoadDivGraph("images/Gem/effect.png", 4, 4, 1, 32, 32, effect_img);
	size = 1.0f;
	width = 50.0f;
	height = 50.0f;

	// サウンド読込
	get_gem_sound = LoadSoundMem("sounds/se/gem/get.mp3");
	drop_sound = LoadSoundMem("sounds/se/gem/drop.mp3");
	play_drop_sound = true;
	play_get_sound = true;

	gem_score = set_score;
	count = 0;
	move_x_timer = 0;
	size = 1.0f;

	player_x = 0.0f;
	player_y = 0.0f;

	just_generated = true;
	from_rolling_enemy = false;
	is_delete = false;

	anim_cnt = 0;
	anim_num = 0;
	effect_num = 0;
	effect_anim_cnt = 0;
	draw_effect = false;			// エフェクトは表示しない

	// サウンドの音量設定
	ChangeVolumeSoundMem(255, get_gem_sound);
	ChangeVolumeSoundMem(255, drop_sound);

}

GreenGem::~GreenGem()
{
}

void GreenGem::Update(GameMainScene* gamemain)
{

	// 宝石が上下に揺れる
	GemSway();

	if (play_get_sound == false)
	{
		// seが鳴ったらエフェクトのアニメーション開始
		if (draw_effect == false)
		{
			draw_effect = true;
		}

		if (effect_anim_cnt < 40)
		{
			effect_anim_cnt++;

			if (effect_num < 3)
			{
				// 10fで画像切り替え
				effect_num = effect_anim_cnt / 10;
			}
		}
		else
		{
			if (CheckSoundMem(get_gem_sound) == FALSE)
			{
				// エフェクトのアニメーションが終わったら削除
				is_delete = true;
			}
		}
	}

	// 宝石のアニメーション
	GemAnim();
}

void GreenGem::Draw() const
{

	if (draw_effect == false)
	{
		// 宝石画像
		DrawRotaGraph((int)location.x, (int)location.y, size, 0.0, gem_img[0], TRUE, 0);
	}
	else
	{
		// ゲットエフェクト画像
		DrawRotaGraph((int)location.x, (int)location.y, size, 0.0, effect_img[effect_num], TRUE, direction);
	}
}

void GreenGem::PlayGetSound()
{
	if (play_get_sound == true && CheckSoundMem(get_gem_sound) == FALSE)
	{
		// ゲットse
		PlaySoundMem(get_gem_sound, DX_PLAYTYPE_BACK);
		play_get_sound = false;
	}
}

// 宝石のアニメーション
void GreenGem::GemAnim()
{
	anim_cnt++;
	anim_num = anim_cnt / 10;
	if (anim_cnt >= 49) {
		anim_cnt = 0;
	}
}


// 宝石が上下に揺れる処理
void GreenGem::GemSway()
{
	// sin用
	if (count < 60)
	{
		count++;
	}
	else
	{
		count = 0;
	}

	world.y = world.y - sinf((float)M_PI * 2.0f / 60.0f * (float)count) * 0.5f;
}