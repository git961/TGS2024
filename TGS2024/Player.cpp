#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define DEBUG
//�f�O���[���烉�W�A���ɕϊ�
#define DEGREE_RADIAN(_deg) (M_PI*(_deg)/180.0f)


int color=0;
Player::Player()
{
	//���ƍ��W
	width = 30;
	height = 30;
	x = 200;
	y = 400;

	direction = 0;

	walk_velocity_x = 0;
	speed = 1;
	v_max = 2;

	move_x = 0;
	move_y = 0;

	//�U���Ɏg�p�ϐ�
	attacking = false;
	atk_cnt_timer = 0;

	//player�W�����v�p�ϐ�
	jump_start_flg = false;
	jump_flg = false;

	jump_timer = 0;
	rad = 0;

	jump_v0 = -12.0;
	gravity = 0.3f;
	velocity_y = 0;

	//�f�o�b�N�p
	y_ground = 600;

}

Player::~Player()
{
}

void Player::Update(GameMainScene* gamemain)
{

	//
	input.InputUpdate();


	//�W�����v
	if (input.CheckBtn(XINPUT_BUTTON_A) == TRUE)
	{
		jump_start_flg = true;
	}

	if (jump_start_flg == true)
	{
		PlayerJump();
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
		//�v���C���[�̈ړ�����
		PlayerMove();
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
	//DrawFormatString(100, 100, 0xffffff, "Right:%d", a);
	DrawFormatString(100, 120, 0xffffff, "btnnum: % d", input.Btnnum);

	DrawFormatString(100, 150, 0xffffff, "move_x: %f",move_x);


#endif // DEBUG
}

void Player::PlayerJump()
{
	////�E�W�����v
//Zakuro_Movey = -V_zero * sinf(rad) * time + (g * time * time) / 2;


	if (jump_flg == false)
	{
		jump_flg = true;
		velocity_y = -10;//������^����
		sita = 70;
		rad = sita * pi / 180;
		
	}

	velocity_y += gravity;
	move_y = -jump_v0 * sinf(rad) * jump_timer + (gravity * jump_timer * jump_timer) / 2;

	y += velocity_y;

	if (y > y_ground)
	{
		y = y_ground;
		velocity_y = 0;
		jump_flg = false;
		jump_start_flg = false;
	}


	//Old_Zakuroy = location.y;
	////�E�W�����v
	//Zakuro_Movey = -V_zero * sinf(rad) * time + (g * time * time) / 2;
	//if (location.x > 1200)location.x = Set_Zakuro_x + Zakuro_Movex;
	//if (location.y < 320)location.y = Set_Zakuro_y + Zakuro_Movey;
	//time += 0.01f;


}

void Player::PlayerMove()
{

	//�U��������Ȃ�������v���C���[�ړ�
	//�E�ړ�
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_RIGHT) == TRUE) {

		if (move_x <= 3)
		{
			move_x += 1;
		}

		direction = 0;
	}

	//���ړ�
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_LEFT) == TRUE) {

		if (move_x >= -3)
		{
			move_x -= 1;
		}
		direction = 1;
	}

	//�E���ړ����ĂȂ���
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_RIGHT) != TRUE && input.LongPressBtn(XINPUT_BUTTON_DPAD_LEFT) != TRUE)
	{
		move_x *= 0.9;
	}
	x += move_x;
}
