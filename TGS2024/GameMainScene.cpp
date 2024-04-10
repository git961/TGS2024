#include "GameMainScene.h"

GameMainScene::GameMainScene() {

}

GameMainScene::~GameMainScene() {

}

void GameMainScene::Update() {
	input.InputUpdate();
}

void GameMainScene::Draw() const {
		DrawFormatString(0, 0, 0xffffff, "GameMain");
}

AbstractScene* GameMainScene::Change() {
	//if (change == TRUE) {
	//	return new GameOverScene;
	//}
	return this;
}