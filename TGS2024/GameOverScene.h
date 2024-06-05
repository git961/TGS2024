#pragma once
#include "AbstractScene.h"
#include "TitleScene.h"

class GameOverScene : public AbstractScene
{
private:
	int change_cnt;		// シーン切り替えできるようになるまでのカウント
	int volume;
	int gameover_bgm;

public:
	GameOverScene();
	~GameOverScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

