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


		//もし相手の座標が自身の座標の２００以内に居たら
		//if(world.x)

		//ブロックの上に乗っかる処理
		////もし自分の右下が、相手の左上よりも、下だったら
		//if (box_vertex.lower_righty >= set_box_vertex.upper_lefty)
		//{
		//	//相手のｙをもらって、押し上げてもらう
		//	//恐らくworldrロケーションをもらう
		//	world.y = set_world.y-BLOCKSIZE;
		//}//当たったら下降とめる

		////ブロックの下にぶつかる処理
		//if (box_vertex.upper_righty <= set_box_vertex.lower_lefty)
		//{
		//	//相手のｙをもらって、押し上げてもらう
		//	//恐らくworldrロケーションをもらう
		//	world.y = set_world.y + BLOCKSIZE;
		//}
		////ブロックにぶつかったら上昇を止める
		////すぐ下に落ちてく
		//

		//ブロックの右にぶつかる処理
		if (box_vertex.lower_leftx <= set_box_vertex.upper_rightx)
		{
			world.x = set_world.x + BLOCKSIZE;
		}

		//ブロックの左にぶつかる処理
		if (box_vertex.lower_rightx >=set_box_vertex.upper_leftx)
		{
			world.x = set_world.x - BLOCKSIZE;
		}

	}


};

