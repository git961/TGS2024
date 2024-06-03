#pragma once
#include "AbstractScene.h"
#include "TitleScene.h"
#include "AnimScene.h"

class HelpScene : public AbstractScene
{
private:

public:
	HelpScene();
	~HelpScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

