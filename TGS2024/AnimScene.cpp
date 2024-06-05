#include "AnimScene.h"
//画面の中央を座標に入れる



AnimScene::AnimScene()
{
	fallingrock = new FallingRock;
	player = new Player();
	back_img = LoadGraph("images/Animscene/backimg.png", TRUE);
	block_img = LoadGraph("images/Animscene/block.png", TRUE);
	black_img = LoadGraph("images/Animscene/blackimg.png", TRUE);
	p_backimg[0]=LoadGraph("images/Animscene/startanim1.png", TRUE);
	p_backimg[1]=LoadGraph("images/Animscene/startanim2.png", TRUE);
	p_backimg[2]=LoadGraph("images/Animscene/startanim3.png", TRUE);
	p_ase_img= LoadGraph("images/Animscene/fukidashi_ase_white.png", TRUE);
	p_exc_img= LoadGraph("images/Animscene/fukidashi_exclamation_white.png", TRUE);
	x = 0;
	shake_cnt = 0;
	shake_x1=0;
	shake_x2=0;
	p_backimg_num = 0;

	cameraposition camera_pos{ SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f };

	cameraposition screen_origin_position = {
		camera_pos.x - SCREEN_WIDTH / 2.0f,
		camera_pos.y - SCREEN_HEIGHT / 2.0f
	};

	anim_scene = 0;
	//anim_scene = 6;
	alpha = 255;
	alpha2 = 0;
	exc_flg = false;
	ase_flg = false;
	shake_flg = false;
	next_scene_flg = false;

	cloth_rubbing_sound = LoadSoundMem("sounds/se/op/cloth_rubbing.mp3");
	shake_sound = LoadSoundMem("sounds/se/op/shake.mp3");
	anim_bgm = LoadSoundMem("sounds/bgm/opening.mp3");
	op_sad_sound = LoadSoundMem("sounds/se/player/sad.mp3");
	play_sad_sound = true;


	// サウンドの音量設定
	ChangeVolumeSoundMem(255, cloth_rubbing_sound);
	ChangeVolumeSoundMem(150, shake_sound);
	ChangeVolumeSoundMem(100, anim_bgm);
	ChangeVolumeSoundMem(180, op_sad_sound);
}

AnimScene::~AnimScene()
{
	delete player;
	// サウンド削除
	DeleteSoundMem(cloth_rubbing_sound);
	DeleteSoundMem(shake_sound);
	DeleteSoundMem(anim_bgm);
	DeleteSoundMem(op_sad_sound);

}

void AnimScene::Update()
{
	player->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);

	switch (anim_scene)
	{
	case 0:
		//暗い画面で
		//カンカン鳴らす
		player->OpAnimUpdate(this,anim_scene);


		break;
	case 1:
		if (CheckSoundMem(anim_bgm) == FALSE)
		{
			PlaySoundMem(anim_bgm, DX_PLAYTYPE_LOOP);
		}

		if (alpha < 0) {
			alpha = 0;
			anim_scene = 2;
		}
		else {
			alpha -= 5;
		}

		break;
	case 2:
		//プレイヤーが歩いてくる
		player->OpAnimUpdate(this, anim_scene);

		//画面の揺れ
		//ShakeCamera(fallingrock->GetLanding());

		break;
	case 3:
		alpha += 5;
		if (alpha > 255) {
			if (alpha > 300) {
				p_backimg_num = 1;
				//布擦れ音
				if (CheckSoundMem(cloth_rubbing_sound) == FALSE)
				{
					PlaySoundMem(cloth_rubbing_sound, DX_PLAYTYPE_BACK);
				}
			}
			
			if (alpha > 400) {
				p_backimg_num = 2;

			}

			if (alpha > 520)
			{
				//p_backimg_num = 3;
			}

			if (alpha > 700) {
				anim_scene = 4;
				alpha2 = 255;
				alpha = 255;
			}
		}

		break;
	case 4:

		player->OpAnimUpdate(this, anim_scene);

		if (alpha < 0) {
			alpha = 0;
			alpha2 = 0;
			ase_flg = true;
			//悲しいse
			if (play_sad_sound == true)
			{
				if (CheckSoundMem(op_sad_sound) == FALSE)
				{
					PlaySoundMem(op_sad_sound, DX_PLAYTYPE_BACK);
				}
				play_sad_sound = false;
			}
		}
		else {
			alpha -= 5;
		}

		if (ase_flg == true)
		{
			cnt += 5;
			if (cnt > 300)
			{
				ase_flg = false;
				anim_scene = 5;
				shake_flg = true;
				cnt = 0;
			}
		}

		break;
	case 5:

		StopSoundMem(anim_bgm);
		//画面の揺れ
		ShakeCamera(shake_flg,1);
		//揺れse
		if (CheckSoundMem(shake_sound) == FALSE)
		{
			PlaySoundMem(shake_sound, DX_PLAYTYPE_BACK);
		}
		player->OpAnimUpdate(this, anim_scene);
		alpha = 0;

		break;
	case 6:
		//でかい岩が落ちてくる
		if (fallingrock != nullptr)
		{
			fallingrock->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
			fallingrock->Update();
		}
		//画面の揺れ
		ShakeCamera(fallingrock->GetLanding(),2);
	break;
	}
	
	if (run_flg == true)
	{
		player->OpAnimUpdate(this, 6);

	}

	if (fallingrock->GetBlackOut() == true)
	{
		alpha += 5;
		if (alpha > 255) {
			next_scene_flg = true;
			anim_scene = 7;
		}

	}


	//screen_origin_position = {
	//camera_pos.x - SCREEN_WIDTH / 2.0f,
	//camera_pos.y - SCREEN_HEIGHT / 2.0f
	//};
}

void AnimScene::Draw() const
{

	DrawGraph(screen_origin_position.x, 0, back_img, FALSE);

	if (fallingrock != nullptr)
	{
		fallingrock->Draw();

	}

	if (player != nullptr)
	{
		player->Draw();

		if (ase_flg == true)
		{
			DrawGraph(player->GetLocation().x-60, player->GetLocation().y-60, p_ase_img, TRUE);
		}

		if (exc_flg == true)
		{
			DrawGraph(player->GetLocation().x - 60, player->GetLocation().y - 60, p_exc_img, TRUE);
		}
	}

	DrawGraph(x, 640,block_img, FALSE);

	if (anim_scene == 1||fallingrock->GetBlackOut() == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(screen_origin_position.x, 0, black_img, FALSE);
	}

	if (anim_scene == 3||anim_scene==4)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(screen_origin_position.x, 0, p_backimg[p_backimg_num], FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha2);
	}



	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

	//DrawFormatString(300, 180, 0xffffff, "camerax: %f", camera_pos.x);
	//DrawFormatString(300, 300, 0xffffff, "alpha%d", alpha);
	//DrawFormatString(300, 300, 0xffffff, "anim_scene%d", anim_scene);
}

void AnimScene::ShakeCamera(bool set_true, int set_num)
{
	if (set_num == 1)
	{
		shake_x1 = 5;
		shake_x2 = 10;
		if (set_true == true)
		{
			//画面の揺れ
			switch (shake_cnt)
			{
			case 0:
				screen_origin_position.x += shake_x1;
				break;
			case 2:
				screen_origin_position.x -= shake_x2;
				break;
			case 4:
				screen_origin_position.x = 0;
				break;
			case 6:
				screen_origin_position.x += shake_x1;
				break;
			case 8:
				screen_origin_position.x -= shake_x2;
				break;
			case 10:
				screen_origin_position.x = 0;
				shake_cnt = 0;
				break;
			}
			shake_cnt++;
		}
		else
		{
			shake_cnt = 0;
		}

	}
	else
	{
		if (set_true == true)
		{
			shake_x1 = 20;
			shake_x2 = 40;
			//画面の揺れ
			switch (shake_cnt)
			{
			case 0:
				screen_origin_position.x += shake_x1;
				break;
			case 2:
				screen_origin_position.x -= shake_x2;
				break;
			case 4:
				screen_origin_position.x = 0;
				break;
			case 6:
				screen_origin_position.x += shake_x1;
				break;
			case 8:
				screen_origin_position.x -= shake_x2;
				break;
			case 10:
				screen_origin_position.x = 0;
				shake_cnt = 0;
				break;
			}
			shake_cnt++;
		}
		else
		{
			shake_cnt = 0;
		}
	}
}


AbstractScene* AnimScene::Change() {
	if(next_scene_flg==true)
	{
		StopSoundMem(anim_bgm);
		return new GameMainScene;
	}
	return this;
}