#include "FallingFloor.h"

FallingFloor::FallingFloor(float set_x, float set_y)
{
	world.x = set_x;
	world.y = set_y;
	location.x = world.x;
	location.y = world.y;
	width = 128.0f;
	height = 64.0f;

	falling_floor_img = LoadGraph("images/Stage/Gimmick/FallingFloor.png");
	
	hp = 10.0f;
	img_num = 0;
	anim_cnt = 0;
	touched_ground = false;			// 地面に触れていない
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

	if (hp <= 0.0f && touched_ground == false)
	{
		// 落下
		world.y++;
	}
}

void FallingFloor::Draw() const
{
	// 落ちる床画像の描画
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, falling_floor_img, TRUE);

	// 頂点の確認
	//DrawBox((int)box_vertex.right_x, (int)box_vertex.upper_y, (int)box_vertex.left_x, (int)box_vertex.lower_y, 0x00ffff, FALSE);
}

// 被ダメージ処理
void FallingFloor::Damage(float damage)
{
	hp -= damage;
}

// 床の落下を止める
void FallingFloor::StopFalling()
{
	// 地面に触れた
	touched_ground = true;
}
