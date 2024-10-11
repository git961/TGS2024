#pragma once
#include <math.h>
#include "DxLib.h"
#include "Define.h"

class GameMainScene;


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

struct Boxvertex
{
	float right_x = 0.0f;
	float left_x = 0.0f;
	float upper_y = 0.0f;
	float lower_y = 0.0f;
};

enum class ObjectType
{
	player,
	enemy,
	rock
};

class ObjectBase
{
protected:

	Vec2 location;
	World world;
	//vertex 頂点

	Boxvertex box_vertex;
	ObjectType my_object_type;

	float width;//幅
	float height;//高さ
	float half_width;//半分の幅
	float half_height;//半分の高さ

	float distance_x;//x同士の距離の計算用
	float distance_y;//y同士の距離の計算用

	float two_widths;//2つの幅を合わせる用
	float two_heights;//2つの高さを合わせる用

	//opponent:意味→相手


public:
	//コンストラクタとデストラクタ
	ObjectBase()
	{
		width = 0.0f;
		height = 0.0f;
		distance_x = 0.0f;
		distance_y = 0.0f;
		two_widths = 0.0f;
		two_heights = 0.0f;
		world.x = 0.0f;
		world.y = 0.0f;
		location = { 0 };
		box_vertex = { 0 };
	};
	~ObjectBase() {};

	virtual void Update(GameMainScene* gamemain)=0;
	virtual void Draw() const=0;
	virtual void HitReaction(ObjectBase* character)=0; //hitCheckがtrueだったらhitした後の処理をする

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

	//カメラの近くにいるかチェック
	bool InCameraRange(float screen_originpos_x)
	{
		if (world.x > screen_originpos_x - 100.0f && world.x < screen_originpos_x + SCREEN_WIDTH + 100)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

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

	ObjectType GetObjectType() { return my_object_type; }

};