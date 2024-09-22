#include "AttackCheck.h"

AttackCheck::AttackCheck()
{
	width = 70.0f;
	height = 70.0f;
	location.x = 0.0f;
	location.y = 0.0f;
	world.x = 0.0f;
	world.y = 0.0f;
	attack_flg = false;
	shift_x = 60.0f;
	shift_y = 20.0f;

}

AttackCheck::~AttackCheck()
{
}

void AttackCheck::Update(GameMainScene* gamemain,Player* player)
{
	input.InputUpdate();
	
	//Bおしたら攻撃
	if(player->GetAttacking() == true)
    {

		//プレイヤーが右を向いてたら
		if (player->GetDirection() == 0)
		{
			world.x = player->GetWorldLocation().x + shift_x;
			world.y = player->GetWorldLocation().y + shift_y;
			location.x = player->GetLocation().x + shift_x;
			location.y = player->GetLocation().y + shift_y;
		}
		//プレイヤーが左を向いていたら
		if (player->GetDirection() == 1)
		{
			world.x = player->GetWorldLocation().x - shift_x;
			world.y = player->GetWorldLocation().y + shift_y;
			location.x = player->GetLocation().x - shift_x;
			location.y = player->GetLocation().y + shift_y;
		}

		//デバック攻撃範囲表示用
		attack_flg = true;
	}
	else
	{
		attack_flg = false;
	}


	if (player->GetAtkDynamite() == true)
	{
		//プレイヤーが右を向いてたら
		if (player->GetDirection() == 0)
		{
			world.x = player->GetWorldLocation().x + 30;
			world.y = player->GetWorldLocation().y;
		}
		//プレイヤーが左を向いていたら
		if (player->GetDirection() == 1)
		{
			world.x = player->GetWorldLocation().x - 30;
			world.y = player->GetWorldLocation().y;

		}
	}

}

void AttackCheck::Draw() const
{
		//DrawBox(location.x - width / 2,location.y - height / 2,location.x + width / 2, location.y + height / 2, 0x00ffff, false);
		//DrawCircleAA(location.x, location.y, 2, 0xff00ff, true);
}