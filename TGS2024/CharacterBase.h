#pragma once
#include "ObjectBase.h"

class GameMainScene;

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

	void Update(GameMainScene* gamemain) override{};
	void Draw() const override{};
	void HitReaction(ObjectBase* character) override {};

	void HitCheckB(struct Boxvertex set_box_vertex)
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

