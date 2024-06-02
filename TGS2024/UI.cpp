#include "UI.h"

UI::UI(int set_hp, int set_dyna_num)
{
	heart_img = LoadGraph("images/UI/heart.png");
	p_img = LoadGraph("images/UI/player.png");
	score_img = LoadGraph("images/UI/score_Icon.png");
	dyna_img= LoadGraph("images/UI/dynamite.png");
	LoadDivGraph("images/UI/UIB.png", 2, 2, 1, 128, 128, btnB_img);
	LoadDivGraph("images/UI/UIY.png", 2, 2, 1, 128, 128, btnY_img);
	tuto_backimg[0] = LoadGraph("images/Animscene/dynapic.png");
	tuto_backimg[1] = LoadGraph("images/Animscene/kanbananim.png");
	//tuto_backimg[2] = LoadGraph("images/Animscene/kanbananim2.png");
	//tuto_backimg[3] = LoadGraph("images/Animscene/kanbananim3.png");
	//tuto_backimg[4] = LoadGraph("images/Animscene/kanbananim4.png");
	//btnY_img= LoadGraph("images/UI/buttonY.png");
	player_hp = set_hp;
	heart_num = set_hp / 10;
	dyna_num=set_dyna_num;
	x = 100;
	y = 40;
	btn_num = 0;
	btn_cnt = 0;
	alpha = 0;
	alpha2 = 0;
	alpha_flg = false;
	kanban_anim_num = 1;
	i = 0;
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
	//DrawFormatString(1000, 10, 0xffff00, "%d,%d", ax, ay);

	DrawRotaGraph(620, 30, 1, 0, score_img, TRUE, 0);

	//if (player->GetTutoAtkFlg() == true)
	//{
	//	DrawRotaGraph(player->GetLocation().x, player->GetLocation().y-100, 1, 0, btnB_img, TRUE, 0);
	//}
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

void UI::UpdateTutorial(Player* player)
{
	switch (player->GetTutoUiNum())
	{
	case 0:
		break;
	case 1:
		if (btn_cnt++ > 10)
		{
			btn_num = 1;
		}

		if (btn_cnt > 20)
		{
			btn_cnt = 0;
			btn_num = 0;
		}

		break;
	case 2:
		if (alpha_flg == false)
		{
			if (alpha > 400)
			{
				alpha_flg = true;
			}
			else
			{
				alpha += 4;
			}
		}
		else {
			alpha -= 4;
			if (alpha < 0)
			{
				alpha_flg = false;
				player->SetMoveStop(true);
			}
		}
		break;
	case 3:
		if (btn_cnt++ > 10)
		{
			btn_num = 1;
		}

		if (btn_cnt > 20)
		{
			btn_cnt = 0;
			btn_num = 0;
		}

		break;
	case 4:
		alpha += 5;
		//i++;
		//switch (i)
		//{
		//case 100:
		//	kanban_anim_num = 2;
		//	break;
		//case 200:
		//	kanban_anim_num = 3;
		//	break;
		//case 300:
		//	kanban_anim_num = 4;
		//	break;
		//}

		break;

	}
}

void UI::DrawTutorial(Player* player) const
{
	switch (player->GetTutoUiNum())
	{
	case 0:
		break;
	case 1:
		DrawRotaGraph(player->GetLocation().x, player->GetLocation().y-100, 1, 0, btnB_img[btn_num], TRUE, 0);
		break;
	case 2:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(0, 0, tuto_backimg[0], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	case 3:
		DrawRotaGraph(player->GetLocation().x, player->GetLocation().y - 100, 1, 0, btnY_img[btn_num], TRUE, 0);
		break;
	case 4:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(0, 0, tuto_backimg[1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	}
}
