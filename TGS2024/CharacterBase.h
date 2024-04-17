#pragma once
#include <math.h>
#include "DxLib.h"
#include "ObjectBase.h"

//#define CHARAIMAGENUM 10;//キャラクタ画像入れる配列の大きさ


struct Vector
{
	//キャラの動いてる方向を入れる
	float x;
	float y;
};



class CharacterBase
	:public ObjectBase
{
protected:
	
	Vector vector;

	float move_x;
	float move_y;

	float hp;//体力
	float attack;//攻撃力

	float speed;
	bool direction;//向き　0:右 1:左

	int chara_image[10];//キャラクタ画像入れる用

	float edge_list[4][4];
	bool is_check_edge[4];

public:
	//コンストラクタとデストラクタ
	CharacterBase(){};
	~CharacterBase(){};


	bool GetDirection() { return direction; }//キャラの向きを返す　0:右 1:左



	//当たり判定:何かに当たったかどうかだけ返す
	bool HitCheckBlock(Vec2 opponent, float opponent_width, float opponent_height,Vector set_vector)
	{
		float my_center_x = width / 2+set_vector.x;
		float my_center_y = height / 2+set_vector.y;

		//x座標の相手と自分の距離を絶対値で測る
		distance_x = fabs(location.x - opponent.x);
		//2つの幅/2を足す
		two_widths = my_center_x + opponent_width / 2;

		//y座標の相手と自分の距離を絶対値で測る
		distance_y = fabs(location.y - opponent.y);
		//2つの高さ/2を足す
		two_heights = my_center_y + opponent_height / 2;

		//もし距離の絶対値より幅が大きかったらヒット
		if (distance_x < two_widths && distance_y < two_heights)
		{
			//return true;

			//判定
			for (int i = 0; i < 4; i++)
			{
				//使用しない軸ならcontinue
				if (is_check_edge[i] == false)
				{
					continue;
				}

				for (int y = edge_list[i][1]; y <= edge_list[i][3]; y++)
				{
					for (int x = edge_list[i][0]; x <= edge_list[i][2]; x++)
					{
						//当たり

					}
				}

			}
		}
		else
		{
			return false;
		}

	}


};

