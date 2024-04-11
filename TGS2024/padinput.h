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

	//�P�����A�b�v�f�[�g
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
			LongPressBtnflg[i] = nowBtn[i];

			//�P���󂯎�����獡�̔ԍ��Ai���󂯎��
			if (Btnflg[i] == 1) {
				Btnnum = i;
			}

			//���\���L�[�`�F�b�N
			if (Btnflg[2] == 1) {
				LongBtnnum = 2;
			}
			//�E�\���L�[�`�F�b�N
			if (Btnflg[3] == 1) {
				LongBtnnum = 3;
			}

		}

	}

	//�v���C���[�̈ړ��p�A�b�v�f�[�g
	//void InputMoveUpdate() {
	//	//���͏�Ԃ��擾
	//	GetJoypadXInputState(DX_INPUT_PAD1, &getkey);
	//}

	//���v�b�V���p
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

	//���������Ă���ԗp
	int LongPressBtn(int getbtn)
	{
		if (LongPressBtnflg[LongBtnnum] == 1) {
			//�����ꂽ�{�^���̔ԍ�==�󂯎�����l��������
			if (LongBtnnum == getbtn) {
				return TRUE;
			}
		}

	}




};


