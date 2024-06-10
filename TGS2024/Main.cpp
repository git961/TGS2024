#include "DxLib.h"
#include "fps.h"
#include "padinput.h"
#include "AbstractScene.h"
#include "SceneManager.h"
#include "GameMainScene.h"
#include "AnimScene.h"
#include "TitleScene.h"
#include "GameOverScene.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int
	nCmdShow)
{
	//タイトルをverminに変更
	SetMainWindowText("GanGanCrush");
	ChangeWindowMode(TRUE);

	SetGraphMode(1280, 720, 32);	//画面サイズ指定

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	SceneManager SceneManager(dynamic_cast<AbstractScene*>(new GameOverScene(0)));
	Input input;
	fps fp;
	//ループ前にFPS計測を初期化
	fp.Reset_fps();

	//ゲームループ
	while (ProcessMessage() != -1)
	{
		//fps固定
		fp.fpsUpdate();

		SceneManager.Update();
		SceneManager.Draw();
		input.InputUpdate();

		if (input.CheckBtn(XINPUT_BUTTON_BACK) == TRUE) {
			break;
		}

		if (SceneManager.Change() == nullptr) {
			break;
		}

	}


	DxLib_End(); // DXライブラリ使用の終了処理
	return 0; // ソフトの終了

}