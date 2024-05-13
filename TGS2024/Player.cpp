#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define DEBUG


Player::Player()
{




	//画像読込
	player_img[0] = LoadGraph("images/Player/player.png");
	LoadDivGraph("images/Player/player_walk.png", 4, 4, 1, 64, 64, player_walk_img);
	LoadDivGraph("images/Player/p_attack.png", 12, 4, 3, 128, 128, player_attack_img);
	LoadDivGraph("images/Player/pickaxe.png", 12, 4, 3, 128, 128, pickaxe_img);
	LoadDivGraph("images/Player/soil_effect.png", 2, 2, 1, 128, 128, soil_effect);

	atk_sound = LoadSoundMem("sounds/Attack.mp3");


	p_imgnum = 0;
	p_atk_imgnum = 0;
	effect_num = 0;
	walk_num = 0;

	anim_cnt = 0;

	world.x = 200;
	world.y = 600.0f;

	location.x = 200;
	location.y = 600.0f;

	old_worldx = world.x;

	//幅と座標
	width = 40;
	height = 50;

	direction = 0;

	walk_velocity_x = 0;
	speed = 1;

	move_x = 0;
	move_y = 0;

	//攻撃に使用変数
	attacking = false;
	atk_cnt_timer = 0;
	next_attackflg = false;
	attack_cnt = 0;
	wait_atk_cnt = 0;
	wait_flg = false;

	color13 = 0xffffff;

	is_atk_putout = false;

	player_state = NOMAL;
	is_hit_enemy = false;
}

Player::~Player()
{
}

void Player::Update(GameMainScene* gamemain)
{
	//プレイヤー状態によってスイッチで変えよう

	input.InputUpdate();



	if (wait_flg==false)
	{
		//Bおしたら攻撃
		if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
		{
			if (CheckSoundMem(atk_sound) == FALSE)
			{
				PlaySoundMem(atk_sound, DX_PLAYTYPE_BACK);
			}

			//右向きだったら
			if (direction == 0)
			{
				world.x += 3;
			}
			else {
				world.x -= 3;
			}
			attacking = true;
			player_state = ATTACK;
		}
	}
	else if(wait_flg==true)
	{//攻撃がすぐには出来ないように待たせる
		if (wait_atk_cnt++ > 30) {
			attack_cnt = 0;
			wait_atk_cnt = 0;
			wait_flg = false;
		}
	}




	if (attacking == true)
	{
		if (attack_cnt == 1)
		{
			p_atk_imgnum = 4;
		}
		else if (attack_cnt == 2)
		{
			p_atk_imgnum = 8;
		}
		else {
			p_atk_imgnum = 0;

		}

		switch (anim_cnt)
		{
		case 0:
			p_imgnum = 0;
			break;
		case 7:
			p_imgnum = 1;
			break;
		case 10:
			is_atk_putout = true;
			effect_num = 0;
			p_imgnum = 2;
			break;
		case 13:
			effect_num = 1;
			p_imgnum = 3;
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
		if (anim_cnt > 1)
		{
			//そのままやるとそのままcheckBtnの中に入ってしまうので、数フレーム待たせる
			//受付を１０までにする
			//123.じゃなくて1,23ってなるときがあるので治す？
			if (atk_cnt_timer < 15)
			{
				if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
				{
					color13 = 0x000000;
					next_attackflg = true;
				}
			}
		}
		//20フレーム回ったら
		if (atk_cnt_timer++ > 20)
		{
			if (CheckSoundMem(atk_sound) == TRUE)
			{
				StopSoundMem(atk_sound);
			}


			if (next_attackflg == false || attack_cnt>=2)
			{
				attack_cnt = 0;
				anim_cnt = 0;
				atk_cnt_timer = 0;
				is_atk_putout = false;
				next_attackflg = false;
				attacking = false;
				wait_flg = true;
				player_state = NOMAL;
				color13 = 0x000000;

			}
			else
			{
				//次の攻撃をする準備
				anim_cnt = 0;
				atk_cnt_timer = 0;
				attack_cnt++;
				is_atk_putout = false;
				attacking = false;
				next_attackflg = false;

			}
		}

	}
	else
	{

		player_state = NOMAL;
	}




	SetVertex();

	if (player_state != ATTACK)
	{
		//プレイヤーの移動処理
		PlayerMove();
	}
	else
	{
		move_x = 0;
	}

		if (player_state == WALK)
		{
			if (abs((int)world.x - (int)old_worldx) > 61)
			{
				old_worldx = world.x;
			}

			walk_abs = abs((int)world.x - (int)old_worldx);
			// 歩行
			// 5カウントごとに変わる
			if (walk_abs != 0)
			{
				walk_num = walk_abs / 20;
			}
		}
	
	
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


	DrawBoxAA(location.x - width/2, location.y - height/2, location.x + width / 2, location.y + height / 2, color13,true);
	DrawCircleAA(location.x, location.y, 1, 0xff00ff, true);


	//プレイヤー画像表示
	//DrawRotaGraph(location.x, location.y-25, 1, 0, player_img[p_imgnum], TRUE, direction);



	switch (player_state)
	{

	case NOMAL:
		DrawRotaGraph(location.x, location.y-25, 1, 0, player_img[0], TRUE, direction);
		break;
	case ATTACK:
		DrawRotaGraph(location.x, location.y - 25, 1, 0, player_attack_img[p_imgnum+p_atk_imgnum], TRUE, direction);

		if (is_hit_enemy == true)
		{
			if (p_imgnum > 2)
			{
				DrawRotaGraph(location.x, location.y - 25, 1, 0, pickaxe_img[2 + p_atk_imgnum], TRUE, direction);
			}
			else
			{
				DrawRotaGraph(location.x, location.y - 25, 1, 0, pickaxe_img[p_imgnum + p_atk_imgnum], TRUE, direction);
			}
		}
		else {

			DrawRotaGraph(location.x, location.y - 25, 1, 0, pickaxe_img[p_imgnum + p_atk_imgnum], TRUE, direction);
			if (p_imgnum > 2)
			{
				//DrawRotaGraph(location.x, location.y - 25, 1, 0, effect_img[effect_num], TRUE, direction);
				DrawRotaGraph(location.x, location.y - 25, 1, 0, soil_effect[effect_num], TRUE, direction);
			}
		}

		break;
	case WALK:
		DrawRotaGraph(location.x, location.y, 1, 0, player_walk_img[walk_num], TRUE, direction);
		break;
	default:
		break;
	}



#ifdef DEBUG


	//DrawCircle(box_vertex.upper_leftx, box_vertex.upper_lefty, 2, 0x0000ff, TRUE);
	//DrawCircle(box_vertex.lower_leftx, box_vertex.lower_lefty, 2, 0x0000ff, TRUE);
	//DrawCircle(box_vertex.upper_rightx, box_vertex.upper_righty, 2, 0x0000ff, TRUE);
	//DrawCircle(box_vertex.lower_rightx, box_vertex.lower_righty, 2, 0x0000ff, TRUE);
	//
	//

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
	DrawFormatString(location.x, location.y-20, 0x000000, "attaking%d", attacking);
	DrawFormatString(location.x, location.y, 0x000000, "%d", attack_cnt);
	/*DrawFormatString(100, 120, 0xffffff, "location.y: %f", location.y);
	DrawFormatString(100, 140, 0xffffff, "world.x: %f",world.x);
	DrawFormatString(100, 160, 0xffffff, "world.y: %f",world.y);*/

	DrawCircleAA(location.x, location.y, 1, 0xff00ff, true);			// 中心座標

#endif // DEBUG
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

		if (player_state != ATTACK)
		{
			player_state = WALK;
		}
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

		if (player_state != ATTACK)
		{
			player_state = WALK;
		}
	}

	//右左移動してない時
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_RIGHT) != TRUE && input.LongPressBtn(XINPUT_BUTTON_DPAD_LEFT) != TRUE)
	{
		move_x *= 0.9;
		if (player_state != ATTACK)
		{
			player_state = NOMAL;
		}
	}

	//壁に当たっていなかったら加算
	/*if (wall_flg != true)
	{*/
		location.x += move_x;
		world.x += move_x;
	//}
}
