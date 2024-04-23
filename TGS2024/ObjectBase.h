#pragma once
#include <math.h>
#include "DxLib.h"
#include "Define.h"

struct Vec2
{
	float x;
	float y;
};
struct World
{
	float x;
	float y;
};

//vertex 頂点
struct Boxvertex
{
	//右下の頂点
	float lower_rightx;
	float lower_righty;

	//左上の頂点
	float upper_leftx;
	float upper_lefty;
};
//
////左上の頂点
//struct vertexupperleft
//{
//	float x;
//	float y;
//};

class ObjectBase
{
protected:

	Vec2 location;
	World world;
	Boxvertex box_vertex;

	float width;//幅
	float height;//高さ

	float distance_x;//x同士の距離の計算用
	float distance_y;//y同士の距離の計算用

	float two_widths;//2つの幅を合わせる用
	float two_heights;//2つの高さを合わせる用

	//opponent:意味→相手

public:
	//コンストラクタとデストラクタ
	ObjectBase() {};
	~ObjectBase() {};

	//当たり判定:何かに当たったかどうかだけ返す
	bool HitCheck(Vec2 opponent, float opponent_width, float opponent_height)
	{
		float my_center_x = width / 2;
		float my_center_y = height / 2;

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


	Vec2 GetLocation() { return location; }
	World GetWorldLocation() { return world; }

	Boxvertex GetVertex() { return box_vertex; }

	float GetWidth() { return width; }
	float GetHeight() { return height; }


	//キャラのlocationとスクリーンの原点を引いてスクリーン座標上の位置に変換
	void SetLocalPosition(float set_origin_posx, float set_origin_posy)
	{
		//ワールド座標ースクリーン座標の原点してオブジェクトのスクリーン座標を出す計算
		location.x = world.x - set_origin_posx;
		location.y = world.y - set_origin_posy;
	};

	//各頂点の座標をセット
	void SetVertex()
	{
		//右下の座標をセット
		//右下のx座標＝中心ｘ＋ボックスの半分X
		box_vertex.lower_rightx=world.x+BLOCKSIZE/2;
		//右下のy座標＝中心y＋ボックスの半分Y
		box_vertex.lower_righty = world.y + BLOCKSIZE / 2;


		//左上の座標をセット
		//左上のx座標＝中心ｘ-ボックスの半分X
		box_vertex.upper_leftx = world.x - BLOCKSIZE / 2;
		//左上のy座標＝中心y-ボックスの半分Y
		box_vertex.upper_lefty = world.y - BLOCKSIZE / 2;

	};


};