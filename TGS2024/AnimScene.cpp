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
	//anim_scene = 5;
	alpha = 255;
	exc_flg = false;
	ase_flg = false;
	shake_flg = false;
}

AnimScene::~AnimScene()
{
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

		if (alpha < 0) {
			alpha = 0;
			anim_scene = 2;
		}
		else {
			alpha -= 1;
		}

		break;
	case 2:
		//プレイヤーが歩いてくる
		player->OpAnimUpdate(this, anim_scene);

		//画面の揺れ
		//ShakeCamera(fallingrock->GetLanding());

		break;
	case 3:

		if (alpha++ > 255) {
			if (alpha > 300) {
				p_backimg_num = 1;
			}
			
			if (alpha > 350) {
				p_backimg_num = 2;

			}

			if (alpha > 400) {
				anim_scene = 4;
				alpha = 255;
			}
		}

		break;
	case 4:

		player->OpAnimUpdate(this, anim_scene);

		if (alpha < 0) {
			alpha = 0;
			ase_flg = true;
		}
		else {
			alpha -= 1;
		}

		if (ase_flg == true)
		{
			if (cnt++ > 250)
			{
				ase_flg = false;
				anim_scene = 5;
				shake_flg = true;
			}
		}

		break;
	case 5:

		//画面の揺れ
		ShakeCamera(shake_flg,1);
		player->OpAnimUpdate(this, anim_scene);

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

	if (anim_scene == 1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(screen_origin_position.x, 0, black_img, FALSE);

	}

	if (anim_scene == 3||anim_scene==4)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(screen_origin_position.x, 0, p_backimg[p_backimg_num], FALSE);
	}



	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

	//DrawFormatString(300, 180, 0xffffff, "camerax: %f", camera_pos.x);
	//DrawFormatString(300, 300, 0xffffff, "alpha%d", alpha);
	DrawFormatString(300, 300, 0xffffff, "anim_scene%d", anim_scene);
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
			case 10:
				screen_origin_position.x -= shake_x2;
				break;
			case 20:
				screen_origin_position.x = 0;
				break;
			case 30:
				screen_origin_position.x += shake_x1;
				break;
			case 40:
				screen_origin_position.x -= shake_x2;
				break;
			case 50:
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
			case 10:
				screen_origin_position.x -= shake_x2;
				break;
			case 20:
				screen_origin_position.x = 0;
				break;
			case 30:
				screen_origin_position.x += shake_x1;
				break;
			case 40:
				screen_origin_position.x -= shake_x2;
				break;
			case 50:
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
	//if(shake_cnt>60)
	//{
	//	return new GameMainScene;
	//}
	return this;
}