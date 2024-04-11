#include "Player.h"
#define DEBUG
int color=0;
int a;
Player::Player()
{
	//���ƍ��W
	width = 30;
	height = 30;
	x = 200;
	y = 600;

	//�U���Ɏg�p�ϐ�
	attacking = false;
	atk_cnt_timer = 0;

	//player�W�����v�p�ϐ�
	jump = false;
	old_y = 0;
}

Player::~Player()
{
}

void Player::Update(GameMainScene* gamemain)
{

	//
	input.InputUpdate();
	a = input.LongPressBtn(XINPUT_BUTTON_DPAD_RIGHT);

	//
	if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
	{
		jump = true;
	}

	//Y��������U��
	if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
	{
		attacking = true;
	}
	//���b���o������U�����t���O��߂��H
	if (attacking == true)
	{
		if (atk_cnt_timer++ > 5)
		{
			atk_cnt_timer = 0;
			attacking = false;
		}
	}
	else
	{

		//�U��������Ȃ�������v���C���[�ړ�
		//�E�ړ�
		if (input.LongPressBtn(XINPUT_BUTTON_DPAD_RIGHT) == TRUE) {
			x += 3;
			direction = 0;
		}
		//���ړ�
		if (input.LongPressBtn(XINPUT_BUTTON_DPAD_LEFT) == TRUE) {
			x -= 3;
			direction = 1;
		}
	}
}

void Player::Draw() const
{
	DrawBoxAA(x - width/2, y - height/2, x + width / 2, y + height / 2, 0x00ffff,true);
	DrawCircleAA(x, y, 1, 0xff00ff, true);

#ifdef DEBUG


	////// ��ʂ� XINPUT_STATE �̒��g��`��
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

void Player::PlayerJump()
{
	old_y = y;
	//Old_Zakuroy = location.y;
	////�E�W�����v
	//Zakuro_Movex = V_zero * cosf(rad) * time;
	//Zakuro_Movey = -V_zero * sinf(rad) * time + (g * time * time) / 2;

}
