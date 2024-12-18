﻿#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>

Player::Player(float set_x,float set_y)
{
	//画像読込
	LoadDivGraph("images/Player/player_img.png",72, 4, 18, 170, 170, player_img);
	LoadDivGraph("images/Player/pickaxe2.png", 8, 4, 2, 170, 170, pickaxe_img);
	LoadDivGraph("images/Player/pickeffect3.png", 4, 4, 1, 170, 170, pickaxe_effect);
	LoadDivGraph("images/Player/soil_effect.png", 2, 2, 1, 170, 170, soil_effect);

	pickaxe_add_x = 0.0f;

	atk_sound = LoadSoundMem("sounds/se/player/Attack.mp3");
	op_run_sound = LoadSoundMem("sounds/se/player/run.mp3");
	damage_sound = LoadSoundMem("sounds/se/player/damage.mp3");
	throw_dynamite_sound = LoadSoundMem("sounds/se/player/Throw.mp3");
	death_sound = LoadSoundMem("sounds/se/player/death.mp3");

	
	img_down = 45;

	reset_timer = 0;
	p_imgnum = 0;
	old_p_imgnum = p_imgnum;
	//p_atk_imgnum = 0;
	effect_num = 0;
	//walk_num = 0;

	anim_cnt = 0;

	//world.x = 200.0f;
	//world.y = 1700.0f;
	world.x = set_x;
	world.y = set_y;

	location.x = 0.0f;
	location.y = 0.0f;

	old_worldx = world.x;
	old_worldy = world.y;

	//体力
	hp = 50;
	//hp = 10;

	//攻撃力
	attack = 10;

	//幅と座標
	width = 50;
	height = 80;
	half_width = width / 2.0f;
	half_height = height / 2.0f;

	direction = 0;

	walk_velocity_x = 0;
	curent_x = world.x;
	curent_y = world.y;

	move_x = 0;
	move_y = 1;

	walk_abs = 0;
	fall_abs = 0;

	//攻撃に使用変数
	attacking = false;
	atk_cnt_timer = 0;
	next_attackflg = false;
	attack_cnt = 0;
	wait_atk_cnt = 0;
	wait_flg = false;

	//ダイナマイトに使用
	atk_dynamite = false;
	//dyna_throw_num = 0;
	dyna_anmcnt = 0;

	dyna_stock_num = 5;
	dyna_stock_cnt = 0;


	is_atk_putout = false;

	player_state = PlayerState::NOMAL;
	is_hit_enemy = false;

	//被弾点滅
	hit_damage = false;
	flash_start = false;
	flash_flg = false;
	flash_cnt = 0;

	death_anim_cnt = 0;
	//death_num = 0;
	death_flg = false;

	//op_num = 2;
	op_cnt = 0;
	tuto_anim_flg=false;
	tuto_atk_flg = false;
	tuto_num = 0;
	tuto_cnt=0;
	tuto_ui_num = 0;
	rock_break_flg = false;
	rock_cnt = 0;

	p_atk_imgnum = 0;
	//p_nomal_num = 0;

	// サウンドの音量設定
	ChangeVolumeSoundMem(200, atk_sound);
	ChangeVolumeSoundMem(180, op_run_sound);
	ChangeVolumeSoundMem(180, damage_sound);
	ChangeVolumeSoundMem(180, throw_dynamite_sound);
	ChangeVolumeSoundMem(210, death_sound);

	dyna_anm_start = false;
	walk_stop_flg = false;
	tuto_anim_dynaflg = false;
	start_flg = false;

	helmet_flg = false;
	helmet_down = -1000;

	// stop_walk_snd = false;

	// エンド画面用変数
	LoadDivGraph("images/Player/player_end1.png", 3, 3, 1, 170, 170, player_end_img);
	end_img_num = 0;
	end_anim_cnt = 0;


	// エンドクレジット画面用変数
	LoadDivGraph("images/Player/dance.png", 8, 4, 2, 170, 170, player_credits_img);
	LoadDivGraph("images/Player/applause.png", 4, 4, 1, 170, 170, applause_img);
	LoadDivGraph("images/Player/cracker.png", 5, 5, 1, 170, 170, cracker_img);
	LoadDivGraph("images/Player/ribbon.png", 5, 5, 1, 150, 220, ribbon_img);
	credits_img_num = 0;
	ribbon_img_num = 0;
	credits_anim_cnt = 0;
	cracker_anim_cnt = 0;
	ribbon_anim_cnt = 0;
	credits_timer = 0;
	facing_left_flg = false;
	push_b_flg = false;
	dash_anim_cnt = 0;
	change_to_title_flg = false;
	ribbon_x = 0;
	ribbon_y = 0;
	set_ribbon_pos_flg = false;
	change_scene_cnt = 0;
	credits_walk_cnt = 0;
	walk_cnt_up_flg = true;
	anim_end_flg = false;

	limit_y = 600;
	fall_flg = false;
	lift_hit_flg = false;
	geyser_hit_flg = false;
	magma_hit_flg = false;
	floorblock_hit_flg = false;
	fallingfloor_hit_flg = false;
	vel = 1.0f;
	set_speed = 0.0f;
	speed = set_speed;
	rest_move_count = 0;
	stop_up_flg = false;

	lift_anim_cnt = 0;
}

Player::~Player()
{
	// サウンド削除
	DeleteSoundMem(atk_sound);
	DeleteSoundMem(op_run_sound);
	DeleteSoundMem(damage_sound);
	DeleteSoundMem(throw_dynamite_sound);
	DeleteSoundMem(death_sound);

	for (int i = 0; i < 68; i++)
	{
		DeleteGraph(player_img[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(pickaxe_img[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(pickaxe_effect[i]);
	}
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(soil_effect[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(player_end_img[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(player_credits_img[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(applause_img[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(cracker_img[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(ribbon_img[i]);
	}

}

void Player::Update(GameMainScene* gamemain)
{
	

	input.InputUpdate();
	SetVertex();



	switch (player_state)
	{
	case PlayerState::DEATH:
		is_atk_putout = false;
		DeathAnim();

		break;
	case PlayerState::DYNAMITE:

		ThrowAnim();

		break;
	case PlayerState::HITDAMAGE:
		if (direction == false)
		{
			p_imgnum = 30;
		}
		else {
			p_imgnum = 31;
		}



		if (CheckSoundMem(damage_sound) == FALSE)
		{
			PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
		}

		attacking = false;
		is_atk_putout = false;
		p_atk_imgnum = 0;
		attack_cnt = 0;
		anim_cnt = 0;
		atk_cnt_timer = 0;
		wait_flg = true;
		
		if ((unsigned)move_x > 0) {
			move_x *= 0.9f;
			location.x += move_x;
			world.x += move_x;
		}
		else
		{
			player_state = PlayerState::NOMAL;
			hit_damage = false;
			flash_start = true;
		}

		break;
	case PlayerState::ATTACK:
	case PlayerState::WALK:
	case PlayerState::NOMAL:


		if (player_state == PlayerState::NOMAL && fall_flg == false)
		{
			if (direction == false)
			{
				p_imgnum = 27;
			}
			else {
				p_imgnum = 28;
			}
		}

		PlayerAttack();


		if (player_state != PlayerState::ATTACK)
		{
			//プレイヤーの移動処理
			PlayerMove();
		}
		else
		{
			move_x = 0;
		}

		WalkAnim();

		PlayerFall();
		PlayerFallAnim();

		// 端に来たら跳ね返る
		if (world.x + width / 2 > FIELD_WIDTH)
		{
			world.x = FIELD_WIDTH - 20;
			StopSoundMem(op_run_sound);
		}
		else if (world.x - width / 2 < 0) {
			world.x = width / 2;
			StopSoundMem(op_run_sound);
		}

		//敵からダメージを食らったら
		if (hit_damage == true)
		{
			if (CheckSoundMem(atk_sound) == TRUE)
			{
				StopSoundMem(atk_sound);
			}
			player_state = PlayerState::HITDAMAGE;

			//ノックバック処理
			//右向きだったら
			if (direction == 0)
			{
				move_x = -4;
			}
			else
			{
				move_x = 4;
			}
		}

		//点滅処理
		if (flash_start == true)
		{
			if ((flash_cnt % 20) == 0)
			{
				flash_flg = true;
			}
			else if ((flash_cnt % 10) == 0) {
				flash_flg = false;
			}

			if (flash_cnt > 90)
			{
				flash_flg = false;
				flash_start = false;
				gamemain->SetPlayerDamageOnce(false);
			}


			flash_cnt++;

		}
		else
		{
			flash_cnt = 0;
		}

		//つるはし攻撃
		if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE && fall_flg == false)
		{
			attacking = true;
			player_state = PlayerState::ATTACK;
			wait_flg = false;
		}

		if (dyna_stock_num > 0)
		{
			//ダイナマイト攻撃
			if (input.CheckBtn(XINPUT_BUTTON_Y) == TRUE && attacking == false && fall_flg == false)
			{
				player_state = PlayerState::DYNAMITE;
			}
		}


		if (player_state != PlayerState::WALK)
		{
			StopSoundMem(op_run_sound);
		}

		HitMapChip(gamemain);

		break;
		case PlayerState::STOP:
			break;
	default:
		break;
	}
	
	if (hp <= 0) {
		if (CheckSoundMem(damage_sound) == FALSE)
		{
			PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
		}


		player_state = PlayerState::DEATH;
	}

	
#ifdef DEBUG

	#endif // DEBUG
	
}

void Player::Draw() const
{

	if (flash_flg == true)
	{

		//ダメージを受けたら、薄くなったり、元に戻ったりの点滅をして
		//数秒たったら戻る
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		
	}
	else if(flash_flg==false) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}
		

	DrawRotaGraph((int)location.x, (int)location.y - (int)img_down, 1, 0, player_img[p_imgnum], TRUE, false);
	if (player_state== PlayerState::ATTACK)
	{
		DrawRotaGraph((int)location.x+(int)pickaxe_add_x, (int)location.y - (int)img_down, 1, 0, pickaxe_img[p_atk_imgnum], TRUE, direction);
		DrawRotaGraph((int)location.x+(int)pickaxe_add_x, (int)location.y - (int)img_down, 1, 0, pickaxe_effect[p_atk_imgnum], TRUE, direction);
		if (p_atk_imgnum > 2)
		{
			//DrawRotaGraph(location.x, location.y - img_down, 1, 0, effect_img[effect_num], TRUE, direction);
			DrawRotaGraph((int)location.x, (int)location.y - (int)img_down, 1, 0, soil_effect[effect_num], TRUE, direction);
		}
	}


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef DEBUG

#endif // DEBUG
}

void Player::PlayerMove()
{

	curent_x = world.x;
	curent_y = world.y;

	//攻撃中じゃなかったらプレイヤー移動
	//右移動
	
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_RIGHT) == TRUE||input.GetPadThumbLX()>=32000) {

		move_x = 5.0f;
		
		direction = 0;

		if (player_state != PlayerState::ATTACK)
		{
			player_state = PlayerState::WALK;
		}

	}

	//左移動
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_LEFT) == TRUE||input.GetPadThumbLX() <= -32000) {


		move_x = -5.0f;		

		direction = 1;

		if (player_state != PlayerState::ATTACK)
		{
			player_state = PlayerState::WALK;
		}

	}

	//右左移動してない時
	//十字キーの入力がなかったら
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_RIGHT) != TRUE && input.LongPressBtn(XINPUT_BUTTON_DPAD_LEFT) != TRUE)
	{
		//左スティックからの入力が無かったら
		if (input.GetPadThumbLX() >= -32000 && input.GetPadThumbLX() <= 32000)
		{
			move_x *= 0.9f;
			if (player_state != PlayerState::ATTACK)
			{
				player_state = PlayerState::NOMAL;
			}
		}
	}


	//落ちてる途中だったら
	if (fall_flg == true)
	{
		move_x = move_x / 1.5f;
	}
	else {
		//落ちていなかったら
		speed = 0.0f;
	}


	location.x += move_x;
	world.x += move_x;
	

}

void Player::WalkAnim()
{
	if (player_state == PlayerState::WALK && fall_flg == false)
	{

		if (abs((int)world.x - (int)old_worldx) > 119)
		{
			old_worldx = world.x;
		}

		walk_abs = abs((int)world.x - (int)old_worldx);
		// 歩行
		// 5カウントごとに変わる
		if (walk_abs != 0)
		{

			if (direction == false)
			{
				p_imgnum = 54 + walk_abs / 40;
			}
			else {
				p_imgnum = 57 + walk_abs / 40;
			}

			//走るSE再生
			if (p_imgnum == 55||p_imgnum==58)
			{
				if (world.x + width / 2 < FIELD_WIDTH)
				{
					if (old_p_imgnum != p_imgnum)
					{
						//走る音
						if (CheckSoundMem(op_run_sound) == FALSE)
						{
							PlaySoundMem(op_run_sound, DX_PLAYTYPE_BACK);
						}
					}
				}
			}

			old_p_imgnum = p_imgnum;
		}
	}

	//move_xが0になってない場合
	if (player_state != PlayerState::WALK && fall_flg == false) {

		if (direction == 0 && move_x > 0.0f)
		{
			if (move_x < 0.3f)
			{
				move_x = 0.0f;
			}

			//プレイヤーを歩かせる
			rest_move_count++;
			if (rest_move_count < 15) {
				p_imgnum = 55;
			}
			else if (rest_move_count < 25)
			{
				p_imgnum = 56;
			}
		}

		if (direction == 1 && move_x < 0.0f)
		{
			if (move_x > -0.3f)
			{
				move_x = 0.0f;
			}

			//プレイヤーを歩かせる
			rest_move_count++;
			if (rest_move_count < 15) {
				p_imgnum = 58;
			}
			else if (rest_move_count < 25)
			{
				p_imgnum = 59;
			}
		}

	}
	else {
		rest_move_count = 0;
	}

}

void Player::DeathAnim()
{
	death_anim_cnt++;
	if (direction == false)
	{
		switch (death_anim_cnt)
		{
		case 1:
			p_imgnum = 46;
			break;
		case 5:
			p_imgnum = 47;
			break;
		case 15:
			if (CheckSoundMem(death_sound) == FALSE)
			{
				PlaySoundMem(death_sound, DX_PLAYTYPE_BACK);
			}
			p_imgnum = 48;
			break;
		case 20:
			p_imgnum = 49;
			break;
		case 25:
			death_flg = true;
			death_anim_cnt = 0;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (death_anim_cnt)
		{
		case 1:
			p_imgnum = 50;
			break;
		case 5:
			p_imgnum = 51;
			break;
		case 15:
			if (CheckSoundMem(death_sound) == FALSE)
			{
				PlaySoundMem(death_sound, DX_PLAYTYPE_BACK);
			}
			p_imgnum = 52;
			break;
		case 20:
			p_imgnum = 53;
			break;
		case 25:
			death_flg = true;
			death_anim_cnt = 0;
			break;
		default:
			break;
		}

	}
}

void Player::ThrowAnim()
{
	//ダイナマイト投擲
	if (direction == false)
	{
		switch (dyna_anmcnt)
		{
		case 1:
			PlaySoundMem(throw_dynamite_sound, DX_PLAYTYPE_BACK);

			dyna_stock_num -= 1;
			//dyna_throw_num = 0;
			p_imgnum = 32;
			break;
		case 5:
			//dyna_throw_num = 1;
			p_imgnum = 33;
			break;
		case 10:
			//dyna_throw_num = 2;
			p_imgnum = 34;
			atk_dynamite = true;
			break;
		case 15:
			dyna_anmcnt = 0;
			player_state = PlayerState::NOMAL;
			break;
		default:
			break;
		}
	}
	else {
		switch (dyna_anmcnt)
		{
		case 1:
			PlaySoundMem(throw_dynamite_sound, DX_PLAYTYPE_BACK);
			dyna_stock_num -= 1;
			//dyna_throw_num = 0;
			p_imgnum = 35;
			break;
		case 5:
			//dyna_throw_num = 1;
			p_imgnum = 36;
			break;
		case 10:
			//dyna_throw_num = 2;
			p_imgnum = 37;
			atk_dynamite = true;
			break;
		case 15:
			dyna_anmcnt = 0;
			player_state = PlayerState::NOMAL;
			break;
		default:
			break;
		}

	}
	dyna_anmcnt++;
}

void Player::PlayerFall()
{
	if (fall_flg == true)
	{
		if (vel < 4.0f)
		{
			vel += 1.0f;
			speed += vel;
		}

	}
	else {
		vel = 1.0f;

	}
	//y座標に加算
	world.y += speed;
}

void Player::PlayerFallAnim()
{

	//落下画像表示
	if (fall_flg == true)
	{
		if (abs((int)world.y - (int)old_worldy) > 119)
		{
			old_worldy = world.y;
		}

		fall_abs = abs((int)world.y - (int)old_worldy);

		if (fall_abs != 0)
		{
			if (direction == 0)
			{
				//落下右向き
				p_imgnum = 66 + fall_abs / 40;
			}
			else {
				//落下左向き
				p_imgnum = 69 + fall_abs / 40;
			}
		}
	}

}

void Player::PlayerAttack()
{
	if (attacking == true)
	{
		if (direction == false)
		{
			switch (anim_cnt)
			{
			case 0:
				pickaxe_add_x = 0.0f;
				p_atk_imgnum = 0;
				p_imgnum = 38;
				break;
			case 7:
				p_atk_imgnum = 1;
				p_imgnum = 39;
				if (CheckSoundMem(atk_sound) == FALSE)
				{
					PlaySoundMem(atk_sound, DX_PLAYTYPE_BACK);
				}
				break;
			case 10:
				p_atk_imgnum = 2;
				is_atk_putout = true;
				effect_num = 0;
				p_imgnum = 40;
				break;
			case 13:
				pickaxe_add_x = 15.0f;
				p_atk_imgnum = 3;
				effect_num = 1;
				p_imgnum = 41;
				break;
			}
		}
		else
		{
			switch (anim_cnt)
			{
			case 0:
				p_atk_imgnum = 0;
				p_imgnum = 42;
				break;
			case 7:
				p_atk_imgnum = 1;
				p_imgnum = 43;
				if (CheckSoundMem(atk_sound) == FALSE)
				{
					PlaySoundMem(atk_sound, DX_PLAYTYPE_BACK);
				}
				break;
			case 10:
				p_atk_imgnum = 2;
				is_atk_putout = true;
				effect_num = 0;
				p_imgnum = 44;
				break;
			case 13:
				pickaxe_add_x = -15.0f;
				p_atk_imgnum = 3;
				effect_num = 1;
				p_imgnum = 45;
				break;
			}

		}
	}

	//何秒か経ったら攻撃中フラグを戻す？
	if (attacking == true)
	{
		anim_cnt++;

		//20フレーム回ったら
		if (atk_cnt_timer++ > 20)
		{
			if (CheckSoundMem(atk_sound) == TRUE)
			{
				StopSoundMem(atk_sound);
			}


				p_atk_imgnum = 0;
				attack_cnt = 0;
				anim_cnt = 0;
				atk_cnt_timer = 0;
				is_atk_putout = false;
				attacking = false;
				wait_flg = true;
				player_state = PlayerState::NOMAL;
		}
	}
}

void Player::PlayerTutoAttack()
{
	if (attacking == true)
	{
		if (direction == false)
		{
			//初段
			switch (anim_cnt)
			{
			case 0:
				p_atk_imgnum = 0;
				p_imgnum = 13;
				break;
			case 7:
				p_atk_imgnum = 1;
				p_imgnum = 14;
				if (CheckSoundMem(atk_sound) == FALSE)
				{
					PlaySoundMem(atk_sound, DX_PLAYTYPE_BACK);
				}
				break;
			case 10:
				p_atk_imgnum = 2;
				is_atk_putout = true;
				effect_num = 0;
				p_imgnum = 15;
				break;
			case 13:
				p_atk_imgnum = 3;
				effect_num = 1;
				p_imgnum = 16;
				break;
			}
		}
		else {
			switch (anim_cnt)
			{
			case 0:
				p_atk_imgnum = 0;
				p_imgnum = 17;
				break;
			case 7:
				p_atk_imgnum = 1;
				p_imgnum = 18;
				if (CheckSoundMem(atk_sound) == FALSE)
				{
					PlaySoundMem(atk_sound, DX_PLAYTYPE_BACK);
				}
				break;
			case 10:
				p_atk_imgnum = 2;
				is_atk_putout = true;
				effect_num = 0;
				p_imgnum = 19;
				break;
			case 13:
				p_atk_imgnum = 3;
				effect_num = 1;
				p_imgnum = 20;
				break;
			}
		}

	}


	//何秒か経ったら攻撃中フラグを戻す？
	if (attacking == true)
	{
		anim_cnt++;

		//20フレーム回ったら
		if (atk_cnt_timer++ > 20)
		{
			if (CheckSoundMem(atk_sound) == TRUE)
			{
				StopSoundMem(atk_sound);
			}

			attack_cnt = 0;
			anim_cnt = 0;
			atk_cnt_timer = 0;
			is_atk_putout = false;
			attacking = false;
			wait_flg = true;
			player_state = PlayerState::NOMAL;
		}
	}
}

void Player::TutoWalkAnim()
{
	if (player_state == PlayerState::WALK)
	{

		if (abs((int)world.x - (int)old_worldx) > 119)
		{
			old_worldx = world.x;
		}

		walk_abs = abs((int)world.x - (int)old_worldx);
		// 歩行
		if (walk_abs != 0)
		{
			if (direction == false)
			{
				p_imgnum = 4 + walk_abs / 40;
			}
			else {
				p_imgnum = 7 + walk_abs / 40;

			}
		}

		if (walk_abs == 0)
		{
			if (direction == false)
			{
				p_imgnum = 4;
			}
			else {
				p_imgnum = 7;

			}
		}

		//走るSE再生
		if (p_imgnum == 5 || p_imgnum == 8)
		{
			if (world.x + width / 2 < FIELD_WIDTH)
			{
				if (old_p_imgnum != p_imgnum)
				{
					//走る音
					if (CheckSoundMem(op_run_sound) == FALSE)
					{
						PlaySoundMem(op_run_sound, DX_PLAYTYPE_BACK);
					}
				}
			}
		}

		old_p_imgnum = p_imgnum;
	}
	
	//move_xが0になってない場合
	if (player_state != PlayerState::WALK) {

		if (direction == 0 && move_x > 0.0f)
		{
			if (move_x < 0.3f)
			{
				move_x = 0.0f;
			}

			//プレイヤーを歩かせる
			rest_move_count++;
			if (rest_move_count < 15) {
				p_imgnum = 4;
			}
			else if (rest_move_count < 25)
			{
				p_imgnum = 5;
			}
		}

		if (direction == 1 && move_x < 0.0f)
		{
			if (move_x > -0.3f)
			{
				move_x = 0.0f;
			}

			//プレイヤーを歩かせる
			rest_move_count++;
			if (rest_move_count < 15) {
				p_imgnum = 7;
			}
			else if (rest_move_count < 25)
			{
				p_imgnum = 8;
			}
		}

	}
	else {
		rest_move_count = 0;
	}


}

void Player::LiftEvent(int set_num)
{
	switch (set_num)
	{
	case 0:
		location.x += 1.0f;
		world.x += 1.0f;
		if (abs((int)world.x - (int)old_worldx) > 59)
		{
			old_worldx = world.x;
			//走る音
			if (CheckSoundMem(op_run_sound) == FALSE)
			{
				PlaySoundMem(op_run_sound, DX_PLAYTYPE_BACK);
			}
		}
		walk_abs = abs((int)world.x - (int)old_worldx);
		// 歩行
		// 5カウントごとに変わる
		if (walk_abs != 0)
		{
			p_imgnum = 54 + walk_abs / 40;

		}

		break;
	case 1:
		if (lift_anim_cnt++ < 30)
		{
			p_imgnum = 28;
		}
		else if (lift_anim_cnt < 60)
		{
			p_imgnum = 27;
		}
		else if (lift_anim_cnt < 90)
		{
			lift_anim_cnt = 0;
		}
		break;
	case 2:
		lift_anim_cnt = 0;
		p_imgnum = 30;
		break;
	case 3:
		if (lift_anim_cnt++ < 60) {
			p_imgnum = 49;
		}
		else if(lift_anim_cnt>80)
		{
			p_imgnum = 29;
		}
		
		if (lift_anim_cnt > 100)
		{
			player_state = PlayerState::NOMAL;
			lift_anim_cnt = 0;
		}
		break;
	default:
		break;
	}
}

void Player::OpAnimUpdate(AnimScene* anim_scene,int set_case)
{

	switch (set_case)
	{
	case 0:

		world.x = -50;
		location.x = -50;

		if (CheckSoundMem(atk_sound) == FALSE&&op_cnt<=2)
		{
			PlaySoundMem(atk_sound, DX_PLAYTYPE_BACK);
			op_cnt++;
		}

		if (op_cnt >= 2)
		{
			op_cnt++;
			if (op_cnt > 60)
			{
				op_cnt = 0;
				anim_scene->SetAnimScene(1);
			}
		}

	break;
	case 2:
		//画面の中心まで歩いてくる
		if (640 > world.x) {
			//走る音
			if (CheckSoundMem(op_run_sound) == FALSE)
			{
				PlaySoundMem(op_run_sound, DX_PLAYTYPE_BACK);
			}

			player_state = PlayerState::WALK;
			location.x += 4;
			world.x += 4;

			if (abs((int)world.x - (int)old_worldx) > 59)
			{
				old_worldx = world.x;
			}

			walk_abs = abs((int)world.x - (int)old_worldx);
			// 歩行
			// 5カウントごとに変わる
			if (walk_abs != 0)
			{
				p_imgnum = 4+walk_abs / 20;
			}

		}
		else {
			if (op_cnt++ >60)
			{
				//player_state = PANIM;
				p_imgnum = 63;
				if (op_cnt++ > 140)
				{
					anim_scene->SetAnimScene(3);
					op_cnt = 0;
				}
			}
			else
			{
				//player_state = NOMAL;
				p_imgnum = 0;
			}
		}
		
		
	break;
	case 4:
		p_imgnum = 64;
		break;
	case 5:
		world.x = 620;
		location.x = 620;
		player_state = PlayerState::PANIM;
		op_cnt++;
		switch (op_cnt)
		{
		case 1:
			p_imgnum = 0;
			break;
		case 30:
			p_imgnum = 1;
			break;
		case 60:
			p_imgnum = 0;
			break;
		case 90:
			anim_scene->SetShakeFlg(false);
			break;
		case 120:
			p_imgnum = 2;
			anim_scene->SetExc(true);
			break;
		case 140:
			anim_scene->SetExc(false);
			anim_scene->SetRun(true);

			break;
		case 150:
			anim_scene->SetAnimScene(6);
			op_cnt = 0;
			break;
		}

		break;
	case 6:
		
		if (1400> world.x) {
			player_state = PlayerState::ASE;
			location.x += 4;
			world.x += 4;

			if (abs((int)world.x - (int)old_worldx) > 59)
			{
				old_worldx = world.x;
			}

			walk_abs = abs((int)world.x - (int)old_worldx);
			// 歩行
			// 5カウントごとに変わる
			if (walk_abs != 0)
			{
				p_imgnum = 10+walk_abs / 20;
			}
			//走る音
			if (CheckSoundMem(op_run_sound) == FALSE)
			{
				PlaySoundMem(op_run_sound, DX_PLAYTYPE_BACK);
			}
		}

		break;
	}
}

void Player::TutorialAnimUpdate()
{
	input.InputUpdate();
	SetVertex();

	if (player_state == PlayerState::NOMAL && p_imgnum != 27)
	{
		if (direction == false)
		{
			p_imgnum = 0;
		}
		else {
			p_imgnum = 1;
		}
	}

	switch (tuto_num)
	{
	case 0:
		if (tuto_atk_flg == false)
		{
			if (tuto_anim_flg == false) {

				if (370 < world.x)
				{
					tuto_anim_flg = true;
				}

				player_state = PlayerState::ASE;
				location.x += 3;
				world.x += 3;

				if (abs((int)world.x - (int)old_worldx) > 39)
				{
					old_worldx = world.x;
				}

				walk_abs = abs((int)world.x - (int)old_worldx);
				// 歩行
				// 5カウントごとに変わる
				if (walk_abs != 0)
				{
					p_imgnum = 10+walk_abs / 15;
				}
				//走る音
				if (CheckSoundMem(op_run_sound) == FALSE)
				{
					PlaySoundMem(op_run_sound, DX_PLAYTYPE_BACK);
				}


			}

			if (tuto_anim_flg == true) {
				death_anim_cnt++;
				switch (death_anim_cnt)
				{
				case 1:
					player_state = PlayerState::DEATH;
					world.x += -10;
					location.x += -10;
					p_imgnum = 21;
					break;
				case 5:
					world.x += -10;
					location.x += -10;
					p_imgnum = 22;
					break;
				case 15:
					if (CheckSoundMem(death_sound) == FALSE)
					{
						PlaySoundMem(death_sound, DX_PLAYTYPE_BACK);
					}

					p_imgnum = 23;
					break;
				case 20:
					p_imgnum = 24;
					break;
				case 80:
					world.x += 1;
					location.x += 1;
					break;
				case 85:
					world.x -= 2;
					location.x -= 2;
					break;
				case 90:
					world.x += 1;
					location.x += 1;

					break;
				case 100:
					player_state = PlayerState::PANIM;
					//op_num = 5;
					p_imgnum = 3;
					break;
				case 150:
					player_state = PlayerState::ATTACK;
					p_imgnum = 13;
					tuto_atk_flg = true;
					tuto_ui_num = 1;
					death_anim_cnt = 0;
					break;
				default:
					break;
				}
			}

		}
		else
		{

			if (rock_break_flg==true)
			{
					tuto_cnt = 0;
					tuto_ui_num = 0;
					tuto_num = 1;
					rock_cnt=0;
					player_state = PlayerState::NOMAL;
				
			}
			else
			{
				//三回攻撃したら
				if (tuto_cnt >= 3)
				{
					if (rock_cnt++ > 20)
					{
						rock_break_flg = true;
					}
				}
				//つるはし攻撃
				if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
				{
					if (CheckSoundMem(atk_sound) == FALSE)
					{
						tuto_cnt++;
						PlaySoundMem(atk_sound, DX_PLAYTYPE_BACK);
					}


					attacking = true;
					player_state = PlayerState::ATTACK;
					wait_flg = false;
				}

				PlayerTutoAttack();

			}
	
		


		}
	break;
	case 1:

		if (world.x > 1200)
		{
			tuto_num = 2;
		}
		else
		{
			//
			tuto_ui_num = 4;
		}

		SetVertex();

		//つるはし攻撃
		if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
		{
			if (CheckSoundMem(atk_sound) == FALSE)
			{

				PlaySoundMem(atk_sound, DX_PLAYTYPE_BACK);
			}

			attacking = true;
			player_state = PlayerState::ATTACK;
			wait_flg = false;
		}
		PlayerTutoAttack();


		if (player_state != PlayerState::ATTACK)
		{
			//プレイヤーの移動処理
			PlayerMove();
		}
		else
		{
			move_x = 0;
		}

		TutoWalkAnim();

	break;
	case 2:
		//袋に近づいて開ける
		if (walk_stop_flg == true)
		{
			player_state = PlayerState::PANIM;
			p_imgnum = 63;
			//op_num = 2;
			if (tuto_cnt++ > 60)
			{
				tuto_cnt = 0;
				tuto_ui_num = 2;
				walk_stop_flg = false;
				tuto_num = 3;
			}
		}
		else{
			location.x += 1;
			world.x += 1;
			player_state = PlayerState::WALK;
			TutoWalkAnim();
		}

		break;
	case 3:
		if (walk_stop_flg == true)
		{
			tuto_ui_num = 3;

			if (player_state!= PlayerState::DYNAMITE)
			{
				//ダイナマイト攻撃
				if (input.CheckBtn(XINPUT_BUTTON_Y) == TRUE || CheckHitKey(KEY_INPUT_S) == TRUE)
				{
					player_state = PlayerState::DYNAMITE;
					tuto_anim_dynaflg = true;
				}
			}

			if (player_state == PlayerState::DYNAMITE)
			{
				tuto_ui_num = 0;

				move_x = 0;
				switch (dyna_anmcnt)
				{
				case 1:
					PlaySoundMem(throw_dynamite_sound, DX_PLAYTYPE_BACK);
					dyna_stock_num -= 1;
					p_imgnum = 60;
					break;
				case 5:
					p_imgnum = 61;
					break;
				case 10:
					p_imgnum = 62;
					atk_dynamite = true;
					break;
				case 150:

					tuto_anim_dynaflg = false;
					break;
				case 200:
					dyna_anmcnt = 0;
					p_imgnum = 0;
					player_state = PlayerState::NOMAL;
					tuto_num = 4;
					break;
				default:
					break;
				}
				dyna_anmcnt++;

			}
		}

		break;
	case 4:
		SetVertex();

		//つるはし攻撃
		if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
		{
			if (CheckSoundMem(atk_sound) == FALSE)
			{

				PlaySoundMem(atk_sound, DX_PLAYTYPE_BACK);
			}

			attacking = true;
			player_state = PlayerState::ATTACK;
			wait_flg = false;
		}
		PlayerTutoAttack();


		if (player_state != PlayerState::ATTACK)
		{
			//プレイヤーの移動処理
			PlayerMove();
		}
		else
		{
			move_x = 0;
		}

		TutoWalkAnim();

		if (world.x > 1950)
		{
			tuto_num = 5;
			walk_stop_flg = false;
		}


		break;
	case 5:

		if (walk_stop_flg == true)
		{
			//helmet_flg = true;
			player_state = PlayerState::PANIM;
			p_imgnum = 65;
			tuto_cnt++;
			if (tuto_cnt > 60)
			{
				tuto_num = 6;
				p_imgnum = 25;

				player_state = PlayerState::PANIM;
				tuto_cnt = 0;
			}
		}
		else {
			location.x += 4;
			world.x += 4;

			TutoWalkAnim();
		}

		break;
	case 6:
		//チュートリアル終anim
		if (tuto_cnt++>60)
		{
			p_imgnum = 27;

		}else if(tuto_cnt>30) {
			p_imgnum = 26;

		}



		if (tuto_cnt > 100)
		{
			move_x = 0;
			start_flg = true;
			attacking = false;
			is_atk_putout = false;
			p_atk_imgnum = 0;
			attack_cnt = 0;
			anim_cnt = 0;
			atk_cnt_timer = 0;
			player_state = PlayerState::NOMAL;
		}
		break;
	}


	// 端に来たら跳ね返る
	if (world.x + width / 2 > FIELD_WIDTH)
	{
		world.x = FIELD_WIDTH - 20;
		StopSoundMem(op_run_sound);

	}
	else if (world.x - width / 2 < 0) {
		world.x = width / 2;
		StopSoundMem(op_run_sound);

	}

	//HitMapChip(gamemain);


}

void Player::RespawnAnimUpdate()
{
	death_anim_cnt++;
	switch (death_anim_cnt)
	{
	case 1:
		player_state = PlayerState::DEATH;
		p_imgnum= 49;
		break;
	case 40:
		player_state = PlayerState::PANIM;
		p_imgnum = 29;
		break;
	case 80:
		p_imgnum = 27;
		player_state = PlayerState::NOMAL;
		death_anim_cnt = 0;
		start_flg = true;
		break;
	}

	
}

// エンド画面用アニメーション更新処理
void Player::EndAnimUpdate()
{
	if (world.y != 50.0f)
	{
		world.y = 50.0f;
	}

	if (end_anim_cnt < 29)
	{
		end_anim_cnt++;
		end_img_num = end_anim_cnt / 10;
	}
	else
	{
		end_anim_cnt = 0;
	}

	// 右に移動
	world.x += 6.0f;
}

// エンド画面用アニメーション描画処理
void Player::EndAnimDraw() const
{
	// プレイヤーが袋を持って走る画像
	DrawRotaGraph((int)world.x, (int)world.y, 10.0, 0.0, player_end_img[end_img_num], TRUE, direction);
}

// エンドクレジット画面用アニメーション更新処理
void Player::EndCreditsAnimUpdate()
{
	if (credits_anim_cnt < 2700)
	{
		credits_timer++;

		// クレジット画面でのプレイヤー移動処理
		PlayerMoveEndCredits();
	}
	
	if (credits_timer < 2150)
	{
		// コサックダンスアニメーション
		DanceAnim();
	}
	else if(credits_timer >= 2250 && credits_timer < 2550)
	{
		// 拍手アニメーション
		ApplauseAnim();
	}
	else if(credits_timer >= 2550)
	{
		if (cracker_anim_cnt < 50)
		{
			// クラッカーアニメーション
			CrackerAnim();
		}

		if (credits_img_num >= 3)
		{
			// リボンアニメーション
			RibbonAnim();
		}
	}

	if (push_b_flg == true)
	{
		// Bボタンでシーンを変えるときのアニメーション
		ChangeSceneAnim();

	}
}

// エンドクレジット画面用アニメーション描画処理
void Player::EndCreditsAnimDraw() const
{
	//int ax, ay;
	//GetMousePoint(&ax, &ay);
	//DrawFormatString(1000, 10, 0xffff00, "%d,%d", ax, ay);

	if (credits_timer < 2250)
	{
		// コサックダンス画像
		DrawRotaGraph((int)world.x, (int)world.y, 1.0, 0.0, player_credits_img[credits_img_num], TRUE, direction);
	}
	else if(credits_timer < 2550)
	{
		// 拍手画像
		DrawRotaGraph((int)world.x, (int)world.y, 1.0, 0.0, applause_img[credits_img_num], TRUE, direction);
	}
	else
	{
		if (credits_img_num >= 3)
		{
			// クラッカーのリボン画像
			DrawRotaGraph(ribbon_x, ribbon_y, 1.5, 0.0, ribbon_img[ribbon_img_num], TRUE, direction);
		}

		if (push_b_flg == true)
		{
			// プレイヤー歩行画像
			DrawRotaGraph((int)world.x, (int)world.y, 1.0, 0.0, player_img[p_imgnum], TRUE, FALSE);

			if (change_scene_cnt >= 240)
			{
				// つるはし画像
				DrawRotaGraph((int)world.x, (int)world.y, 1.0, 0.0, pickaxe_img[p_atk_imgnum], TRUE, FALSE);
			}
		}
		else
		{
			 // クラッカー画像
			DrawRotaGraph((int)world.x, (int)world.y, 1.0, 0.0, cracker_img[credits_img_num], TRUE, direction);
		}
	}
}

// クレジット画面でのプレイヤー移動処理
void Player::PlayerMoveEndCredits()
{
	if (credits_timer < 400)
	{
		world.x += 1.0f;
	}
	else if (credits_timer >= 500 && credits_timer < 600)
	{
		world.x -= 0.5f;
		world.y -= 0.7f;

		// 左向きの画像に変更
		facing_left_flg = true;
	}
	else if (credits_timer >= 750 && credits_timer < 800)
	{
		world.x += 0.7f;

		// 右向きの画像に変更
		facing_left_flg = false;
	}
	else if (credits_timer >= 850 && credits_timer < 1100)
	{
		world.x += 1.2f;
		world.y -= 1.0f;
	}
	else if (credits_timer >= 1100 && credits_timer < 1300)
	{
		world.x += 1.0f;
		world.y -= 1.0f;

		// 左向きの画像に変更
		facing_left_flg = true;
	}
	else if (credits_timer >= 1400 && credits_timer < 1700)
	{
		world.x += 1.2f;
		world.y += 1.0f;

		// 右向きの画像に変更
		facing_left_flg = false;
	}
	else if (credits_timer >= 1800 && credits_timer < 1950)
	{
		world.x -= 0.6f;
		world.y += 1.0f;

		// 左向きの画像に変更
		facing_left_flg = true;
	}
	else if (credits_timer >= 2500 && credits_timer < 2550)
	{
		world.x -= 1.0f;
		world.y -= 0.5f;
	}
}

// Bボタンでシーンを変えるときのアニメーション
void Player::ChangeSceneAnim()
{
	if (change_scene_cnt < 300)
	{
		change_scene_cnt++;
	}
	else
	{
		// アニメーションが終わったらシーンをタイトルに変更
		change_to_title_flg = true;
	}

	if (change_scene_cnt < 200)
	{
		dash_anim_cnt++;

		if (dash_anim_cnt < 150)
		{
			// push_bに向かって走る
			world.x -= 3.0f;
		}
		else
		{
			world.x -= 3.0f;
			world.y += 1.4f;
		}

		if (credits_walk_cnt >= 30)
		{
			walk_cnt_up_flg = false;
		}
		if (credits_walk_cnt <= 0)
		{
			walk_cnt_up_flg = true;
		}

		if (walk_cnt_up_flg == true)
		{
			credits_walk_cnt++;
		}
		else
		{
			credits_walk_cnt--;
		}

		// プレイヤー歩行アニメーション
		if (credits_walk_cnt < 29)
		{
			p_imgnum = credits_walk_cnt / 10 + 57;
			if (p_imgnum == 59)
			{
				// 走る音
				if (CheckSoundMem(op_run_sound) == FALSE)
				{
					PlaySoundMem(op_run_sound, DX_PLAYTYPE_BACK);
				}
			}
		}
		else
		{
			credits_walk_cnt = 0;
		}
	}
	else if(change_scene_cnt < 240)
	{
		// 右向きの直立画像
		p_imgnum = 27;
	}
	else
	{
		// つるはし攻撃アニメーション
		if (p_imgnum != 41)
		{
			p_imgnum = (change_scene_cnt - 240) / 5 + 38;
			p_atk_imgnum = (change_scene_cnt - 240) / 5;
		}

		if (p_atk_imgnum == 2)
		{
			if (CheckSoundMem(atk_sound) == FALSE)
			{
				// つるはしse
				PlaySoundMem(atk_sound, DX_PLAYTYPE_BACK);
			}
			anim_end_flg = true;
		}
	}

}

// コサックダンスアニメーション
void Player::DanceAnim()
{
	if (credits_anim_cnt < 40)
	{
		credits_anim_cnt++;
	}
	else
	{
		credits_anim_cnt = 0;
	}

	// 10fごとに画像切り替え
	credits_img_num = credits_anim_cnt / 10;

	if (facing_left_flg == true)
	{
		// 左向き画像
		if (credits_img_num > 3)
		{
			credits_img_num = 3;
		}
	}
	else
	{
		// 右向き画像
		credits_img_num += 4;
		if (credits_img_num > 7)
		{
			credits_img_num = 7;
		}
	}
}

// 拍手アニメーション
void Player::ApplauseAnim()
{
	if (credits_anim_cnt < 12)
	{
		credits_anim_cnt++;
	}
	else
	{
		credits_anim_cnt = 0;
	}

	// 5fごとに画像切り替え
	credits_img_num = credits_anim_cnt / 3;

	if (credits_img_num > 3)
	{
		credits_img_num = 3;
	}
}

// クラッカーアニメーション
void Player::CrackerAnim()
{
	cracker_anim_cnt++;

	// 10fごとに画像切り替え
	credits_img_num = cracker_anim_cnt / 10;

	if (credits_img_num > 4)
	{
		credits_img_num = 4;
	}
}

// リボンアニメーション
void Player::RibbonAnim()
{
	if (set_ribbon_pos_flg == false)
	{
		// リボンの座標を設定する
		ribbon_x = (int)world.x - 150;
		ribbon_y = (int)world.y;
		set_ribbon_pos_flg = true;
	}

	if (ribbon_anim_cnt < 50)
	{
		ribbon_anim_cnt++;

		// 10fごとに画像切り替え
		ribbon_img_num = ribbon_anim_cnt / 10;

		if (ribbon_img_num > 4)
		{
			ribbon_img_num = 4;
		}
	}
}

// 檻の端にプレイヤーがいるのか調べる
void Player::CheckEdgeCage(float cage_x)
{
	if (cage_x >= location.x - width / 2)
	{
		world.x = world.x - move_x;
	}
}



void Player::HitMapChip(GameMainScene* gamemain)
{
	//マップチップとの当たり判定
	if (direction == 0 && gamemain->CollisionCharaRight(half_width, half_height, world))
	{
		//食い込んだので元の位置に戻す
		world.x = curent_x;
	}
	else if (direction == 1 && gamemain->CollisionCharaLeft(half_width, half_height, world))
	{
		world.x = curent_x;
	}

	if (gamemain->CollisionCharaTop(half_width, half_height, world))
	{
		//頭がぶつかったら押し返す
		SinkCheckTop(gamemain, world.x, world.y-half_height-1.0f);
		stop_up_flg = true;
	}
	else
	{
		if (geyser_hit_flg == true)
		{
			stop_up_flg = false;
		}
	}

	//移動前のｘ座標を渡す
	if (gamemain->CollisionCharaBottom(half_width, half_height, curent_x, world.y))
	{
		floorblock_hit_flg = true;
		speed = 0.0f;
		if (fall_flg == true)
		{
			move_x = 0.0f;
		}
		fall_flg = false;
		stop_up_flg = false;
		//くい込んでたら上に押し出す
		if (direction == 0) {
			SinkCheck(gamemain, curent_x + half_width, world.y + half_height - 1.0f);
		}
		else {
			SinkCheck(gamemain, curent_x - half_width, world.y + half_height - 1.0f);

		}
	}
	else
	{
		floorblock_hit_flg = false;

		if (lift_hit_flg != false)return;
		if (geyser_hit_flg != false)return;
		if (magma_hit_flg != false)return;
		if (fallingfloor_hit_flg != false)return;
		fall_flg = true;
	}

	

}

void Player::SinkCheck(GameMainScene* gamemain,float set_x, float set_y)
{
	int col = (int)set_x / BLOCKSIZE;
	int row = (int)set_y / BLOCKSIZE;

	if (gamemain->GetMapIo()->GetMapData(row, col) == 1) {
		float block_x = (float)col* BLOCKSIZE;
		float block_y = (float)row * BLOCKSIZE;

		//上の座標を取る
		block_x = block_x - (float)BLOCKSIZE;
		//block_y = block_y - (float)BLOCKSIZE;

		float sink_y = set_y - block_y;
		//もしめりこんでいたら
		if (sink_y > 0) {
			//めり込んでいる分上にあげる
			world.y = world.y - sink_y;
		}
	}


}

void Player::SinkCheckTop(GameMainScene* gamemain, float set_x, float set_y)
{
	int col = (int)set_x / BLOCKSIZE;
	int row = (int)set_y / BLOCKSIZE;

	if (gamemain->GetMapIo()->GetMapData(row, col) == 1) {
		float block_x = (float)col * BLOCKSIZE;
		float block_y = (float)row * BLOCKSIZE;


		//自分の上の座標

		float sink_y = (block_y+BLOCKSIZE) - set_y;
		//もしめりこんでいたら
		if (sink_y > 0)
		{
			//めり込んでいる分下に
			world.y = world.y + sink_y;
		}
	}
}

void Player::SinkCheckObject(float set_y)
{
	if (stop_up_flg == false)
	{
		float sink_y = (world.y + half_height) - set_y;
		if (sink_y > 0)
		{
			world.y = world.y - sink_y;
		}
	}
}

void Player::SinkCheckX(float set_x,float set_half_width)
{
	if (direction == 0)
	{
		int col = ((int)set_x - (int)set_half_width) / BLOCKSIZE;
		float block_x = (float)col * BLOCKSIZE;
		float sink_x = fabs(block_x - set_x);

		if (sink_x > 0)
		{
			//めり込んでいる分上にあげる
			world.x = curent_x;
		}
	}
	else
	{
		int col = ((int)set_x + (int)set_half_width) / BLOCKSIZE;
		float block_x = (float)col * BLOCKSIZE;
		float sink_x = fabs(world.x - block_x);

		if (sink_x > 0) 
		{
			world.x = curent_x;
		}
	}
	


}

void Player::PushUpPlayer(float set_upper)
{
	if (stop_up_flg == false)
	{
		//噴き出した水の頭のｙよりプレイヤーの足が下に居たら
		if (set_upper + 6.0f < GetVertex().lower_y)
		{
			world.y = world.y - 3.0f;
		}
	}
}
