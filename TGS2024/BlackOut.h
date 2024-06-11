#pragma once
#include "DxLib.h"

class BlackOut
{
private:
	int black_img;
	float alpha;
	float alpha_fadein;
	bool Fadeout_flg;//真っ暗になったか？
	bool fadein_flg;

public:
	BlackOut();
	~BlackOut();
	void Update();
	void Fadein();
	void Draw() const;
	void Draw_Fadein() const;
	bool GetFadeout() { return Fadeout_flg; }
	bool GetFadein() { return fadein_flg; }
};

