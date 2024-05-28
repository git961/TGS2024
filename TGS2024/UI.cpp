#include "UI.h"

UI::UI(int set_hp, int set_dyna_num)
{
	heart_img = LoadGraph("images/UI/heart.png");
	p_img = LoadGraph("images/UI/player.png");
	score_img = LoadGraph("images/UI/score_Icon.png");
	dyna_img= LoadGraph("images/UI/dynamite.png");
	btnB_img= LoadGraph("images/UI/buttonB.png");
	btnY_img= LoadGraph("images/UI/buttonY.png");
	player_hp = set_hp;
	heart_num = set_hp / 10;
	dyna_num=set_dyna_num;
	x = 100;
	y = 40;
}

UI::~UI()
{
}

void UI::Update(int set_hp,int set_dyna_num)
{
	heart_num = set_hp / 10;
	dyna_num = set_dyna_num;
}

void UI::Draw() const
{
	int ax, ay;
	GetMousePoint(&ax, &ay);
	DrawFormatString(1000, 10, 0xffff00, "%d,%d", ax, ay);

	DrawRotaGraph(620, 30, 1, 0, score_img, TRUE, 0);
	//DrawRotaGraph(550, 675, 1, 0, btnB_img, TRUE, 0);
	//DrawRotaGraph(650, 675, 1, 0, btnY_img, TRUE, 0);
	// 	//DrawRotaGraph(1130, 675, 1, 0, btnB_img, TRUE, 0);
	//DrawRotaGraph(1200, 675, 1, 0, btnY_img, TRUE, 0);
	//DrawRotaGraph(1120, 30, 1, 0, score_img, TRUE, 0);
	DrawRotaGraph(140, y, 1, 0, p_img, TRUE, 0);

	for (int i = 0; i < heart_num; i++)
	{
		DrawRotaGraph(x+35*i, y, 1, 0, heart_img, TRUE, 0);
	}
	for (int i = 0; i < dyna_num; i++)
	{
		DrawRotaGraph(32+35 * i, y+64, 1, 0, dyna_img, TRUE, 0);
	}
}