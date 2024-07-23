#pragma once
#include <math.h>
#include "DxLib.h"
#include "ObjectBase.h"


//#define CHARAIMAGENUM 10;//キャラクタ画像入れる配列の大きさ

//
//struct Vector
//{
//	//キャラの動いてる方向を入れる
//	float x;
//	float y;
//};



class CharacterBase
	:public ObjectBase
{
protected:

	float move_x;
	float move_y;

	float hp;//体力


	float speed;
	bool direction;//向き　0:右 1:左

	bool stop_walk_snd;//音を止めるか？

public:
	//コンストラクタとデストラクタ
	CharacterBase()
	{
		attack = 0.0f;
		direction = false;
		hp = 0.0f;
		move_x = 0.0f;
		move_y = 0.0f;
		speed = 0.0f;


	};
	~CharacterBase() {};


	bool GetDirection() { return direction; }//キャラの向きを返す　0:右 1:左
	//bool GetGroundFlg() { return ground_flg; }


	/*
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

		}
		else
		{
			return false;
		}

	}*/


	void HitCheckB(Boxvertex set_box_vertex)
	{

		/*
		//もしキャラクタがブロックのｘ座標の幅の内側に居たら
		if (world.x >= set_box_vertex.lower_leftx && world.x <= set_box_vertex.lower_rightx)
		{
			//もしキャラのｙ座標がブロックのｙよりも下だったら
			if (world.y < set_world.y)
			{
				//キャラの右下の頂点の高さと、ボックスの左上の頂点の高さを比べる
				if (box_vertex.lower_righty > set_box_vertex.upper_lefty)
				{
					//右下の頂点の方が高かったら上に居るという事になる。

					world.y = set_world.y - height/2-BLOCKSIZE;
					ground_flg = true;
				}
				else {
					//ground_flg = false;
				}
			}
			else
			{
				//ブロックの下にいる
				if (box_vertex.upper_righty < set_box_vertex.lower_lefty)
				{
					world.y = set_world.y + height/2+BLOCKSIZE;
				}
				else
				{

				}
			}
		}

		*/

		//キャラがブロックの左からぶつかった場合
		if (box_vertex.right_x >= set_box_vertex.left_x)
		{
			world.x = world.x - move_x;
		}

		//キャラがブロックの右からぶつかった場合
		if (box_vertex.left_x <= set_box_vertex.right_x)
		{
			world.x = world.x - move_x;
		}

		//}

		//}


	};

};

