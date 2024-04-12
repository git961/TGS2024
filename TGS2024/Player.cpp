#include "Player.h"
#define DEBUG
int color=0;
int a;
Player::Player()
{
	width = 30;
	height = 30;
	x = 200;
	y = 600;
	attacking = false;
	atk_cnt_timer = 0;
}

Player::~Player()
{
}

void Player::Update(GameMainScene* gamemain)
{

	//
	input.InputUpdate();


	//プレイヤー移動
	//右移動
	a = input.LongPressBtn(XINPUT_BUTTON_DPAD_RIGHT);

	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_RIGHT) == TRUE) {
		x+=3;
		direction = 0;
	}
	//左移動
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_LEFT) == TRUE) {
		x-=3;
		direction = 1;
	}

	//Yおしたら攻撃
	if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
	{
		attacking = true;
	}
	//何秒か経ったら攻撃中フラグを戻す？
	if (attacking == true)
	{
		if (atk_cnt_timer++ > 5)
		{
			atk_cnt_timer = 0;
			attacking = false;
		}
	}
}

void Player::Draw() const
{
	DrawBoxAA(x - width/2, y - height/2, x + width / 2, y + height / 2, 0x00ffff,true);
	DrawCircleAA(x, y, 1, 0xff00ff, true);

#ifdef DEBUG


	////// 画面に XINPUT_STATE の中身を描画
	color = GetColor(255, 255, 255);
	for (int i = 0; i < 16; i++)
	{
		DrawFormatString(64 + i % 8 * 64, 64 + i / 8 * 16, color,
			"%2d:%d", i, input.getkey.Buttons[i]);
	}
	DrawFormatString(100, 100, 0xffffff, "Right:%d", a);
	DrawFormatString(100, 120, 0xffffff, "btnnum: % d", input.Btnnum);
#endif // DEBUG
}