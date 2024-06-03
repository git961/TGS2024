#include "EndScene.h"

EndScene::EndScene()
{
	end_cnt = 300;			// 300f経過したら終了
	endflg = false;
	fps = 0;
}

EndScene::~EndScene()
{

}

void EndScene::Update()
{
	end_cnt--;

	if (end_cnt != 0)
	{
		if (end_cnt % 60 == 0)
		{
			fps++;
		}
	}
	if (end_cnt <= 0)
	{
		endflg = true;
	}
}

void EndScene::Draw() const
{
	SetFontSize(20);
	DrawFormatString(10, 10, 0xffffff, "End");
	DrawFormatString(300, 10, 0xffffff, "end_cnt: %d", end_cnt);
	DrawFormatString(300, 30, 0xffffff, "fps: %d", fps);

}

AbstractScene* EndScene::Change()
{
	if (endflg == true)
	{
		// 終了
		return nullptr;
	}

	return this;
}
