#include "UI.h"

UI::UI(int set_hp)
{
	heart_img[0] = LoadGraph("images/UI/heart.png");
	p_img[0] = LoadGraph("images/UI/player.png");
	player_hp = set_hp;
	heart_num = set_hp / 10;
	x = 70;
	y = 100;
}

UI::~UI()
{
}

void UI::Update(int set_hp)
{
	heart_num = set_hp / 10;

}

void UI::Draw() const
{
	for (int i = 0; i < heart_num; i++)
	{
		DrawRotaGraph(x+50*i, y, 1, 0, heart_img[0], TRUE, 0);

	}
}
