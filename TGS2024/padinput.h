#pragma once
#include "DxLib.h"

#define BUTTON_NUMMAX 16

class Input
{
private:

public:
	XINPUT_STATE getkey;

	int Btnflg[BUTTON_NUMMAX] = { 0 };
	int LongPressBtnflg[BUTTON_NUMMAX] = { 0 };
	int nowBtn[BUTTON_NUMMAX] = { 0 };
	int oldBtn[BUTTON_NUMMAX] = { 0 };
	int Btnnum = 0;
	int LongBtnnum = 0;

	

	//単押しアップデート
	void InputUpdate() {
		//入力状態を取得
		GetJoypadXInputState(DX_INPUT_PAD1, &getkey);
		
		//ボタン入力
		for (int i = 0; i < 16; i++) {
			//前の入力を受け取る
			oldBtn[i] = nowBtn[i];
			//今入力されているボタンを受け取る
			nowBtn[i] = getkey.Buttons[i];
			//0か１を受け取る
			Btnflg[i] = nowBtn[i] & ~oldBtn[i];
			LongPressBtnflg[i] = nowBtn[i];

			//１を受け取ったら今の番号、iを受け取る
			if (Btnflg[i] == 1) {
				Btnnum = i;
			}

			//左十字キーチェック
			if (Btnflg[2] == 1) {
				LongBtnnum = 2;
			}
			//右十字キーチェック
			if (Btnflg[3] == 1) {
				LongBtnnum = 3;
			}

		}

	}

	//プレイヤーの移動用アップデート
	//void InputMoveUpdate() {
	//	//入力状態を取得
	//	GetJoypadXInputState(DX_INPUT_PAD1, &getkey);
	//}

	//一回プッシュ用
	int CheckBtn(int getBtn) {
		//押された瞬間のkeynum番目の値が１だったら
		if (Btnflg[Btnnum] == 1) {
			//押されたボタンの番号==受け取った値だったら
			if (Btnnum == getBtn) {
				return TRUE;
			}
		}
		return FALSE;
	}

	//押し続けている間用
	int LongPressBtn(int getbtn)
	{
		if (LongPressBtnflg[LongBtnnum] == 1) {
			//押されたボタンの番号==受け取った値だったら
			if (LongBtnnum == getbtn) {
				return TRUE;
			}
		}

	}

	int GetPadThumbLX() { return getkey.ThumbLX; }


};


