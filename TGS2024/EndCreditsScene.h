#pragma once
#include "AbstractScene.h"
#include "TitleScene.h"
#include "AnimScene.h"

class EndCreditsScene : public AbstractScene
{
private:
	int text_x;
	int text_y;
	int timer;
	int score;
	int change_cnt;		// シーン切り替えできるようになるまでのカウント
	int volume;
	int text_img[12];	// 使用素材のテキスト画像
	int num_img[10];	// スコアで使う数字画像
	int credits_bgm;

public:
	EndCreditsScene(int set_score);
	~EndCreditsScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

