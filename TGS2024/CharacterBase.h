#pragma once
#include <math.h>
#include "DxLib.h"
#include "ObjectBase.h"

//#define CHARAIMAGENUM 10;//キャラクタ画像入れる配列の大きさ


struct Vector
{
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



public:
	//コンストラクタとデストラクタ
	CharacterBase(){};
	~CharacterBase(){};


	bool GetDirection() { return direction; }//キャラの向きを返す　0:右 1:左




};

