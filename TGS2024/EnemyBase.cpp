#include "EnemyBase.h"

EnemyBase::EnemyBase()
{
	/** サウンドの読み込み */
	// 死亡se
	death_sound = LoadSoundMem("sounds/se/enemy/death.mp3");

	/** 画像・アニメーション用 */
	anim_cnt = 0;
	enemy_img_num = 0;
	lust_death_img_num = 0;

	/** フラグ */
	play_death_sound_flg = false;			// 死亡seはまだ鳴っていない
	gem_drop_flg = false;					// 宝石はドロップしない
	is_delete = false;						// 削除しない

	/** 星エフェクト */
	star_img = LoadGraph("images/Enemy/star.png");
	star_flg = false;
	star_x = 0.0f;
	star_y = 0.0f;
	star_degree = 0.0;						// 画像の角度
	star_radian = 0.0;						// 画像の角度
	star_timer = 0;
	star_count = 0;
	star_is_draw = false;				// 星の描画なし
	star_direction = direction;

	player_world_x = 0.0f;
	player_world_y = 0.0f;
}

EnemyBase::~EnemyBase()
{
	// サウンド削除
	DeleteSoundMem(death_sound);
	// 画像削除
	DeleteGraph(star_img);
}

// 死亡音を1回だけ再生する処理
void EnemyBase::PlayDeathSound()
{
	// 死亡seを鳴らしたことがあるなら処理を抜ける
	if (play_death_sound_flg == true) return;

	if (CheckSoundMem(death_sound) == FALSE)
	{
		// 死亡seの再生
		PlaySoundMem(death_sound, DX_PLAYTYPE_BACK);
		play_death_sound_flg = true;
	}
}

// 星エフェクトの準備
void EnemyBase::StarEffectPreparation()
{
	if (world.x > player_world_x)
	{
		// 左に星が出る
		star_direction = false;
	}
	else
	{
		// 右に星が出る
		star_direction = true;
	}

	// 星画像用変数
	star_degree = 0.0;
	star_radian = 0.0;
	star_x = location.x;
	star_y = location.y - 40;
	star_timer = 0;
	star_count = 0;
	star_is_draw = true;
	star_flg = false;
}

// 星エフェクトの処理
void EnemyBase::StarEffect()
{
	// 星の座標を敵のスクリーン座標にする
	star_x = location.x;
	star_y = location.y - fabs(sinf((float)M_PI * 2.0f / 60.0f * (float)star_count) * 60.0f);
	star_timer++;

	if (star_direction == false)
	{
		// 反時計回り
		if (star_degree > 0.0)
		{
			star_degree -= 4;
		}
		else
		{
			star_degree = 360.0;
		}
	}
	else
	{
		// 時計回り
		if (star_degree < 360.0)
		{
			star_degree += 4;
		}
		else
		{
			star_degree = 0.0;
		}
	}

	// 角度をデグリーからラジアンへ変更
	star_radian = DEGREE_RADIAN(star_degree);

	// 星の画像sin用カウント
	if (star_count < 30)
	{
		star_count++;
	}
	else
	{
		star_count = 0;
	}

	// 星が飛ぶ向き
	if (star_direction == false)
	{
		// 左に飛ぶ
		star_x -= (float)star_timer;
	}
	else
	{
		// 右に飛ぶ
		star_x += (float)star_timer;
	}

	if (star_timer > 30)
	{
		star_is_draw = false;
		star_timer = 0;
		star_count = 0;
		star_degree = 0.0;
		star_radian = 0.0;
	}
}

void EnemyBase::Damage(float damage)
{
	hp -= damage;
}

float EnemyBase::GetHp() const
{
	return hp;
}

float EnemyBase::GetAttack() const
{
	return attack;
}

bool EnemyBase::GetGemDropFlg() const
{
	return gem_drop_flg;
}

bool EnemyBase::GetDeleteFlg() const
{
	return is_delete;
}

void EnemyBase::SetPlayerWorldLocation(World set_world)
{
	player_world_x = set_world.x;
	player_world_y = set_world.y;
}

void EnemyBase::SetStarFlg()
{
	star_flg = true;
}
