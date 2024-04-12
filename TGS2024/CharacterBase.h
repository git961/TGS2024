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
	bool direction;//向き　0:右 1:左

	int chara_image[10];//キャラクタ画像入れる用

	float width;//幅
	float height;//高さ

	float distance_x;//x同士の距離の計算用
	float distance_y;//y同士の距離の計算用

	float two_widths;//2つの幅を合わせる用
	float two_heights;//2つの高さを合わせる用

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


	float GetX() { return x; };
	float GetY() { return y; };

	float GetWidth() { return width; };
	float GetHeight() { return height; };

	bool GetDirection() { return direction; };//キャラの向きを返す　0:右 1:左

};

