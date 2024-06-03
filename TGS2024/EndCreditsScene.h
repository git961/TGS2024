#pragma once
#include "AbstractScene.h"
#include "TitleScene.h"
#include "AnimScene.h"

class EndCreditsScene : public AbstractScene
{
private:

public:
	EndCreditsScene();
	~EndCreditsScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

