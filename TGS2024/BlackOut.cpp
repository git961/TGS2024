#include "BlackOut.h"

BlackOut::BlackOut()
{
	alpha = 0;
	alpha_fadein = 255;
	Fadeout_flg = false;
	fadein_flg = false;
	black_img= LoadGraph("images/Animscene/blackimg.png", TRUE);
}

BlackOut::~BlackOut()
{
}

void BlackOut::Update()
{
	if (alpha > 255) {
		Fadeout_flg = true;
	}

	alpha += 5;
}

void BlackOut::Fadein()
{
	alpha_fadein -= 5;
	if (alpha_fadein < 0) {
		fadein_flg=true;
	}
}

void BlackOut::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(0, 0, black_img, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void BlackOut::Draw_Fadein() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_fadein);
	DrawGraph(0, 0, black_img, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
