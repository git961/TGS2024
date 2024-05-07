#include "AttackCheck.h"

AttackCheck::AttackCheck()
{
	width = 50;
	height = 40;
	location.x = 0;
	location.y = 0;
	world.x = 0;
	world.y = 0;
	attack_flg = false;

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
			world.x = player->GetWorldLocation().x+20;
			world.y = player->GetWorldLocation().y;
		}
		//プレイヤーが左を向いていたら
		if (player->GetDirection() == 1)
		{
			world.x = player->GetWorldLocation().x-20;
			world.y = player->GetWorldLocation().y;
		}
		attack_flg = true;
	}
	else
	{
		attack_flg = false;
	}

}

void AttackCheck::Draw() const
{
	if (attack_flg == true)
	{
		DrawBoxAA(world.x - width / 2, world.y - height / 2, world.x + width / 2, world.y + height / 2, 0x00ffff, false);
		DrawCircleAA(world.x, world.y, 1, 0xff00ff, true);

	}
}