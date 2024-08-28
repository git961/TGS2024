#pragma once
#include <math.h>
#include "DxLib.h"
#include "ObjectBase.h"
#include "MapIo.h"

class CharacterBase : public ObjectBase
{
protected:
	float move_x;
	float move_y;
	float hp;
	float speed;
	bool direction;				//向き　0:右 1:左
	float attack;				//攻撃力

	float old_world_x;

public:
	//コンストラクタとデストラクタ
	CharacterBase()
	{
		direction = false;
		hp = 0.0f;
		move_x = 0.0f;
		move_y = 0.0f;
		speed = 0.0f;
		attack = 0.0f;
	};

	bool GetDirection() { return direction; }//キャラの向きを返す　0:右 1:左
	float GetAttack() { return attack; }
	float GetHalfWidth() { return width / 2.0f; }
	float GetHalfHeight() { return height / 2.0f; }

	void HitCheckB(Boxvertex set_box_vertex)
	{
		//キャラがブロックの上からぶつかった場合
		if (box_vertex.lower_y <= set_box_vertex.upper_y)
		{
			world.y = world.y - move_y;
		}
		else
		{
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
		}
	};

	//床ブロックとキャラが当たっているかのチェック
	bool CollisionCheck(float set_x, float set_y)
	{
		MapIo* mapdata;
		//受け取ったワールド座標からマップデータの列colと行rowに各当する所を求める
		int col = (int)set_x / BLOCKSIZE;
		int row = (int)set_y / BLOCKSIZE;

		if ((col < 0) || (col >= map_blockmax_x) || (row < 0) || (row >= map_blockmax_y))
		{
			return false;
		}
		
		//求めた列colと行rowの場所にマップチップがあれば、当たっている
		if (mapdata->GetMapData(row, col) == 1) {
			return true;
		}

		return false;

	};

	bool CollisionCharaRight()
	{
		//キャラクタの左上の座標を入れる
		bool right_top = CollisionCheck(world.x + GetHalfWidth() - 1.0f, world.y);
		bool right_bottom = CollisionCheck(world.x + GetHalfWidth() - 1.0f,world.y + GetHalfHeight() - 1);
		return right_top || right_bottom;
	};

	bool CollisionCharaBottom()
	{
		//マップチップとキャラの下が接しているか
		bool bottom_left = CollisionCheck(world.x - GetHalfWidth(),world.y + GetHalfWidth());
		bool bottom_right = CollisionCheck(world.x + GetHalfWidth() - 1, world.y+GetHalfHeight());
		return bottom_left || bottom_right;
	};
};

