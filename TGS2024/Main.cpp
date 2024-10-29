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
int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int)
{
	SetMainWindowText("GanGanCrush");
	ChangeWindowMode(TRUE);

	SetGraphMode(1280, 720, 32);	//画面サイズ指定

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする
	SetMouseDispFlag(FALSE);		// マウスカーソル非表示GameMainScene(true,1)
	SceneManager SceneManager(dynamic_cast<AbstractScene*>(new TitleScene));
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

	SceneManager.Finalize();
	DxLib_End(); // DXライブラリ使用の終了処理

	return 0; // ソフトの終了

}