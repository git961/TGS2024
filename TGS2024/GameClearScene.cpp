#include "GameClearScene.h"

GameClearScene::GameClearScene()
{
	change_cnt = 180;
}

GameClearScene::~GameClearScene()
{

}

void GameClearScene::Update()
{
	input.InputUpdate();

	if (change_cnt > 0)
	{
		change_cnt--;
	}
}

void GameClearScene::Draw() const
{
#ifdef DEBUG
	SetFontSize(20);
	DrawFormatString(10, 10, 0xffffff, "GameClear");
	DrawFormatString(10, 30, 0xffffff, "B: EndCredits");
	DrawFormatString(10, 50, 0xffffff, "draw_cnt: %d", change_cnt);

#endif // DEBUG

}

AbstractScene* GameClearScene::Change()
{
	if (change_cnt <= 0)
	{
		if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
		{
			// Bボタンでエンドロールに遷移
			return new EndCreditsScene;
		}
	}
	return this;
}
