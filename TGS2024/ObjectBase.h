#pragma once
#include <math.h>
#include "DxLib.h"
#include "Define.h"
#include "GameObjectBase.h"

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
	float right_x = 0.0f;
	float left_x = 0.0f;
	float upper_y = 0.0f;
	float lower_y = 0.0f;
};

class ObjectBase :
	public GameObjectBase
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
	ObjectBase(class GameMainScene* set_game_main);
	~ObjectBase() {};

	virtual void Initialize(float set_x,float set_y)=0;
	virtual void Update() = 0;
	virtual void Draw()const = 0;
	virtual void Finalize() = 0;

	//当たり判定:何かに当たったかどうかだけ返す
	bool HitCheck(World opponent, float opponent_width, float opponent_height)
	{
		float my_center_x = width / 2;
		float my_center_y = height / 2;

		//x座標の相手と自分の距離を絶対値で測る
		distance_x = (float)fabs(world.x - opponent.x);
		//2つの幅/2を足す
		two_widths = my_center_x + opponent_width / 2.0f;

		//y座標の相手と自分の距離を絶対値で測る
		distance_y = (float)fabs(world.y - opponent.y);
		//2つの高さ/2を足す
		two_heights = my_center_y + opponent_height / 2.0f;

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
		//右の座標をセット
		box_vertex.right_x = location.x + width / 2;

		//左の座標をセット
		box_vertex.left_x = location.x - width / 2;

		//上の座標をセット
		box_vertex.upper_y = location.y - height / 2;

		//下の座標をセット
		box_vertex.lower_y = location.y + height / 2;
	};


};