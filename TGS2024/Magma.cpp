#include "Magma.h"

Magma::Magma(float set_x, float set_y)
{
	world.x = set_x - 32.0f;
	world.y = set_y;
	location.x = world.x;
	location.y = world.y;
	width = 128.0f;
	height = 64.0f;

	LoadDivGraph("images/Stage/Gimmick/Magma.png", 10, 5, 2, 128, 64, magma_img);
	LoadDivGraph("images/Stage/Gimmick/MagmaEffect.png", 4, 4, 1, 168, 84, magma_effect_img);

	img_num = 0;
	anim_cnt = 0;
	effect_img_num = 0;
	effect_anim_cnt = 0;
	is_any_damage = true;				// ダメージあり
}

Magma::~Magma()
{
	for (int i = 0; i < 10; i++)
	{
		// 画像の削除
		DeleteGraph(magma_img[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		// 画像の削除
		DeleteGraph(magma_effect_img[i]);
	}
}

// 更新処理
void Magma::Update()
{
	// 頂点の更新
	SetVertex();

	// マグマのアニメーション
	Animation();
}

// 描画処理
void Magma::Draw() const
{
	// マグマ画像の描画
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, magma_img[img_num], TRUE);
	if (is_any_damage == true)
	{
		DrawRotaGraph((int)location.x, (int)location.y-20, 1.0, 0.0, magma_effect_img[effect_img_num], TRUE);
	}
	// 頂点の確認
	DrawBox((int)box_vertex.right_x, (int)box_vertex.upper_y, (int)box_vertex.left_x, (int)box_vertex.lower_y, 0x00ffff, FALSE);
}

bool Magma::GetAnyDamageFlg() const
{
	return is_any_damage;
}

void Magma::NullificationDamage()
{
	// マグマのダメージ無し
	is_any_damage = false;
}

// マグマのアニメーション
void Magma::Animation()
{
	if (anim_cnt <= 30)
	{
		anim_cnt++;
	}
	else
	{
		anim_cnt = 0;

		// 画像切り替え
		img_num++;

		if (is_any_damage == true)
		{
			if (img_num == 5)
			{
				img_num = 0;
			}
		}
		else
		{
			if (img_num == 10)
			{
				img_num = 6;
			}
		}
	}


	if (is_any_damage == true)
	{
		if (effect_anim_cnt++ == 10)
		{
			effect_anim_cnt = 0;
			if (effect_img_num++ == 4)
			{
				effect_img_num = 0;
			}
		}
	}

}
