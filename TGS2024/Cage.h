#pragma once
#include "ObjectBase.h"

class Cage : public ObjectBase
{
private:
	int cage_img;						// 檻（箱）の画像
	int cage_grate_img;					// 檻の格子の画像

	bool inside_flg;					// プレイヤーが檻の中にいるか？

public:
	Cage(World set_world);
	~Cage();

	void Update(GameMainScene* gamemain)override;	// 更新処理
	void Draw() const override;					// 描画処理
	void HitReaction(ObjectType set_type) override;

	void SetInsideFlg(bool set_flg);

};