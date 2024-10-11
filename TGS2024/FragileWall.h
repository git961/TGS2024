#pragma once
#include "ObjectBase.h"

class FragileWall : public ObjectBase
{
private:
	enum class WallState
	{
		GLOW,
		BREAK
	};

	WallState wall_state;

	int fragile_wall_img[11];				// 脆い壁の画像

	float hp;							// 体力
	int img_num;						// 画像番号
	int anim_cnt;						// アニメーション用カウント
	int anim_wait_time;					// 光るアニメーション開始までの待ち時間
	bool delete_flg;					// 削除するか？

public:
	FragileWall(float set_x, float set_y);
	~FragileWall();

	void Update(GameMainScene* gamemain)override;	// 更新処理
	void Draw() const override;					// 描画処理
	void HitReaction(ObjectBase* character) override;

private:
	void BrokenAnimation();				// 壊れるアニメーション
	void GlowingAnimation();			// つやつや光るアニメーション
	void CheckBroken();					// 壊れたか調べる

public:
	void Damage(float damage);            // 被ダメージ処理
	bool GetDeleteFlg() const { return delete_flg; }
	float GetHp() const { return hp; }

};