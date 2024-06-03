#pragma once
#include "AbstractScene.h"
#include "EndCreditsScene.h"

class GameClearScene : public AbstractScene
{
private:

public:
	GameClearScene();
	~GameClearScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

