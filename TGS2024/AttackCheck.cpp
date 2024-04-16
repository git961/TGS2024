#include "AttackCheck.h"

AttackCheck::AttackCheck()
{
	width = 50;
	height = 40;
	location.x = 0;
	location.y = 0;
	attack_flg = false;
}

AttackCheck::~AttackCheck()
{
}

void AttackCheck::Update(GameMainScene* gamemain,Player* player)
{
	input.InputUpdate();
	
	//Yおしたら攻撃
	if(player->GetAttacking() == true)
    {
		//プレイヤーが右を向いてたら
		if (player->GetDirection() == 0)
		{
			location.x = player->GetLocation().x+40;
			location.y = player->GetLocation().y;
		}
		//プレイヤーが左を向いていたら
		if (player->GetDirection() == 1)
		{
			location.x = player->GetLocation().x-40;
			location.y = player->GetLocation().y;
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
		DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0x00ffff, false);
		DrawCircleAA(location.x, location.y, 1, 0xff00ff, true);

	}
}