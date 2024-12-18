#include "GameOverScene.h"

GameOverScene::GameOverScene(int stage_num)
{

	set_stage_num = stage_num;

	change_cnt = 60;
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
	LoadDivGraph("images/scene/gameover/haka.png", 5, 5, 1, 170, 170, rip_img);
	LoadDivGraph("images/scene/gameover/retry.png", 5, 5, 1, 170, 170, retry_img);
	LoadDivGraph("images/scene/gameover/font.png", 2, 1, 2, 180, 64, font_img);
	LoadDivGraph("images/Animscene/rockeffect.png", 4, 4, 1, 1024, 512, rock_effect_img);

	LoadDivGraph("images/scene/title/cursor01.png", 3, 3, 1, 128, 92, cursor_img);
	ring_img = LoadGraph("images/scene/gameover/ring.png");
	push_b_img = LoadGraph("images/scene/title/push_b_blue.png");
	move_cursor_se = LoadSoundMem("sounds/se/scene/title/cursor.mp3");
	font_img[2] = LoadGraph("images/scene/gameover/gameover.png");
	ChangeVolumeSoundMem(200, move_cursor_se);
	//640, 400,
	cursor_x = 430;
	cursor_y = 400;
	cursor_move_interval = 40;
	cursor_num = Retry;
	cursor_img_num = 0;

	size = 0.5;
	alpha = 255;
	// サウンド読込
	gameover_se = LoadSoundMem("sounds/se/scene/gameover/defeat.mp3");
	change_flg = false;

	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, gameover_se);

	ring_x = 640;
	ring_y = 590;
	count = 0;
	ring_start_x = ring_x;
	anim_finish_flg = false;
	ring_alpha = 0;
	lower_ring_alpha = false;

	grave_se = LoadSoundMem("sounds/se/scene/gameover/grave.mp3");
	fallen_leaves_se = LoadSoundMem("sounds/se/scene/gameover/fallen_leaves.mp3");
	decision_se = LoadSoundMem("sounds/se/player/Attack.mp3");
	gameover_bgm = LoadSoundMem("sounds/bgm/gameover.mp3");

	ChangeVolumeSoundMem(150, grave_se);
	ChangeVolumeSoundMem(150, fallen_leaves_se);
	ChangeVolumeSoundMem(150, decision_se);
	ChangeVolumeSoundMem(130, gameover_bgm);

	cursor_anim_cnt = 0;

	fade_alpha = 0;
	fadeout_flg = false;
	black_img= LoadGraph("images/Backimg/death.png");
}

GameOverScene::~GameOverScene()
{

	// 画像の削除
	DeleteGraph(ring_img);
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(cursor_img[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(rock_effect_img[i]);
		DeleteGraph(retry_img[i]);
		DeleteGraph(font_img[i]);
	}
	for (int i = 0; i < 6; i++)
	{
		DeleteGraph(rip_img[i]);
	}

	// サウンドの削除
	DeleteSoundMem(gameover_se);
	DeleteSoundMem(move_cursor_se);
	DeleteSoundMem(grave_se);
	DeleteSoundMem(fallen_leaves_se);
	DeleteSoundMem(decision_se);
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

	if (anim_finish_flg == false)
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

				// 墓の着地音
				if (CheckSoundMem(grave_se) == FALSE)
				{
					PlaySoundMem(grave_se, DX_PLAYTYPE_BACK);
				}

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

				size = 0.6f;
				alpha = 150;
				effect_y -= 10;
				break;
			case 15:

				size = 0.7f;
				alpha = 100;
				effect_y -= 30;
				break;
			case 18:

				size = 0.8f;
				alpha = 50;
				effect_y -= 40;
				break;
			case 21:
				rock_flg = false;
				break;
			case 30:
				rip_cnt = 0;
				anim_finish_flg = true;
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

				if (select_flg == true)
				{
					// Bボタンで決定
					if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
					{
						// つるはしでたたく音
						if (CheckSoundMem(decision_se) == FALSE)
						{
							PlaySoundMem(decision_se, DX_PLAYTYPE_BACK);
						}

						push_b_flg = true;
					}
				}
				
				if (cursor_num == Retry)
				{
					cursor_y = 400;
				}
				else
				{
					cursor_y = 480;
				}

			}
			else
			{
				// カーソルの画像番号を動かす
				if (cursor_img_num < 2)
				{
					cursor_anim_cnt++;

					cursor_img_num = cursor_anim_cnt / 3;
				}

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
						// 墓から出てくる音
						if (CheckSoundMem(fallen_leaves_se) == FALSE)
						{
							PlaySoundMem(fallen_leaves_se, DX_PLAYTYPE_BACK);
						}

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
					if (change_cnt > 0)
					{
						change_cnt--;
					}
					else
					{
						change_flg = true;
					}
				}
			}
		}

	}

	// 墓アニメーションが終わっていたら
	if (anim_finish_flg == true)
	{
		// リングアニメーション
		RingAnimation();
	}

	// ゲームオーバーbgmループ再生
	if (CheckSoundMem(gameover_se) == FALSE)
	{
		if (CheckSoundMem(gameover_bgm) == FALSE)
		{
			PlaySoundMem(gameover_bgm, DX_PLAYTYPE_LOOP);
		}
	}

	if (change_flg==true)
	{
		//画面暗くする
		if (fade_alpha > 255)
		{
			fadeout_flg = true;
		}
		fade_alpha += 5;
	}
}

void GameOverScene::Draw() const
{
#ifdef DEBUG
	//SetFontSize(20);
	//DrawFormatString(10, 10, 0xffffff, "GameOver");
	//DrawFormatString(10, 50, 0xffffff, "draw_cnt: %d", change_cnt);
	//DrawFormatString(10, 70, 0xffffff, "btnflg: %d", push_b_flg);
	//DrawFormatString(10, 70, 0xffffff, "cursor_num: %d", cursor_num);
	//DrawFormatString(10, 70, 0xffffff, "change_flg: %d", change_flg);
#endif // DEBUG

	//DrawRotaGraph(location.x, location.y-25, 1, 0, player_img[p_imgnum], TRUE, direction);
	if (rock_flg == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawRotaGraph((int)x, (int)effect_y, size, 0, rock_effect_img[rock_num], TRUE, 0);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (anim_finish_flg == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, ring_alpha);
		// リング画像
		DrawRotaGraph((int)ring_x, (int)ring_y - 60, 1, 0, ring_img, TRUE, 0);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (push_b_flg == false)
	{
		DrawRotaGraph((int)x, (int)y, 1, 0, rip_img[rip_num], TRUE, 0);
	}
	else {

		if (cursor_num == Retry) {
			DrawRotaGraph((int)x, (int)y, 1, 0, retry_img[rip_num], TRUE, 0);
		}
		else
		{
			DrawRotaGraph((int)x, (int)y, 1, 0, rip_img[0], TRUE, 0);
		}

	}

	if (select_flg == true)
	{
		// カーソルアニメーション
		DrawRotaGraph(cursor_x, cursor_y, 1.0, 0.0, cursor_img[cursor_img_num], TRUE, FALSE);

		DrawRotaGraph(640, 150, 2.3, 0.0, font_img[2], TRUE, FALSE);
		// start・end
		DrawRotaGraph(640, 400, 1.5, 0.0, font_img[0], TRUE, FALSE);
		DrawRotaGraph(680, 480, 1.5, 0.0, font_img[1], TRUE, FALSE);

		DrawRotaGraph(640, 700, 0.5, 0.0, push_b_img, TRUE, FALSE);
	}

	if (change_flg == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade_alpha);
		DrawGraph(0, 0, black_img,TRUE);
	}

}

AbstractScene* GameOverScene::Change()
{
	//画面が暗くなったら画面切り替えをする
	if (fadeout_flg==true)
	{
		// ゲームオーバーbgm停止
		if (CheckSoundMem(gameover_bgm) == TRUE)
		{
			StopSoundMem(gameover_bgm);
		}

		if (cursor_num == Retry)
		{
			return new GameMainScene(true,set_stage_num);
		}
		else {
			// Bボタンでタイトルに遷移
			return new TitleScene;
		}
	}
	
	return this;
}

// リングアニメーション
void GameOverScene::RingAnimation()
{
	// cos用カウント
	if (count <= 60)
	{
		count++;
	}
	else
	{
		count = 0;
	}

	// 画像は左右に揺れながら上がっていく
	ring_x = ring_start_x - cosf((float)M_PI * 2.0f / 60.0f * count) * 10.0f;
	ring_y--;

	// アニメーションが終わったら選択可能になる
	if (lower_ring_alpha == false)
	{
		// 画像を濃くする
		if (ring_alpha <= 120)
		{
			ring_alpha += 3;
		}
		else
		{
			lower_ring_alpha = true;
		}
	}
	else
	{
		// 画像を薄くする
		if (ring_alpha >= 0)
		{
			ring_alpha -= 2;
		}
		else
		{
			select_flg = true;
		}
	}
}
