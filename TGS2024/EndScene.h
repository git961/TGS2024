#pragma once
#include "AbstractScene.h"
#include "Player.h"

class Player;

class EndScene : public AbstractScene
{
private:
	Player* player;

	int end_cnt;
	bool endflg;

	int volume;
	bool se_flg;
	int end_se;

	int back_img;				// 背景画像
	int thank_you_img;			// テキスト画像



public:
	EndScene();
	~EndScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

