#include "UIHP.h"

UIHP::UIHP(int set_hp)
{
	heart_img[0] = LoadGraph("images/UI/h.png");
	heart_img[1] = LoadGraph("images/UI/hf.png");
	player_hp = set_hp;
	heart_num = set_hp / 10;
	x = 70;
	y = 100;
}

UIHP::~UIHP()
{
}

void UIHP::Update(int set_hp)
{
	heart_num = set_hp / 10;

}

void UIHP::Draw() const
{
	for (int i = 0; i < heart_num; i++)
	{
		DrawRotaGraph(x+50*i, y, 1, 0, heart_img[0], TRUE, 0);

	}
}
