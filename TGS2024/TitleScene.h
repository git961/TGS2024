#pragma once
#include "AbstractScene.h"
#include "AnimScene.h"
#include "HelpScene.h"
#include "EndScene.h"

class TitleScene : public AbstractScene
{
private:

public:
	TitleScene();
	~TitleScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};