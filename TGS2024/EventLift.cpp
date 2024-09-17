#include "EventLift.h"

EventLift::EventLift(float set_x, float set_y)
{
	switch_object = new Switch(set_x, set_y);
	switch_object->SetEventFlg(true);
	lift_img = LoadGraph("images/Stage/Gimmick/Lift.png");
	LoadDivGraph("images/Stage/Gimmick/spear.png", 4, 4, 1, 13, 80, spear_img);
	shift_y = 25.0f;
	world.x = set_x;
	world.y = set_y + shift_y;
	location.x = set_x;
	location.y = set_y;
	move_y = 5.0f;

	anim_state = AnimState::None;

	up_max_y = 200;
	down_max_y = world.y;
	screen_position_x = 0.0f;
	screen_position_y = 0.0f;

	width = 192.0f;
	height = 11.0f;

	check_inside_x = width;

	canmove_flg = false;
	down_flg = false;
	anim_start_flg = false;
	anim_cnt = 0;
	img_num = 0;
	shift_img_y = 12.0f;
	spear_num = 0;
	player_anim_num = 0;
	anim_end_flg = false;
}

EventLift::~EventLift()
{
	delete switch_object;
	DeleteGraph(lift_img);
}

void EventLift::Update(AttackCheck* ac, Player* player)
{

	switch_object->SetLocalPosition(screen_position_x, screen_position_y);

	switch (anim_state)
	{
	case AnimState::None:
		if (anim_start_flg == true)
		{
			anim_state = AnimState::GetOn;
		}
		break;
	case AnimState::GetOn:
		player->LiftEvent(player_anim_num);
		//リフトに乗ってスイッチにあたる
		if (switch_object != nullptr)
		{
			//つるはしとボタンが当たってるかのチェック
			if (switch_object->HitCheck(player->GetWorldLocation(), player->GetWidth(), player->GetHeight()) == true)
			{
				switch_object->SetEventFlg(true);
				player_anim_num = 1;
				anim_state = AnimState::BeTrapped;
			}
			switch_object->Update();
		}
		break;
	case AnimState::BeTrapped:
		player->LiftEvent(player_anim_num);
		DownEventAnim();
		break;
	case AnimState::Fall:
		player_anim_num = 2;
		player->SetY(world.y);
		player->LiftEvent(player_anim_num);
		if (world.y < 2850.f)
		{
			world.y += 20.0f;
		}
		else
		{
			anim_state = AnimState::Clash;
		}
		break;
	case AnimState::Clash:
		player_anim_num = 3;
		player->LiftEvent(player_anim_num);
		if (player->GetState() != 8) {
			anim_state = AnimState::End;
		}
		break;
	case AnimState::End:
		anim_end_flg = true;
		break;
	default:
		break;
	}

	
}

void EventLift::Draw() const
{
	DrawRotaGraph((int)location.x-90, (int)location.y -35.0f, 1, 0, spear_img[spear_num], TRUE);
	DrawRotaGraph((int)location.x+90, (int)location.y - 35.0f, 1, 0, spear_img[spear_num], TRUE);
	DrawRotaGraph((int)location.x, (int)location.y - shift_img_y, 1, 0, lift_img, TRUE);

	if (switch_object != nullptr)
	{
		switch_object->Draw();
	}
}

void EventLift::UpEventAnim()
{
}

void EventLift::DownEventAnim()
{
	anim_cnt++;
	switch (anim_cnt)
	{
	case 5:
		spear_num = 1;
		switch_object->SetImgNum(1);
		break;
	case 10:
		switch_object->SetImgNum(2);
		break;
	case 15:
		spear_num = 2;
		switch_object->SetImgNum(3);
		break;
	case 20:
		switch_object->SetImgNum(4);
		break;
	case 25:
		spear_num = 3;
		break;
	case 90:
		anim_cnt = 0;
		anim_state = AnimState::Fall;
		break;
	default:
		break;
	}
}
