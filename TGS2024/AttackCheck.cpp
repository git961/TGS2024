#include "AttackCheck.h"

AttackCheck::AttackCheck()
{
	width = 30;
	height = 30;
	x = 0;
	y = 0;
	attack_flg = false;
}

AttackCheck::~AttackCheck()
{
}

void AttackCheck::Update(GameMainScene* gamemain,Player* player)
{
	input.InputUpdate();
	
	//Y��������U��
	if(player->GetAttacking() == true)
    {
		//�v���C���[���E�������Ă���
		if (player->GetDirection() == 0)
		{
			x = player->GetX()+30;
			y = player->GetY();
		}
		//�v���C���[�����������Ă�����
		if (player->GetDirection() == 1)
		{
			x = player->GetX()-30;
			y = player->GetY();
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
		DrawBoxAA(x - width / 2, y - height / 2, x + width / 2, y + height / 2, 0x00ffff, true);
		DrawCircleAA(x, y, 1, 0xff00ff, true);

	}
}