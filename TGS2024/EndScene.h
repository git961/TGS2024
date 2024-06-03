#pragma once
#include "AbstractScene.h"

class EndScene : public AbstractScene
{
private:
	int end_cnt;
	bool endflg;

	int fps;

public:
	EndScene();
	~EndScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

