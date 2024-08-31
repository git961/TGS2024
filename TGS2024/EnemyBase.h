#pragma once
#include "CharacterBase.h"

class EnemyBase : public CharacterBase
{
protected:
	int death_sound;				// 死亡se

	int anim_cnt;					// アニメーション用カウント
	int enemy_img_num;				// 表示する画像の番号
	int lust_death_img_num;			// 死亡画像の最後の画像番号

	bool play_death_sound_flg;		// 死亡音が鳴ったか？
	bool gem_drop_flg;				// 宝石をドロップするか？
	bool is_delete;					// 自身を削除するか？

public:
	EnemyBase();
	~EnemyBase();

protected:
	//virtual void Update() = 0;
	//virtual void Draw() const = 0;

	//virtual void Move() = 0;
	//virtual void Death() = 0;
	//virtual void DeathAnimation() = 0;

	void PlayDeathSound();					// 死亡音を1回だけ再生する処理

public:
	void Damage(float damage);

	float GetHp() const;
	float GetAttack() const;
	bool GetGemDropFlg() const;
	bool GetDeleteFlg() const;
};