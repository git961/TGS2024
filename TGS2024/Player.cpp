#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define DEBUG


Player::Player()
{




	//画像読込
	LoadDivGraph("images/Player/player.png", 5, 5, 1, 128, 128, player_img);
	LoadDivGraph("images/Player/pickaxe_effect.png", 2, 2, 1, 128, 128, effect_img);

	atk_sound = LoadSoundMem("sounds/Attack.mp3");

	p_imgnum = 0;
	effect_num = 0;

	anim_cnt = 0;

	world.x = 200;
	world.y = 600.0f;

	location.x = 200;
	location.y = 600.0f;


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
	next_attackflg = false;
	attack_cnt = 0;
	wait_atk_cnt = 0;
	wait_flg = false;

	//playerジャンプ用変数
	vel = -20;
	acc = 1;
	is_jump = true;

	//player落下用変数
	fall_vel = 7;
	fall_acc = 1;

	//デバック用
	y_ground = 650;
	player_state = NOMAL;

}

Player::~Player()
{
}

void Player::Update(GameMainScene* gamemain)
{
	//プレイヤー状態によってスイッチで変えよう

	input.InputUpdate();



	////ジャンプ
	//if (player_state == NOMAL)
	//{
	//	if (input.CheckBtn(XINPUT_BUTTON_A) == TRUE)
	//	{
	//		player_state = JUMP;
	//		is_jump = true;
	//		ground_flg = false;
	//	}
	//}

	if (wait_flg==false)
	{
		//Bおしたら攻撃
		if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
		{
			if (CheckSoundMem(atk_sound) == FALSE)
			{
				PlaySoundMem(atk_sound, DX_PLAYTYPE_BACK);
			}
			attacking = true;
			player_state = ATTACK;
		}
	}
	else if(wait_flg==true)
	{//攻撃がすぐには出来ないように待たせる
		if (wait_atk_cnt++ > 30) {
			wait_atk_cnt = 0;
			wait_flg = false;
		}
	}

	switch (player_state)
	{

	case NOMAL:

		break;
	case JUMP:
		//PlayerJump();
		break;
	case FALLING:
		//PlayerFALL();
		break;
	case ATTACK:
		break;
	default:
		break;
	}

	if (ground_flg == false)
	{
		PlayerFALL();
	}

	//プレイヤーの移動処理
	PlayerMove();

	if (attacking == true)
	{

		switch (anim_cnt)
		{
		case 0:
			p_imgnum = 1;
			break;
		case 10:
			p_imgnum = 2;
			break;
		case 15:
			effect_num = 0;
			p_imgnum = 3;
			break;
		case 20:
			effect_num = 1;
			p_imgnum = 4;
			break;
		}

	}
	else {
		p_imgnum = 0;
	}


	//何秒か経ったら攻撃中フラグを戻す？
	if (attacking == true)
	{
		anim_cnt++;
		if (anim_cnt > 2)
		{
			//そのままやるとそのままcheckBtnの中に入ってしまうので、数フレーム待たせる

			if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
			{

				next_attackflg = true;
			}
		}
		if (atk_cnt_timer++ > 30)
		{
			if (CheckSoundMem(atk_sound) == TRUE)
			{
				StopSoundMem(atk_sound);
			}

			if (next_attackflg == false||attack_cnt>1)
			{
				attack_cnt = 0;
				anim_cnt = 0;
				atk_cnt_timer = 0;
				attacking = false;
				wait_flg = true;
				player_state = NOMAL;
			}
			else
			{
				//次の攻撃をする準備
				anim_cnt = 0;
				atk_cnt_timer = 0;
				attack_cnt++;

				attacking = false;
				next_attackflg = false;
			}
		}
	}
	else
	{
		//player_state = NOMAL;
	}

	//if (ground_flg != true)
	//{
		//world.y++;
	//}
	

	SetVertex();

	
	// 端に来たら跳ね返る
	if (world.x + width / 2 > FIELD_WIDTH)
	{
		world.x=FIELD_WIDTH-20;

	}else if (world.x - width / 2 < 0) {
		world.x = width / 2;
	}

}

void Player::Draw() const
{


	DrawBoxAA(location.x - width/2, location.y - height/2, location.x + width / 2, location.y + height / 2, 0x00ffff,true);
	DrawCircleAA(location.x, location.y, 1, 0xff00ff, true);


	//プレイヤー画像表示
	DrawRotaGraph(location.x, location.y-25, 1, 0, player_img[p_imgnum], TRUE, direction);
	if (p_imgnum > 1)
	{
		DrawRotaGraph(location.x, location.y - 25, 1, 0, effect_img[effect_num], TRUE, direction);
	}
#ifdef DEBUG


	DrawCircle(box_vertex.upper_leftx, box_vertex.upper_lefty, 2, 0x0000ff, TRUE);
	DrawCircle(box_vertex.lower_leftx, box_vertex.lower_lefty, 2, 0x0000ff, TRUE);
	DrawCircle(box_vertex.upper_rightx, box_vertex.upper_righty, 2, 0x0000ff, TRUE);
	DrawCircle(box_vertex.lower_rightx, box_vertex.lower_righty, 2, 0x0000ff, TRUE);
	
	

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
	DrawFormatString(100, 140, 0xffffff, "playerstate%d", player_state);
	DrawFormatString(100, 160, 0xffffff, "attack_cnt%d", attack_cnt);
	/*DrawFormatString(100, 120, 0xffffff, "location.y: %f", location.y);
	DrawFormatString(100, 140, 0xffffff, "world.x: %f",world.x);
	DrawFormatString(100, 160, 0xffffff, "world.y: %f",world.y);*/

	DrawCircleAA(location.x, location.y, 1, 0xff00ff, true);			// 中心座標

#endif // DEBUG
}

void Player::PlayerJump()
{
	if (is_jump == true)
	{
		//ジャンプ
		vel += acc;
		world.y += vel;


		if (ground_flg == true)
		{
			is_jump = false;
			player_state = NOMAL;
			vel = -20;
		}
		//ジャンプはジャンプで下まで降りるものとして
		//落下はスイッチからぬかしてグラウンドフラグふぁるすだったらとか
	}
}

void Player::PlayerFALL()
{

	fall_vel += fall_acc;
	world.y += fall_vel;

	//地面に付いたら
	if (ground_flg==true)
	{
		fall_vel = 20;
		player_state = NOMAL;
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

	//壁に当たっていなかったら加算
	/*if (wall_flg != true)
	{*/
		location.x += move_x;
		world.x += move_x;
	//}
}
