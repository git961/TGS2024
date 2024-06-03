#pragma once
#include "AbstractScene.h"
#include "TitleScene.h"

class GameOverScene : public AbstractScene
{
private:

public:
	GameOverScene();
	~GameOverScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

