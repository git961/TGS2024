#include "AnimScene.h"
//画面の中央を座標に入れる



AnimScene::AnimScene()
{
	fallingrock = new FallingRock;
	player = new Player();
	back_img = LoadGraph("images/Animscene/backimg.png", TRUE);
	block_img = LoadGraph("images/Animscene/block.png", TRUE);

	x = 0;
	shake_cnt = 0;
	shake_x1=20;
	shake_x2=40;

	cameraposition camera_pos{ SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f };

	cameraposition screen_origin_position = {
		camera_pos.x - SCREEN_WIDTH / 2.0f,
		camera_pos.y - SCREEN_HEIGHT / 2.0f
	};

	anim_scene = 0;
}

AnimScene::~AnimScene()
{
}

void AnimScene::UpdateCamera()
{

	//ワールドの底に到達したらカメラが移動しないように
	if (camera_pos.y - WINDOW_HALFY <= 0.0f)
	{
		camera_pos.y = WINDOW_HALFY;
	}
	else if (camera_pos.y + WINDOW_HALFY >= FIELD_HEIGHT)
	{
		//ワールドのてっぺんに到達したらカメラが移動しないように
		camera_pos.y = FIELD_HEIGHT - WINDOW_HALFY;
	}

	
}


void AnimScene::Update()
{
	UpdateCamera();

	switch (anim_scene)
	{
	case 0:
		//プレイヤーが歩いてくる
		

		//画面の揺れ
		//ShakeCamera(fallingrock->GetLanding());

	break;
	case 1:
		//でかい岩が落ちてくる
		if (fallingrock != nullptr)
		{
			fallingrock->SetLocalPosition(screen_origin_position.x, screen_origin_position.y);
			fallingrock->Update();
		}
		//画面の揺れ
		ShakeCamera(fallingrock->GetLanding());

	break;
	case 2:
		//逃げる
		break;
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
	}

	DrawGraph(x, 640,block_img, FALSE);

	//DrawFormatString(300, 180, 0xffffff, "camerax: %f", camera_pos.x);
	//DrawFormatString(300, 200, 0xffffff, "cameray: %f", camera_pos.y);
}

void AnimScene::ShakeCamera(bool set_true)
{
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


AbstractScene* AnimScene::Change() {
	//if(shake_cnt>60)
	//{
	//	return new GameMainScene;
	//}
	return this;
}