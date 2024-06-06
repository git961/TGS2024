#pragma once
#include "AbstractScene.h"

class EndScene : public AbstractScene
{
private:
	int end_cnt;
	bool endflg;

	int volume;
	bool se_flg;
	int end_se;


public:
	EndScene();
	~EndScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

