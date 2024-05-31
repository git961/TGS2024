#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>

Player::Player()
{
	//画像読込
	player_img[0] = LoadGraph("images/Player/player.png");
	player_img[1] = LoadGraph("images/Player/damage.png");
	player_img[2] = LoadGraph("images/Player/bagopen.png");
	player_img[3] = LoadGraph("images/Player/bagopen2.png");
	player_img[4] = LoadGraph("images/Player/plookup.png");
	player_img[5] = LoadGraph("images/Player/wakeup.png");
	LoadDivGraph("images/Player/player_walk.png", 4, 4, 1, 170, 170, player_walk_img);
	LoadDivGraph("images/Player/player_ase.png", 4, 4, 1, 170, 170, player_ase_img);
	LoadDivGraph("images/Player/p_death.png", 4, 4, 1, 170, 170, player_death_img);
	LoadDivGraph("images/Player/p_attack.png", 4, 4, 1, 170, 170, player_attack_img);
	LoadDivGraph("images/Player/throw.png", 3, 3, 1, 170, 170, player_throw_img);
	LoadDivGraph("images/Player/pickaxe.png", 4, 4, 1, 170, 170, pickaxe_img);
	LoadDivGraph("images/Player/soil_effect.png", 2, 2, 1, 170, 170, soil_effect);

	atk_sound = LoadSoundMem("sounds/Attack.mp3");

	img_down = 15;

	reset_timer = 0;
	p_imgnum = 0;
	p_atk_imgnum = 0;
	effect_num = 0;
	walk_num = 0;

	anim_cnt = 0;

	world.x = 0;
	world.y = 600.0f-30;

	location.x = 0;
	location.y = 600.0f-30;

	old_worldx = world.x;

	//体力
	hp = 50;

	//幅と座標
	width = 50;
	height = 100;

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

	//ダイナマイトに使用
	atk_dynamite = false;
	dyna_throw_num = 0;
	dyna_anmcnt = 0;

	dyna_stock_num = 5;
	dyna_stock_cnt = 0;


	is_atk_putout = false;

	player_state = NOMAL;
	is_hit_enemy = false;

	//被弾点滅
	hit_damage = false;
	flash_start = false;
	flash_flg = false;
	flash_cnt = 0;

	death_anim_cnt = 0;
	death_num = 0;
	death_flg = false;

	op_num = 2;
	op_cnt = 0;
	tuto_anim_flg=false;
	tuto_atk_flg = false;
	tuto_num = 0;
	tuto_cnt=0;
	tuto_ui_num = 0;
	rock_break_flg = false;
	rock_cnt = 0;
	hit_rock_flg = false;
	walk_stop_flg = false;
	tuto_anim_dynaflg = false;
}

Player::~Player()
{
}

void Player::Update(GameMainScene* gamemain)
{
	//プレイヤー状態によってスイッチで変えよう


	input.InputUpdate();
	

	switch (player_state)
	{
	case DEATH:
		death_anim_cnt++;
		switch (death_anim_cnt)
		{
		case 0:
			death_num = 0;
			break;
		case 5:
			death_num = 1;
			break;
		case 15:
			death_num = 2;
			break;
		case 20:
			death_num = 3;
			break;
		case 25:
			death_flg = true;
			break;
		default:
			break;
		}
		break;
	case DYNAMITE:

		switch (dyna_anmcnt)
		{
		case 1:
			dyna_stock_num-=1;
			dyna_throw_num = 0;
			break;
		case 5:
			dyna_throw_num = 1;
			break;
		case 10:
			dyna_throw_num = 2;
			atk_dynamite = true;
			break;
		case 15:
			dyna_anmcnt = 0;
			dyna_throw_num = 0;
			player_state = NOMAL;
			break;
		default:
			break;
		}
		dyna_anmcnt++;

		break;
	case HITDAMAGE:

		if ((unsigned)move_x > 0) {
			move_x *= 0.9;
			location.x += move_x;
			world.x += move_x;
		}
		else
		{
			player_state = NOMAL;
			hit_damage = false;
			flash_start = true;
		}

		break;
	case ATTACK:
	case WALK:
	case NOMAL:
		PlayerAttack();

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
			world.x = FIELD_WIDTH - 20;

		}
		else if (world.x - width / 2 < 0) {
			world.x = width / 2;
		}

		//敵からダメージを食らったら
		if (hit_damage == true)
		{
			player_state = HITDAMAGE;

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
		if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
		{
			//if (CheckSoundMem(atk_sound) == TRUE)
			//{
			//	StopSoundMem(atk_sound);
			//}

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
			wait_flg = false;
		}

		if (dyna_stock_num > 0)
		{
			//ダイナマイト攻撃
			if (input.CheckBtn(XINPUT_BUTTON_Y) == TRUE || CheckHitKey(KEY_INPUT_S) == TRUE)
			{
				player_state = DYNAMITE;
			}
		}


		break;
	default:
		break;
	}
	
	if (hp <= 0) {
		player_state = DEATH;
	}

	
#ifdef DEBUG

	#endif // DEBUG
	
}

void Player::Draw() const
{


	//DrawBoxAA(location.x - width/2, location.y - height/2, location.x + width / 2, location.y + height / 2, 0xffffff,true);
	//DrawCircleAA(location.x, location.y, 1, 0xff00ff, true);


	//プレイヤー画像表示
	//DrawRotaGraph(location.x, location.y-25, 1, 0, player_img[p_imgnum], TRUE, direction);

	if (flash_flg == true)
	{

		//ダメージを受けたら、薄くなったり、元に戻ったりの点滅をして
		//数秒たったら戻る
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		
	}
	else if(flash_flg==false) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}
		switch (player_state)
		{

		case NOMAL:
			DrawRotaGraph(location.x, location.y - img_down, 1, 0, player_img[0], TRUE, direction);
			//DrawFormatString(location.x, location.y - 80, 0x000000, "nomal");
			break;
		case ATTACK:
			DrawRotaGraph(location.x, location.y - img_down, 1, 0, player_attack_img[p_imgnum + p_atk_imgnum], TRUE, direction);
			//DrawFormatString(location.x, location.y - 80, 0x000000, "attack");

			if (is_hit_enemy == true)
			{
				if (p_imgnum > 2)
				{
					DrawRotaGraph(location.x, location.y - img_down, 1, 0, pickaxe_img[2 + p_atk_imgnum], TRUE, direction);
				}
				else
				{
					DrawRotaGraph(location.x, location.y - img_down, 1, 0, pickaxe_img[p_imgnum + p_atk_imgnum], TRUE, direction);
				}
			}
			else {

				DrawRotaGraph(location.x, location.y - img_down, 1, 0, pickaxe_img[p_imgnum + p_atk_imgnum], TRUE, direction);
				if (p_imgnum > 2)
				{
					//DrawRotaGraph(location.x, location.y - img_down, 1, 0, effect_img[effect_num], TRUE, direction);
					DrawRotaGraph(location.x, location.y - img_down, 1, 0, soil_effect[effect_num], TRUE, direction);
				}
			}

			break;
		case WALK:
			DrawRotaGraph(location.x, location.y-img_down, 1, 0, player_walk_img[walk_num], TRUE, direction);
			//DrawFormatString(location.x, location.y - 80, 0x000000, "walk");

			break;
		case HITDAMAGE:
			DrawRotaGraph(location.x, location.y - img_down, 1, 0, player_img[1], TRUE, direction);
			//DrawFormatString(location.x, location.y - 80, 0x000000, "hitdamage");
			break;
		case DYNAMITE:
			DrawRotaGraph(location.x, location.y - img_down, 1, 0, player_throw_img[dyna_throw_num], TRUE, direction);
			break;
		case DEATH:
			DrawRotaGraph(location.x, location.y-img_down, 1, 0, player_death_img[death_num], TRUE, direction);
			//DrawFormatString(location.x, location.y - 80, 0x000000, "death");
			break;
		case PANIM:
			DrawRotaGraph(location.x, location.y - img_down, 1, 0, player_img[op_num], TRUE, direction);
			break;
		case ASE:
			DrawRotaGraph(location.x, location.y - img_down, 1, 0, player_ase_img[walk_num], TRUE, direction);
			break;
		default:
			break;
		}
	
		//if (tuto_atk_flg == true)
		//{
		//	DrawFormatString(location.x, location.y-20, 0xffffff, "PUSH:B!!!");

		//}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

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

	////DrawFormatString(100, 150, 0xffffff, "location.x: %f",location.x);


#endif // DEBUG
}

void Player::PlayerMove()
{

	//攻撃中じゃなかったらプレイヤー移動
	//右移動
	
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_RIGHT) == TRUE||input.GetPadThumbLX()>=32000) {

		if (move_x <= 4)
		{
			move_x += 1;
		}

		direction = 0;

		if (player_state != ATTACK)
		{
			player_state = WALK;
		}
	}

	//左移動
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_LEFT) == TRUE||input.GetPadThumbLX() <= -32000) {

		if (move_x >= -4)
		{
			move_x -= 1;
		}

		direction = 1;

		if (player_state != ATTACK)
		{
			player_state = WALK;
		}
	}

	//右左移動してない時
	//十字キーの入力がなかったら
	if (input.LongPressBtn(XINPUT_BUTTON_DPAD_RIGHT) != TRUE && input.LongPressBtn(XINPUT_BUTTON_DPAD_LEFT) != TRUE)
	{
		//左スティックからの入力が無かったら
		if (input.GetPadThumbLX() >= -32000 && input.GetPadThumbLX() <= 32000)
		{
			move_x *= 0.9;
			if (player_state != ATTACK)
			{
				player_state = NOMAL;
			}
		}
	}


	location.x += move_x;
	world.x += move_x;
	

}

void Player::PlayerAttack()
{



	if (attacking == true)
	{
		if (attack_cnt == 1)
		{
			p_atk_imgnum = 4;
			//2段
			switch (anim_cnt)
			{
			case 0:
				p_imgnum = 0;
				break;
			case 10:
				p_imgnum = 1;
				break;
			case 13:
				is_atk_putout = true;
				effect_num = 0;
				p_imgnum = 2;
				break;
			case 16:
				effect_num = 1;
				p_imgnum = 3;
				break;
			}

		}
		else if (attack_cnt == 2)
		{
			p_atk_imgnum = 8;
			//初段
			switch (anim_cnt)
			{
			case 0:
				p_imgnum = 0;
				break;
			case 12:
				p_imgnum = 1;
				break;
			case 15:
				is_atk_putout = true;
				effect_num = 0;
				p_imgnum = 2;
				break;
			case 18:
				effect_num = 1;
				p_imgnum = 3;
				break;
			}

		}
		else {
			p_atk_imgnum = 0;
			//初段
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
	/*		if (atk_cnt_timer < 20)
			{
				if (input.CheckBtn(XINPUT_BUTTON_X) == TRUE)
				{
					color13 = 0x000000;
					next_attackflg = true;
				}
			}*/
		}
		//20フレーム回ったら
		if (atk_cnt_timer++ > 20)
		{
			if (CheckSoundMem(atk_sound) == TRUE)
			{
				StopSoundMem(atk_sound);
			}


			if (next_attackflg == false || attack_cnt >= 2)
			{
				attack_cnt = 0;
				anim_cnt = 0;
				atk_cnt_timer = 0;
				is_atk_putout = false;
				next_attackflg = false;
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
				is_atk_putout = false;
				attacking = false;
				next_attackflg = false;

			}
		}
	}


}


void Player::OpAnimUpdate(AnimScene* anim_scene,int set_case)
{

	switch (set_case)
	{
	case 0:

		world.x = -50;
		location.x = -50;

		if (CheckSoundMem(atk_sound) == FALSE)
		{
			PlaySoundMem(atk_sound, DX_PLAYTYPE_BACK);
		}

		while (CheckSoundMem(atk_sound) == 1)
		{

		}

		if (CheckSoundMem(atk_sound) == FALSE)
		{
			PlaySoundMem(atk_sound, DX_PLAYTYPE_BACK);
		}

		while (CheckSoundMem(atk_sound) == 1)
		{

		}

		anim_scene->SetAnimScene(1);


	break;
	case 2:
		//画面の中心まで歩いてくる
		if (640 > world.x) {
			player_state = WALK;
			location.x += 1;
			world.x += 1;

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
		else {
			if (op_cnt++ >120)
			{
				player_state = PANIM;
				if (op_cnt++ > 140)
				{
					anim_scene->SetAnimScene(3);
					op_cnt = 0;
				}
			}
			else
			{
				player_state = NOMAL;
			}
		}
		
		
	break;
	case 4:
		op_num = 3;

		break;
	case 5:
		world.x = 600;
		location.x = 600;
		player_state =PANIM;
		op_num = 4;
		op_cnt++;
		switch (op_cnt)
		{
		case 60:
			direction = 1;
			break;
		case 120:
			direction = 0;
			break;
		case 160:
			anim_scene->SetShakeFlg(false);
			break;
		case 180:
			direction = 1;
			anim_scene->SetExc(true);
			break;
		case 240:
			anim_scene->SetExc(false);
			anim_scene->SetRun(true);
			direction = 0;
			break;
		case 300:
			anim_scene->SetAnimScene(6);
			op_cnt = 0;
			break;
		}

		break;
	case 6:
		
		if (1400> world.x) {
			player_state = ASE;
			location.x += 1;
			world.x += 1;

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

		break;
	}
	


}

void Player::TutorialAnimUpdate()
{
	input.InputUpdate();

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

				player_state = ASE;
				location.x += 3;
				world.x += 3;

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

			if (tuto_anim_flg == true) {
				death_anim_cnt++;
				switch (death_anim_cnt)
				{
				case 1:
					player_state = DEATH;
					world.x += -10;
					location.x += -10;
					death_num = 0;
					break;
				case 5:
					world.x += -10;
					location.x += -10;
					death_num = 1;
					break;
				case 15:
					death_num = 2;
					break;
				case 20:
					death_num = 3;
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
					player_state = PANIM;
					op_num = 5;
					break;
				case 150:
					player_state = ATTACK;
					tuto_atk_flg = true;
					tuto_ui_num = 1;
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
					player_state = NOMAL;
				
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
					wait_flg = false;
				}

				PlayerAttack();

			}
	
		


		}
	break;
	case 1:

		if (world.x > 1100)
		{
			tuto_num = 2;
		}

		SetVertex();

		//つるはし攻撃
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
			wait_flg = false;
		}
		PlayerAttack();


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

	break;
	case 2:
		//袋に近づいて開ける
		if (walk_stop_flg == true)
		{
			player_state = PANIM;
			op_num = 2;
			if (tuto_cnt++ > 60)
			{
				tuto_ui_num = 2;
				walk_stop_flg = false;
				tuto_num = 3;
			}
		}
		else{
			location.x += 1;
			world.x += 1;

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

		}

		break;
	case 3:
		if (walk_stop_flg == true)
		{
			tuto_ui_num = 3;

			if (player_state!=DYNAMITE)
			{
				//ダイナマイト攻撃
				if (input.CheckBtn(XINPUT_BUTTON_Y) == TRUE || CheckHitKey(KEY_INPUT_S) == TRUE)
				{
					player_state = DYNAMITE;
					tuto_anim_dynaflg = true;
				}
			}

			if (player_state == DYNAMITE)
			{
				tuto_ui_num = 0;

				move_x = 0;
				switch (dyna_anmcnt)
				{
				case 1:
					dyna_stock_num -= 1;
					dyna_throw_num = 0;
					break;
				case 5:
					dyna_throw_num = 1;
					break;
				case 10:
					dyna_throw_num = 2;
					atk_dynamite = true;
					break;
				case 150:

					tuto_anim_dynaflg = false;
					break;
				case 200:
					dyna_anmcnt = 0;
					dyna_throw_num = 0;
					player_state = NOMAL;
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

		//そのまま歩いて行って、看板を見る　この先出口ですが危険！！

		SetVertex();

		//つるはし攻撃
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
			wait_flg = false;
		}
		PlayerAttack();


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

		break;
	}


	// 端に来たら跳ね返る
	if (world.x + width / 2 > FIELD_WIDTH)
	{
		world.x = FIELD_WIDTH - 20;

	}
	else if (world.x - width / 2 < 0) {
		world.x = width / 2;
	}

}
