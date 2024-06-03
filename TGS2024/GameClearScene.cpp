#include "GameClearScene.h"

GameClearScene::GameClearScene()
{

}

GameClearScene::~GameClearScene()
{

}

void GameClearScene::Update()
{

}

void GameClearScene::Draw() const
{
#ifdef DEBUG
	SetFontSize(20);
	DrawFormatString(10, 10, 0xffffff, "GameClear");
#endif // DEBUG

}

AbstractScene* GameClearScene::Change()
{
	//return new EndCreditsScene;
	return this;
}
