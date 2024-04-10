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
	
	//Y‚¨‚µ‚½‚çUŒ‚
	if(input.CheckBtn(XINPUT_BUTTON_Y) == TRUE)
    {
		x = player->GetX();
		y = player->GetY();
		attack_flg = true;
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