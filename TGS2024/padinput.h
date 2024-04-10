#pragma once
#pragma once
#include "DxLib.h"

#define BUTTON_NUMMAX 16

class Input
{
private:

	XINPUT_STATE getkey;
	int Btnflg[BUTTON_NUMMAX] = { 0 };
	int nowBtn[BUTTON_NUMMAX] = { 0 };
	int oldBtn[BUTTON_NUMMAX] = { 0 };
	int Btnnum = 0;

public:

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
			//１を受け取ったら今の番号、iを受け取る
			if (Btnflg[i] == 1) {
				Btnnum = i;
			}
		}

	}

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

};


