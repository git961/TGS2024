#pragma once
#include <math.h>
#include "DxLib.h"

//#define CHARAIMAGENUM 10;//キャラクタ画像入れる配列の大きさ

class CharacterBase
{
protected:

	float x;
	float y;
	
	float move_x;
	float move_y;

	float hp;//体力
	float attack;//攻撃力

	float speed;

	int chara_image[10];//キャラクタ画像入れる用

	float width;
	float height;

	float distance_x;
	float distance_y;

	float two_widths;
	float two_heights;

	//opponent:意味→相手

public:
	//コンストラクタとデストラクタ
	CharacterBase(){};
	~CharacterBase(){};

	//当たり判定:何かに当たったかどうかだけ返す
	bool HitCheck(float opponent_x,float opponent_y,float opponent_center_x, float opponent_center_y)
	{
		float my_center_x = width / 2;
		float my_center_y = height / 2;

		//x座標の相手と自分の距離を絶対値で測る
		distance_x = fabs(x - opponent_x);
		//2つの幅/2を足す
		two_widths = my_center_x + opponent_center_x/2;

		//y座標の相手と自分の距離を絶対値で測る
		distance_y = fabs(y - opponent_y);
		//2つの高さ/2を足す
		two_heights = my_center_y + opponent_center_y / 2;

		//もし距離の絶対値より幅が大きかったらヒット
		if (distance_x < two_widths && distance_y<two_heights)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

};

