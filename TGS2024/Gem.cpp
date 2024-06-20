#include "Gem.h"

Gem::Gem(World set_world, int set_score)
{
	location.x = set_world.x;
	location.y = set_world.y;

	world.x = set_world.x;
	world.y = set_world.y;

	width = 32.0f;
	height = 32.0f;

	// 画像の読み込み
	LoadDivGraph("images/Gem/Gem.png", 5, 5, 1, 32, 32,gem_img);
	LoadDivGraph("images/Gem/effect.png", 4, 4, 1, 32, 32, effect_img);

	// サウンド読込
	get_gem_sound = LoadSoundMem("sounds/se/gem/get.mp3");
	drop_sound = LoadSoundMem("sounds/se/gem/drop.mp3");
	play_drop_sound = true;
	play_get_sound = true;

	gem_score = set_score;
	count = 0;
	move_x_timer = 0;
	size = 0.0;

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

Gem::~Gem()
{
	// 画像削除
	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(gem_img[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(effect_img[i]);
	}

	// サウンド削除
	DeleteSoundMem(get_gem_sound);
	DeleteSoundMem(drop_sound);

}

void Gem::Update(GameMainScene* gamemain)
{
	if (play_drop_sound == true)
	{
		if (CheckSoundMem(drop_sound) == FALSE)
		{
			// ドロップse
			PlaySoundMem(drop_sound, DX_PLAYTYPE_BACK);
			play_drop_sound = false;
		}
	}

	// 宝石が上下に揺れる
	GemSway();

	// 生成時のx座標の動き
	MoveX();

	// 画面外に出ないように
	ControlPosition();

	// 生成時の宝石の大きさ変更処理
	ChangeSize();

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

void Gem::Draw() const
{
	//DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0xffffff, true);				// 当たり判定のボックス
	//DrawFormatString(location.x, 550, 0xffffff, "effect_num: %d", effect_num);

	if (draw_effect == false)
	{
		// 宝石画像
		DrawRotaGraph((int)location.x, (int)location.y, size, 0.0, gem_img[anim_num], TRUE, direction);
	}
	else
	{
		// ゲットエフェクト画像
		DrawRotaGraph((int)location.x, (int)location.y, size, 0.0, effect_img[effect_num], TRUE, direction);
	}
}

// 宝石のアニメーション
void Gem::GemAnim()
{
	anim_cnt++;
	anim_num = anim_cnt / 10;
	if (anim_cnt >=49) {
		anim_cnt = 0;
	}
}

// 生成時の宝石の大きさ変更処理
void Gem::ChangeSize()
{
	if (from_rolling_enemy == true)
	{
		// だんだんサイズが大きくなる
		if (size < 1.3)
		{
			size += 0.1;
		}
		else
		{
			size = 1.3;
		}
	}
	else
	{
		// だんだんサイズが大きくなる
		if (size < 1.0)
		{
			size += 0.1;
		}
		else
		{
			size = 1.0;
		}
	}
}

// 生成時のx座標の動き
void Gem::MoveX()
{
	if (just_generated == true)
	{
		// 敵の死亡位置がプレイヤーよりも右
		if (world.x > player_x)
		{
			// 宝石が右に移動
			world.x += 15.0f;
		}
		else
		{
			// 宝石が左に移動
			world.x -= 15.0f;

		}
		just_generated = false;
	}
}

// 画面外にでないように
void Gem::ControlPosition()
{
	if (world.x + width / 2 > FIELD_WIDTH)
	{
		world.x -= width / 2;
	}
	else if (world.x - width / 2 < 0)
	{
		world.x += width / 2;
	}
}

// 宝石が上下に揺れる処理
void Gem::GemSway()
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

// 宝石取得seを鳴らす処理
void Gem::PlayGetSound()
{
	if (play_get_sound == true && CheckSoundMem(get_gem_sound) == FALSE)
	{
		// ゲットse
		PlaySoundMem(get_gem_sound, DX_PLAYTYPE_BACK);
		play_get_sound = false;
	}
}