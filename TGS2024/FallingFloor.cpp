#include "FallingFloor.h"

FallingFloor::FallingFloor(float set_x, float set_y)
{
	world.x = set_x - 32.0f;
	world.y = set_y;
	location.x = world.x;
	location.y = world.y;
	width = 128.0f;
	height = 64.0f;

	falling_floor_img = LoadGraph("images/Stage/Gimmick/FallingFloor.png");
	
	img_num = 0;
	anim_cnt = 0;
	falling_speed = 3.0f;
	touched_magma = false;			// 地面に触れていない
	falling_flg = false;			// 落下しない

	// サウンド読込
	falling_se = LoadSoundMem("sounds/se/gimmick/falling_floor.mp3");
	volume = 150;

	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, falling_se);
}

FallingFloor::~FallingFloor()
{
	// 画像の削除
	DeleteGraph(falling_floor_img);
}

void FallingFloor::Update()
{
	// 頂点の更新
	SetVertex();

	if (falling_flg == true && touched_magma == false)
	{
		// 落下
		world.y += falling_speed;

		// サウンドを再生するか調べる
		CheckPlaySound();
	}
	else
	{
		// 音が鳴っていたら
		if (CheckSoundMem(falling_se) == TRUE)
		{
			// 音を止める
			StopSoundMem(falling_se);
		}
	}
}

void FallingFloor::Draw() const
{
	// 落ちる床画像の描画
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, falling_floor_img, TRUE);

	// 頂点の確認
	//DrawBox((int)box_vertex.right_x, (int)box_vertex.upper_y, (int)box_vertex.left_x, (int)box_vertex.lower_y, 0x00ffff, FALSE);
}

bool FallingFloor::GetTouchedMagma() const
{
	return touched_magma;
}

// 床の落下を止める
void FallingFloor::StopFalling()
{
	// 地面に触れた
	touched_magma = true;
	falling_flg = false;//落下しない
}

bool FallingFloor::GetFallingFlg() const
{
	return falling_flg;
}

void FallingFloor::StartFalling()
{
	// 落下を開始する
	falling_flg = true;
}

// サウンドを再生するか調べる
void FallingFloor::CheckPlaySound()
{
	// スクリーン範囲にいるんだったら
	if (location.x > 50.0f && location.x < 1230.0f && location.y > 50.0f && location.y < 670.0f)
	{
		if (volume != 150)
		{
			volume = 150;
			ChangeVolumeSoundMem(volume, falling_se);
		}

		// 音を鳴らす
		if (CheckSoundMem(falling_se) == FALSE)
		{
			PlaySoundMem(falling_se, DX_PLAYTYPE_BACK);
		}
	}
	else if (location.x > 0.0f && location.x < 1280.0f && location.y > 0.0f && location.y < 720.0f)
	{
		// 音量を小さくする
		if (volume != 120)
		{
			volume = 120;
			ChangeVolumeSoundMem(volume, falling_se);
		}

		// 音を鳴らす
		if (CheckSoundMem(falling_se) == FALSE)
		{
			PlaySoundMem(falling_se, DX_PLAYTYPE_BACK);
		}
	}
	else
	{
		// 音を止める
		if (CheckSoundMem(falling_se) == TRUE)
		{
			StopSoundMem(falling_se);
		}
	}
}
