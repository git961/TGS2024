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
		//���͏�Ԃ��擾
		GetJoypadXInputState(DX_INPUT_PAD1, &getkey);

		//�{�^������
		for (int i = 0; i < 16; i++) {
			//�O�̓��͂��󂯎��
			oldBtn[i] = nowBtn[i];
			//�����͂���Ă���{�^�����󂯎��
			nowBtn[i] = getkey.Buttons[i];
			//0���P���󂯎��
			Btnflg[i] = nowBtn[i] & ~oldBtn[i];
			//�P���󂯎�����獡�̔ԍ��Ai���󂯎��
			if (Btnflg[i] == 1) {
				Btnnum = i;
			}
		}

	}

	int CheckBtn(int getBtn) {
		//�����ꂽ�u�Ԃ�keynum�Ԗڂ̒l���P��������
		if (Btnflg[Btnnum] == 1) {
			//�����ꂽ�{�^���̔ԍ�==�󂯎�����l��������
			if (Btnnum == getBtn) {
				return TRUE;
			}
		}
		return FALSE;
	}

};


