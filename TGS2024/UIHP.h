#pragma once
#include "GameMainScene.h"
#include "Player.h"
#include "DxLib.h"
#include "Define.h"


class UIHP
{
private:
	int heart_img[5];//Hp画像
	int p_img[5];
	float x, y;
	int player_hp;
	int heart_num;//表示するhpの数

public:
	UIHP(int set_hp);
	~UIHP();

	void Update(int set_hp);
	void Draw() const;
};