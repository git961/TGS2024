#pragma once
#include <math.h>
#include "DxLib.h"
#include "ObjectBase.h"

class CharacterBase : public ObjectBase
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
};

