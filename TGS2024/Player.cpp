﻿#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define DEBUG
//デグリーからラジアンに変換
#define DEGREE_RADIAN(_deg) (M_PI*(_deg)/180.0f)


int color=0;
Player::Player()
{

	//画像読込
	LoadDivGraph("image/pickaxe.png", 3, 3, 1, 32, 32, player_attack_img);
	LoadDivGraph("image/player.png", 2, 2, 1, 32, 32, player_walk_img);
	anim_cnt = 0;


	//幅と座標
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

	//攻撃に使用変数
	attacking = false;
	atk_cnt_timer = 0;

	//playerジャンプ用変数
	jump_start_flg = false;
	jump_flg = false;

	jump_timer = 0;
	rad = 0;

	jump_v0 = -12.0;
	gravity = 0.3f;
	velocity_y = 0;

	//デバック用
	y_ground = 600;

}

Player::~Player()
{
}

void Player::Update(GameMainScene* gamemain)
{

	//
	input.InputUpdate();


	//ジャンプ
	if (input.CheckBtn(XINPUT_BUTTON_A) == TRUE)
	{
		jump_start_flg = true;
	}

	if (jump_start_flg == true)
	{
		PlayerJump();
	}

	//Yおしたら攻撃
	if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
	{
		attacking = true;
	}
	//何秒か経ったら攻撃中フラグを戻す？
	if (attacking == true)
	{
		anim_cnt++;
		if (atk_cnt_timer++ > 8)
		{
			anim_cnt = 0;
			atk_cnt_timer = 0;
			attacking = false;
		}
	}
	else
	{
		//プレイヤーの移動処理
		PlayerMove();
	}
}

void Player::Draw() const
{
	//プレイヤー画像表示
	switch (direction)
	{
	case 0:
		DrawRotaGraph(x, y, 1, 0, player_walk_img[0], TRUE, FALSE);
		break;
	case 1:
		DrawRotaGraph(x, y, 1, 0, player_walk_img[1], TRUE, FALSE);
		break;
	}

	if (attacking == true)
	{
		switch (direction)
		{
		case 0:
			//右向きだったら
			switch (anim_cnt)
			{
			case 0:
				DrawRotaGraph(x + 30, y, 1, 0, player_attack_img[0], TRUE, FALSE);
				break;
			case 5:
				DrawRotaGraph(x + 30, y, 1, 0, player_attack_img[1], TRUE, FALSE);
				break;
			case 8:
				DrawRotaGraph(x + 30, y, 1, 0, player_attack_img[2], TRUE, FALSE);
				break;
			}
			break;
		case 1:
			//左向きだったら
			switch (anim_cnt)
			{
			case 0:
				DrawRotaGraph(x - 30, y, 1, 0, player_attack_img[0], TRUE, TRUE);
				break;
			case 5:
				DrawRotaGraph(x - 30, y, 1, 0, player_attack_img[1], TRUE, TRUE);
				break;
			case 8:
				DrawRotaGraph(x - 30, y, 1, 0, player_attack_img[2], TRUE, TRUE);
				break;
			}
			break;
		}
	}

	//DrawBoxAA(x - width/2, y - height/2, x + width / 2, y + height / 2, 0x00ffff,true);
	//DrawCircleAA(x, y, 1, 0xff00ff, true);

#ifdef DEBUG


	////// 画面に XINPUT_STATE の中身を描画
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
	////右ジャンプ
//Zakuro_Movey = -V_zero * sinf(rad) * time + (g * time * time) / 2;


	if (jump_flg == false)
	{
		jump_flg = true;
		velocity_y = -10;//初速を与える
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
	////右ジャンプ
	//Zakuro_Movey = -V_zero * sinf(rad) * time + (g * time * time) / 2;
	//if (location.x > 1200)location.x = Set_Zakuro_x + Zakuro_Movex;
	//if (location.y < 320)location.y = Set_Zakuro_y + Zakuro_Movey;
	//time += 0.01f;


}

void Player::PlayerMove()
{

	//攻撃中じゃなかったらプレイヤー移動
	//右移動
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_RIGHT) == TRUE) {

		if (move_x <= 3)
		{
			move_x += 1;
		}

		direction = 0;
	}

	//左移動
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_LEFT) == TRUE) {

		if (move_x >= -3)
		{
			move_x -= 1;
		}
		direction = 1;
	}

	//右左移動してない時
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_RIGHT) != TRUE && input.LongPressBtn(XINPUT_BUTTON_DPAD_LEFT) != TRUE)
	{
		move_x *= 0.9;
	}
	x += move_x;
}
