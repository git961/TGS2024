#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define DEBUG
//デグリーからラジアンに変換
#define DEGREE_RADIAN(_deg) (M_PI*(_deg)/180.0f)


Player::Player()
{




	//画像読込
	LoadDivGraph("image/pickaxe.png", 3, 3, 1, 64, 64, player_attack_img);
	LoadDivGraph("image/player.png", 2, 2, 1, 64, 64, player_walk_img);
	anim_cnt = 0;

	world.x = 200;
	world.y = 200;

	location.x = 200;
	location.y = 200;


	//幅と座標
	width = 40;
	height = 50;

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
	y_ground = 650;

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


	DrawBoxAA(location.x - width/2, location.y - height/2, location.x + width / 2, location.y + height / 2, 0x00ffff,true);
	DrawCircleAA(location.x, location.y, 1, 0xff00ff, true);


	//プレイヤー画像表示
	switch (direction)
	{
	case 0:
		DrawRotaGraph(location.x, location.y, 1, 0, player_walk_img[0], TRUE, FALSE);
		break;
	case 1:
		DrawRotaGraph(location.x, location.y, 1, 0, player_walk_img[1], TRUE, FALSE);
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
				DrawRotaGraph(location.x + 30, location.y-10, 1, 0, player_attack_img[0], TRUE, FALSE);
				break;
			case 3:
				DrawRotaGraph(location.x + 30, location.y+5, 1, 0, player_attack_img[1], TRUE, FALSE);
				break;
			case 4:
				DrawRotaGraph(location.x + 30, location.y+10, 1, 0, player_attack_img[2], TRUE, FALSE);
				break;
			}
			break;
		case 1:
			//左向きだったら
			switch (anim_cnt)
			{
			case 0:
				DrawRotaGraph(location.x - 30, location.y, 1, 0, player_attack_img[0], TRUE, TRUE);
				break;
			case 5:
				DrawRotaGraph(location.x - 30, location.y, 1, 0, player_attack_img[1], TRUE, TRUE);
				break;
			case 8:
				DrawRotaGraph(location.x - 30, location.y, 1, 0, player_attack_img[2], TRUE, TRUE);
				break;
			}
			break;
		}
	}

#ifdef DEBUG


	//////// 画面に XINPUT_STATE の中身を描画
	//color = GetColor(255, 255, 255);
	//for (int i = 0; i < 16; i++)
	//{
	//	DrawFormatString(64 + i % 8 * 64, 64 + i / 8 * 16, color,
	//		"%2d:%d", i, input.getkey.Buttons[i]);
	//}
	////DrawFormatString(100, 100, 0xffffff, "Right:%d", a);
	//DrawFormatString(100, 120, 0xffffff, "btnnum: % d", input.Btnnum);

	//DrawFormatString(100, 150, 0xffffff, "location.x: %f",location.x);
	DrawFormatString(100, 100, 0xffffff, "worldx: %f location.x:%f",world.x,location.x);
	DrawFormatString(100, 120, 0xffffff, "world_y: %f location.y:%f", world.y,location.y);
	/*DrawFormatString(100, 120, 0xffffff, "location.y: %f", location.y);
	DrawFormatString(100, 140, 0xffffff, "world.x: %f",world.x);
	DrawFormatString(100, 160, 0xffffff, "world.y: %f",world.y);*/


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
		vector.x = 0;
		vector.y = -1;
	}

	velocity_y += gravity;
	move_y = -jump_v0 * sinf(rad) * jump_timer + (gravity * jump_timer * jump_timer) / 2;

	location.y += velocity_y;
	world.y += velocity_y;

	if (velocity_y > 0) {
		vector.x = 0;
		vector.y = 1;
	}


	//地面
	if (location.y > y_ground)
	{
		location.y = y_ground;
		velocity_y = 0;
		jump_flg = false;
		jump_start_flg = false;
		vector.x = 0;
		vector.y = 1;
	}

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
		vector.x = 1;
		vector.y = 0;
	}

	//左移動
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_LEFT) == TRUE) {

		if (move_x >= -3)
		{
			move_x -= 1;
		}
		direction = 1;
		vector.x = -1;
		vector.y = 0;
	}

	//右左移動してない時
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_RIGHT) != TRUE && input.LongPressBtn(XINPUT_BUTTON_DPAD_LEFT) != TRUE)
	{
		move_x *= 0.9;
	}
	location.x += move_x;
	world.x += move_x;
	SetVertex();
}
