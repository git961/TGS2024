#include "GameOverScene.h"

GameOverScene::GameOverScene()
{

}

GameOverScene::~GameOverScene()
{

}

void GameOverScene::Update()
{

}

void GameOverScene::Draw() const
{
#ifdef DEBUG
	SetFontSize(20);
	DrawFormatString(10, 10, 0xffffff, "GameOver");
#endif // DEBUG

}

AbstractScene* GameOverScene::Change()
{
	//return new TitleScene;
	return this;
}
