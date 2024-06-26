#pragma once
#include "AbstractScene.h"
#include "TitleScene.h"
#include "Player.h"

class Player;

class EndCreditsScene : public AbstractScene
{
private:
	Player* player;

	int text_x;
	int text_y;
	int timer;
	int score;
	int tmp_score;
	int num[5];				// 表示画像の要素番号（５桁分）
	int change_cnt;		// シーン切り替えできるようになるまでのカウント
	int volume;
	int volume_timer;
	int text_img[13];	// 使用素材のテキスト画像
	int num_img[10];	// スコアで使う数字画像
	int push_b_img;
	int credits_bgm;

public:
	EndCreditsScene(int set_score);
	~EndCreditsScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

