#include "GameClearScene.h"

GameClearScene::GameClearScene(int set_score)
{
	score = set_score;
	change_cnt = 180;
	volume = 150;
	se_flg = true;

	// サウンド読込
	gameclear_se = LoadSoundMem("sounds/se/scene/gameclear.mp3");
	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, gameclear_se);

	ending_img[0] = LoadGraph("images/Ending/ending1.png", TRUE);
	ending_img[1] = LoadGraph("images/Ending/ending2.png", TRUE);
	ending_img[2] = LoadGraph("images/Ending/ending3.png", TRUE);
	ending_img[3] = LoadGraph("images/Ending/ending4.png", TRUE);
	ending_img[4] = LoadGraph("images/Ending/ending5.png", TRUE);
	ending_img[5] = LoadGraph("images/Ending/ending6.png", TRUE);
	ending_img[6] = LoadGraph("images/Ending/ending7.png", TRUE);
	ending_img[7] = LoadGraph("images/Ending/ending8.png", TRUE);
	ending_img[8] = LoadGraph("images/Animscene/blackimg.png", TRUE);

	endimg_num = 0;
	alpha2 = 0;
	change_imgnum_cnt = 0;
	alpha_start_flg = false;
	alpha = 255;
	change_img_num = 0;
}

GameClearScene::~GameClearScene()
{

}

void GameClearScene::Update()
{
	//input.InputUpdate();
	//// クリアse再生

	//if (change_cnt > 0) 
	//{
	//	change_cnt--;
	//}
	/*
	change_imgnum_cnt++;

	switch (change_imgnum_cnt)
	{
		case 100:
			endimg_num = 1;
			break;
		case 150:
			endimg_num = 2;
			break;
		case 200:
			endimg_num = 3;
			break;
		case 350:
			endimg_num = 4;
			break;
		case 400:
			endimg_num = 5;
			break;
		case 500:
			endimg_num = 6;
			break;
		case 650:
			alpha_start_flg = true;
			break;
	}
	*/

	switch (change_img_num)
	{
	case 0:
		//白画像をうすくして洞窟から出てくる画像表示
		alpha -= 2;
		if (alpha < 0)
		{
			//カウントが100より大きくなったら、次の画像をうっすら表示させていく
			if(change_imgnum_cnt<100)
			{
				change_imgnum_cnt++;
			}
			else
			{
				alpha2 += 5;
				if (alpha2 > 255)
				{
					change_imgnum_cnt = 0;
					change_img_num = 1;
					alpha2 = 0;
					alpha = 0;
					endimg_num = 1;
				}

			}
		}
		if (se_flg == true)
		{
			PlaySoundMem(gameclear_se, DX_PLAYTYPE_BACK);
			se_flg = false;
		}
		break;
	case 1:
		//目を閉じて汗を拭く画像１
		if (change_imgnum_cnt < 50)
		{
			change_imgnum_cnt++;
		}
		else {
			change_imgnum_cnt = 0;
			endimg_num = 2;
			change_img_num = 2;
		}
		break;
	case 2:
		//目を閉じて汗を拭く画像２
		//カウントが50より大きくなったら次の画像をうっすら表示
		if (change_imgnum_cnt < 50)
		{
			change_imgnum_cnt++;
		}
		else {
			alpha2 += 5;
			if (alpha2 > 255)
			{
				change_imgnum_cnt = 0;
				endimg_num = 3;
				change_img_num = 3;
				alpha2 = 0;
			}

		}
		break;
	case 3:
		//袋を開ける1
		if (change_imgnum_cnt < 50)
		{
			change_imgnum_cnt++;
		}
		else {
			endimg_num=4;
			change_img_num = 4;
			change_imgnum_cnt = 0;;
		}
		break;
	case 4:
		//袋を開ける2
		if (change_imgnum_cnt < 50)
		{
			change_imgnum_cnt++;
		}
		else {
				endimg_num = 5;
				change_img_num = 5;
				change_imgnum_cnt = 0;
		}
		break;
	case 5:
		//袋を開ける3
		//カウントが50より大きくなったら次の画像をうっすら表示
		if (change_imgnum_cnt < 50)
		{
			change_imgnum_cnt++;
		}
		else {
			alpha2 += 5;
			if (alpha2 > 255)
			{
				endimg_num = 6;
				change_img_num = 6;
				change_imgnum_cnt = 0;
				alpha2 = 0;
			}
		}
		break;
	case 6:
		//上を見上げて喜んでる画像
		if (change_imgnum_cnt < 150)
		{
			change_imgnum_cnt++;
		}
		else {
			change_imgnum_cnt = 0;
			change_img_num = 7;
		}
		break;
	case 7:
		alpha_start_flg = true;
		break;
	}

	
	//白い画像を濃ゆくして、ブラックアウトさせる
	if (alpha_start_flg == true)
	{
		alpha+=2;
		if (alpha > 255)
		{
			alpha2 += 2;
		}
	}

}

void GameClearScene::Draw() const
{
#ifdef DEBUG
	//SetFontSize(20);
	//DrawFormatString(10, 10, 0xffffff, "GameClear");
	//DrawFormatString(10, 50, 0xffffff, "draw_cnt: %d", change_cnt);
	//DrawFormatString(10, 70, 0xffffff, "score: %d", score);

#endif // DEBUG
	//if (change_cnt <= 0)
	//{
	//	DrawFormatString(500, 600, 0xffffff, "B: EndCredits");
	//}

	switch (change_img_num)
	{
	case 0:
		DrawGraph(0, 0, ending_img[endimg_num], TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha2);
		DrawGraph(0, 0, ending_img[endimg_num+1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha);
		DrawGraph(0, 0, ending_img[7], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	case 1:
	case 2:
		DrawGraph(0, 0, ending_img[endimg_num], TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha2);
		DrawGraph(0, 0, ending_img[endimg_num + 1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		break;
	case 3:
	case 4:
	case 5:
		DrawGraph(0, 0, ending_img[endimg_num], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha2);
		DrawGraph(0, 0, ending_img[endimg_num + 1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	case 6:
	case 7:
		DrawGraph(0, 0, ending_img[endimg_num], TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha);
		DrawGraph(0, 0, ending_img[7], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha2);
		DrawGraph(0, 0, ending_img[8], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	}


}

AbstractScene* GameClearScene::Change()
{
	//if (change_cnt <= 0)
	//{
	//	if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
	//	{
	//		// クリアbgm停止
	//		if (CheckSoundMem(gameclear_se) == TRUE)
	//		{
	//			StopSoundMem(gameclear_se);
	//		}

	//		// Bボタンでエンドロールに遷移
	//		return new EndCreditsScene;
	//	}
	//}

	if (alpha2 > 300)
	{
		return new EndCreditsScene(score);
	}
	return this;
}
