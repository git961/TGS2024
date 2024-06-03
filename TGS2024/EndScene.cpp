#include "EndScene.h"

EndScene::EndScene()
{

}

EndScene::~EndScene()
{

}

void EndScene::Update()
{

}

void EndScene::Draw() const
{
	SetFontSize(20);
	DrawFormatString(10, 10, 0xffffff, "End");

}

AbstractScene* EndScene::Change()
{
	// 終了
	//return nullptr;

	return this;
}
