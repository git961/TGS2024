#include "SceneManager.h"
#include "DxLib.h"

//コンストラクタ
SceneManager::SceneManager() {
	now_scene = nullptr;
	next_scene = now_scene;
}

//引数付きコンストラクタ
SceneManager::SceneManager(AbstractScene* scene)
{
	//受け取った引数を代入
	now_scene = scene;
	next_scene = now_scene;
}

SceneManager::~SceneManager()
{

}

void SceneManager::Update()
{
	if (now_scene != nullptr) {
		now_scene->Update();
	}
}

void SceneManager::Draw() const {
	//画面の初期化
	ClearDrawScreen();

	//シーンの描画
	if (now_scene != nullptr) {
		now_scene->Draw();
	}

	//裏画面の内容を表画面に反映
	ScreenFlip();
}

//遷移先の指定
AbstractScene* SceneManager::Change()
{
	next_scene = now_scene->Change();

	//遷移先が現在のシーンと違っていたら
	if (next_scene != now_scene) {
		delete now_scene;
		now_scene = next_scene;
	}

	//遷移先を返却する
	return next_scene;
}