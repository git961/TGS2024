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
	

	//当たり判定:何かに当たったかどうかだけ返す
	bool HitCheckBlock(Vec2 opponent, float opponent_width, float opponent_height, Vector set_vector)
	{
		float my_center_x = width+200 / 2 + set_vector.x;
		float my_center_y = height+200 / 2 + set_vector.y;

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
			return true;
		
		}
		else
		{
			return false;
		}

	}


	void HitCheckB(Boxvertex set_box_vertex,World set_world)
	{
		//上か下にいないって言う条件式で全部囲む

		//もしキャラがブロックより上に居たら

			//ブロックの上に乗っかる処理
			//もし自分の右下が、相手の左上よりも、下だったら

		//もしキャラクタがブロックのｘ座標の幅の内側に居たら
		if (world.x >= set_box_vertex.lower_leftx && world.x <= set_box_vertex.lower_rightx)
		{
			//もしキャラのｙ座標がブロックのｙよりも下だったら
			if (world.y < set_world.y)
			{
				//キャラの右下の頂点の高さと、ボックスの左上の頂点の高さを比べる
				if (box_vertex.lower_righty >= set_box_vertex.upper_lefty)
				{
					//右下の頂点の方が高かったら上に居るという事になる。
					world.y = set_world.y - BLOCKSIZE;
				}
			}
			else
			{
				if (box_vertex.upper_righty < set_box_vertex.lower_lefty)
				{
					world.y = set_world.y + BLOCKSIZE;
				}
			}
		}
		
		//もしキャラクタがブロックのｙ座標の幅の内側に居たら
		if (world.y<=set_box_vertex.lower_lefty && world.y>=set_box_vertex.upper_lefty)
		{
			//キャラがブロックの右に居る場合
			if (world.x >= set_world.x)
				{

					//ブロックの右にぶつかる処理
					if (box_vertex.lower_leftx < set_box_vertex.upper_rightx)
					{
						world.x = set_world.x + BLOCKSIZE;
					}
				}

			//キャラがブロックの左に居る場合
			if (world.x <= set_world.x)
				{
					//ブロックの左にぶつかる処理
					if (box_vertex.lower_rightx > set_box_vertex.upper_leftx)
					{
						world.x = set_world.x - BLOCKSIZE;
					}
				}

		}
			
		
	}


};

