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
}

EnemyBase::~EnemyBase()
{
	// サウンド削除
	DeleteSoundMem(death_sound);
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
