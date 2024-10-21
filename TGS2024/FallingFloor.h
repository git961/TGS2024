#pragma once
#include "ObjectBase.h"

class FallingFloor : public ObjectBase
{
private:
	int falling_floor_img;				// 落ちる床の画像

	int img_num;						// アニメーション用画像番号
	int anim_cnt;						// アニメション用カウント
	float falling_speed;				// 落下速度
	bool touched_magma;					// マグマに触れたか？
	bool falling_flg;					// 落下するか？

	int falling_se;						// 落下se
	int volume;							// se音量

public:
	FallingFloor(float set_x, float set_y);
	~FallingFloor();

	void Update();			// 更新処理
	void Draw() const;		// 描画処理

	bool GetTouchedMagma() const;
	void StopFalling();					// 床の落下を止める

	bool GetFallingFlg() const;
	void StartFalling();				// 落下を開始する
	void SetY(float set_y) { world.y = set_y; }
private:
	void CheckPlaySound();				// サウンドを再生するか調べる
};

