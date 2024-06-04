#pragma once
#include "AbstractScene.h"
#include "EndCreditsScene.h"

class GameClearScene : public AbstractScene
{
private:
	int change_cnt;		// シーン切り替えできるようになるまでのカウント
public:
	GameClearScene();
	~GameClearScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

