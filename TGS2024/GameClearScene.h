#pragma once
#include "AbstractScene.h"
#include "EndCreditsScene.h"

class GameClearScene : public AbstractScene
{
private:
	int change_cnt;		// シーン切り替えできるようになるまでのカウント
	int volume;
	bool se_flg;
	int gameclear_se;
	int endimg_num;//エンディング画像切り替え用
	int change_imgnum_cnt;
	int change_img_num;
	float alpha;
	float alpha2;
	bool alpha_start_flg;

	int ending_img[10];

public:
	GameClearScene();
	~GameClearScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

