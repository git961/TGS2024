#include "TitleScene.h"

TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Update()
{

}

void TitleScene::Draw() const
{

}

AbstractScene* TitleScene::Change()
{
	//return new AnimScene();
	//return new HelpScene();
	//return new EndScene();

	return this;
}
