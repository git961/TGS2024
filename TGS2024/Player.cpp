#include "Player.h"

Player::Player()
{
	width = 30;
	height = 30;
	x = 200;
	y = 200;

}

Player::~Player()
{
}

void Player::Update(GameMainScene* gamemain)
{

	input.InputUpdate();


	//ÉvÉåÉCÉÑÅ[à⁄ìÆ
	if (input.CheckBtn(XINPUT_BUTTON_DPAD_RIGHT) == TRUE) {
		x+=3;
	}
	if (input.CheckBtn(XINPUT_BUTTON_DPAD_LEFT) == TRUE) {
		x-=3;
	}
	if (input.CheckBtn(XINPUT_BUTTON_DPAD_UP) == TRUE) {
		y -= 3;
	}
	if (input.CheckBtn(XINPUT_BUTTON_DPAD_DOWN) == TRUE) {
		y += 3;
	}

}

void Player::Draw() const
{
	DrawBoxAA(x - width/2, y - height/2, x + width / 2, y + height / 2, 0x00ffff,true);
	DrawCircleAA(x, y, 1, 0xff00ff, true);

}
