#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
	change_cnt = 180;
}

GameOverScene::~GameOverScene()
{

}

void GameOverScene::Update()
{
	input.InputUpdate();

	if (change_cnt > 0)
	{
		change_cnt--;
	}
}

void GameOverScene::Draw() const
{
#ifdef DEBUG
	SetFontSize(20);
	DrawFormatString(10, 10, 0xffffff, "GameOver");
	DrawFormatString(10, 30, 0xffffff, "B: Title");
	DrawFormatString(10, 50, 0xffffff, "draw_cnt: %d", change_cnt);
#endif // DEBUG

}

AbstractScene* GameOverScene::Change()
{
	if (change_cnt <= 0)
	{
		if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
		{
			// Bボタンでタイトルに遷移
			return new TitleScene;
		}
	}
	return this;
}
