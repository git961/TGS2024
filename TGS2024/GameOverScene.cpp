#include "GameOverScene.h"

GameOverScene::GameOverScene(int set_score)
{
	score = set_score;
	change_cnt = 180;
	volume = 150;
	play_sound_flg = true;
	x = 640;
	y = -100;
	effect_y = 550;
	rip_num = 0;
	rip_cnt = 0;
	rock_num = 0;
	rock_flg = false;
	select_flg = false;
	push_b_flg = false;

	//画像読込
	LoadDivGraph("images/scene/gameover/haka.png", 5, 5, 1, 128, 128, rip_img);
	LoadDivGraph("images/scene/gameover/retry.png", 5, 5, 1, 128, 128, retry_img);
	LoadDivGraph("images/scene/gameover/font.png", 2, 1, 2, 180, 64, font_img);
	LoadDivGraph("images/Animscene/rockeffect.png", 4, 4, 1, 1024, 512, rock_effect_img);

	cursor_img = LoadGraph("images/scene/title/cursor.png");
	ring_img = LoadGraph("images/scene/gameover/ring.png");
	move_cursor_se = LoadSoundMem("sounds/se/system/cursor.mp3");
	font_img[2] = LoadGraph("images/scene/gameover/gameover.png");
	ChangeVolumeSoundMem(200, move_cursor_se);
	//640, 400,
	cursor_x = 450;
	cursor_y = 400;
	cursor_move_interval = 40;
	cursor_num = Retry;

	size = 0.5;
	alpha = 255;
	// サウンド読込
	gameover_se = LoadSoundMem("sounds/se/scene/gameover.mp3");
	change_flg = false;

	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, gameover_se);
}

GameOverScene::~GameOverScene()
{

}

void GameOverScene::Update()
{
	input.InputUpdate();

	// ゲームオーバーse再生
	if (play_sound_flg == true)
	{
		PlaySoundMem(gameover_se, DX_PLAYTYPE_BACK);
		play_sound_flg = false;
	}

	if (select_flg == false)
	{
		if (y > 599)
		{
			y = 600;
			rip_cnt++;
			switch (rip_cnt)
			{
			case 1:
				rock_flg = true;
				rip_num = 1;
				rock_num = 0;
				break;
			case 3:
				rip_num = 2;
				rock_num = 1;
				break;
			case 6:
				rip_num = 3;
				rock_num = 2;
				break;
			case 9:
				rip_num = 4;
				rock_num = 3;
				break;
			case 12:
				rip_num = 0;

				size = 0.6;
				alpha = 150;
				effect_y -= 10;
				break;
			case 15:

				size = 0.7;
				alpha = 100;
				effect_y -= 30;
				break;
			case 18:

				size = 0.8;
				alpha = 50;
				effect_y -= 40;
				break;
			case 21:
				rock_flg = false;
				break;
			case 30:
				select_flg = true;
				rip_cnt = 0;
				break;
			}
		}
		else {
			y += 40;
		}
	}
	else
	{
		if (cursor_move_interval < 15)
		{
			cursor_move_interval++;
		}
		else
		{
			if (push_b_flg == false)
			{
				if (input.LongPressBtn(XINPUT_BUTTON_DPAD_UP) == TRUE || input.GetPadThumbLY() >= 32000)
				{
					// カーソルse
					PlaySoundMem(move_cursor_se, DX_PLAYTYPE_BACK);

					cursor_move_interval = 0;
					// カーソル上移動
					if (cursor_num == Retry)
					{
						cursor_num = End;
					}
					else
					{
						cursor_num--;
					}
				}
				if (input.LongPressBtn(XINPUT_BUTTON_DPAD_DOWN) == TRUE || input.GetPadThumbLY() <= -32000)
				{
					// カーソルse
					PlaySoundMem(move_cursor_se, DX_PLAYTYPE_BACK);

					cursor_move_interval = 0;
					// カーソル下移動
					if (cursor_num == End)
					{
						cursor_num = Retry;
					}
					else
					{
						cursor_num++;
					}
				}

					// Bボタンで決定
					if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
					{

						push_b_flg = true;
					}
				

				if (cursor_num == Retry)
				{
					cursor_y = 400;
				}
				else
				{
					cursor_y = 500;
				}

			}
			else
			{
				if (cursor_num == Retry)
				{
					//プレイヤーが墓から出てくるアニメーションの後sceneを移動

					rip_cnt++;
					switch (rip_cnt)
					{
					case 1:
						rip_num = 0;
						break;
					case 5:
						rip_num = 1;
						break;
					case 10:
						rip_num = 2;
						break;
					case 15:
						rip_num = 3;
						break;
					case 20:
						rip_num=4;
						break;
					case 60:
						change_flg = true;
						break;
					}

				}
				else {

				}
			}
		}

	}
}

void GameOverScene::Draw() const
{
#ifdef DEBUG
	SetFontSize(20);
	DrawFormatString(10, 10, 0xffffff, "GameOver");
	DrawFormatString(10, 50, 0xffffff, "draw_cnt: %d", change_cnt);
	DrawFormatString(10, 70, 0xffffff, "btnflg: %d", push_b_flg);
#endif // DEBUG

	//DrawRotaGraph(location.x, location.y-25, 1, 0, player_img[p_imgnum], TRUE, direction);
	if (rock_flg == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawRotaGraph(x, effect_y, size, 0, rock_effect_img[rock_num], TRUE, 0);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}

	if (push_b_flg == false)
	{
		DrawRotaGraph(x, y, 1, 0, rip_img[rip_num], TRUE, 0);
		//DrawRotaGraph(x, y-60, 1, 0, ring_img, TRUE, 0);
		
	}
	else {
		if (cursor_num == Retry) {
			DrawRotaGraph(x, y, 1, 0, retry_img[rip_num], TRUE, 0);
		}

	}

	if (select_flg == true)
	{
		// カーソル画像
		DrawRotaGraph(cursor_x, cursor_y, 1.0, 0.0, cursor_img, TRUE, FALSE);
		DrawRotaGraph(640, 170, 2.3, 0.0, font_img[2], TRUE, FALSE);
		// start・end
		DrawRotaGraph(640, 400, 1.5, 0.0, font_img[0], TRUE, FALSE);
		DrawRotaGraph(680, 500, 1.5, 0.0, font_img[1], TRUE, FALSE);

	}

}

AbstractScene* GameOverScene::Change()
{

		if (change_flg == true)
		{
			// ゲームオーバーse停止
			if (CheckSoundMem(gameover_se) == TRUE)
			{
				StopSoundMem(gameover_se);
			}

			if (cursor_num == Retry)
			{
				return new GameMainScene;
			}
			else {
				// Bボタンでタイトルに遷移
				return new TitleScene;

			}
		}
	
	return this;
}
