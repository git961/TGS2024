#include "EndCreditsScene.h"

EndCreditsScene::EndCreditsScene()
{
	change_cnt = 180;
}

EndCreditsScene::~EndCreditsScene()
{

}

void EndCreditsScene::Update()
{
	input.InputUpdate();

	if (change_cnt > 0)
	{
		change_cnt--;
	}
}

void EndCreditsScene::Draw() const
{
#ifdef DEBUG
	SetFontSize(20);
	DrawFormatString(10, 10, 0xffffff, "EndCredits");
	DrawFormatString(10, 30, 0xffffff, "B: Title");
	DrawFormatString(10, 50, 0xffffff, "draw_cnt: %d", change_cnt);
#endif // DEBUG

}

AbstractScene* EndCreditsScene::Change()
{
	if (change_cnt <= 0)
	{
		if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
		{
			// Bボタンでタイトルに遷移
			return new TitleScene();
		}
	}
	//return new AnimScene();

	return this;
}
