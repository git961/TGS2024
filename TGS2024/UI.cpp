#include "UI.h"

UI::UI(int set_hp, int set_dyna_num)
{
	LoadDivGraph("images/UI/heart.png", 6, 6, 1, 128, 128, heart_img);
	LoadDivGraph("images/UI/hpdeath.png", 2, 2, 1, 128, 128, heart_break_img);
	p_img = LoadGraph("images/UI/player.png");
	dyna_img= LoadGraph("images/UI/dynamite.png");
	LoadDivGraph("images/UI/UIB.png", 2, 2, 1, 128, 128, btnB_img);
	LoadDivGraph("images/UI/UIY.png", 2, 2, 1, 128, 128, btnY_img);
	LoadDivGraph("images/UI/walk_UI.png", 4, 4, 1, 128, 128, btnmove_img);
	tuto_backimg[0] = LoadGraph("images/Animscene/dynapic.png");
	LoadDivGraph("images/UI/num.png", 10, 10, 1, 64, 64, num_img);
	//tuto_backimg[2] = LoadGraph("images/Animscene/kanbananim2.png");
	//tuto_backimg[3] = LoadGraph("images/Animscene/kanbananim3.png");
	//tuto_backimg[4] = LoadGraph("images/Animscene/kanbananim4.png");
	//btnY_img= LoadGraph("images/UI/buttonY.png");
	heart_num = set_hp / 10;
	dyna_num=set_dyna_num;
	x = 100;
	y = 38;

	btn_num = 0;
	btn_cnt = 0;
	alpha = 0;
	alpha2 = 0;
	alpha_flg = false;
	kanban_anim_num = 1;
	i = 0;
	btn_flg = false;

	heart_anim_num = 0;
	anim_cnt=0;

	break_flg = false;
	break_cnt = 0;
	break_num = 0;
	hp_x_num = 4;

	for (int i = 0; i < heart_num; i++)
	{
		hp_x[i] = (int)x + 35 * i;
	}

	life_num = 0;
}

UI::~UI()
{
}

void UI::Update(int set_hp,int set_dyna_num)
{


	heart_num = set_hp / 10;
	dyna_num = set_dyna_num;



	HeartAnim();

	if (break_flg == true)
	{
		BreakHpAnim();
	}

}

void UI::Draw() const
{
	//int ax, ay;
	//GetMousePoint(&ax, &ay);
	
	//if (player->GetTutoAtkFlg() == true)
	//{
	//	DrawRotaGraph(player->GetLocation().x, player->GetLocation().y-100, 1, 0, btnB_img, TRUE, 0);
	//}
	//DrawRotaGraph(650, 675, 1, 0, btnY_img, TRUE, 0);
	// 	//DrawRotaGraph(1130, 675, 1, 0, btnB_img, TRUE, 0);
	//DrawRotaGraph(1200, 675, 1, 0, btnY_img, TRUE, 0);
	//DrawRotaGraph(1120, 30, 1, 0, score_img, TRUE, 0);

	DrawRotaGraph(140, (int)y, 1, 0, p_img, TRUE, 0);


	for (int i = 0; i < heart_num; i++)
	{
		DrawRotaGraph((int)x+35*i, (int)y-3, 0.5, 0, heart_img[heart_anim_num], TRUE, 0);
	}

	if (break_flg == true)
	{
		DrawRotaGraph(hp_x[hp_x_num], (int)y - 3, 0.5, 0, heart_break_img[break_num], TRUE, 0);
	}

	for (int i = 0; i < dyna_num; i++)
	{
		DrawRotaGraph(32+35 * i, (int)y+64, 1, 0, dyna_img, TRUE, 0);
	}

	DrawRotaGraph(55,51, 0.5, 0, num_img[life_num], TRUE, 0);

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

		if (btn_flg == false)
		{
			alpha = 255;
			//歩行UI表示
			btn_cnt++;
			switch (btn_cnt)
			{
			case 1:
				btn_num = 0;
				break;
			case 10:
				btn_num = 1;
				break;
			case 20:
				btn_num = 2;
				break;
			case 30:
				btn_num = 3;
				break;
			case 40:
				btn_cnt = 0;
				break;
			}

			if (player->GetLocation().x > 600)
			{
				btn_flg = true;
				btn_cnt = 0;
				btn_num = 0;
			}
		}

		if (btn_flg == true)
		{
			if (alpha > 0)
			{
				alpha -= 15;
			}
		}
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
		DrawRotaGraph((int)player->GetLocation().x, (int)player->GetLocation().y - 100, 1, 0, btnB_img[btn_num], TRUE, 0);
		break;
	case 2:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha);
		DrawGraph(0, 0, tuto_backimg[0], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	case 3:
		DrawRotaGraph((int)player->GetLocation().x, (int)player->GetLocation().y - 100, 1, 0, btnY_img[btn_num], TRUE, 0);
		break;
	case 4:
		if (btn_flg == true)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha);
		}
		DrawRotaGraph(500, (int)player->GetLocation().y - 100, 1, 0, btnmove_img[btn_num], TRUE, 0);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		
		break;

	}


}

void UI::HeartAnim()
{

	switch (anim_cnt)
	{
		case 60:
			heart_anim_num = 1;
			break;
		case 65:
			heart_anim_num = 2;
			break;
		case 70:
			heart_anim_num = 3;
			break;
		case 75:
			heart_anim_num = 4;
			break;
		case 80:
			heart_anim_num = 5;
			break;
		case 85:
			heart_anim_num = 0;
			break;
		case 90:
			heart_anim_num = 1;
			break;
		case 95:
			heart_anim_num = 2;
			break;
		case 100:
			heart_anim_num = 3;
			break;
		case 105:
			heart_anim_num = 4;
			break;
		case 110:
			heart_anim_num = 5;
			break;
		case 115:
			heart_anim_num = 0;
			anim_cnt = 0;
			break;
	}

	anim_cnt++;
}

void UI::BreakHpAnim()
{
	break_cnt++;
	if (break_cnt > 5)
	{
		break_num = 1;
	}
	
	if (break_cnt > 15)
	{
		hp_x_num -= 1;
		break_cnt = 0;
		break_num = 0;
		break_flg = false;
		if (heart_num <= 0)
		{
			hp_x_num = 4;
		}
	}
}
