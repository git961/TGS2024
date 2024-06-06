#pragma once
#include "AbstractScene.h"
#include "TitleScene.h"
#include "AnimScene.h"

class EndCreditsScene : public AbstractScene
{
private:
	int text_x;
	int text_y;
	int change_cnt;		// シーン切り替えできるようになるまでのカウント
	int volume;
	int credits_bgm;

public:
	EndCreditsScene();
	~EndCreditsScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

