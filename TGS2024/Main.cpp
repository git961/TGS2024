#include "DxLib.h"
#include "fps.h"
#include "padinput.h"
#include "AbstractScene.h"
#include "SceneManager.h"
#include "GameMainScene.h"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int
	nCmdShow)
{
	//�^�C�g����vermin�ɕύX
	SetMainWindowText("�܂��^�C�g�����܂��ĂȂ���");
	ChangeWindowMode(TRUE);

	SetGraphMode(1280, 720, 32);	//��ʃT�C�Y�w��

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	SceneManager SceneManager(dynamic_cast<AbstractScene*>(new GameMainScene));
	Input input;
	fps fp;
	//���[�v�O��FPS�v����������
	fp.Reset_fps();

	//�Q�[�����[�v
	while (ProcessMessage() != -1) {
		SceneManager.Update();
		SceneManager.Draw();
		input.InputUpdate();

		//fps�Œ�
		fp.fpsUpdate();

		if (input.CheckBtn(XINPUT_BUTTON_BACK) == TRUE) {
			break;
		}

		if (SceneManager.Change() == nullptr) {
			break;
		}

	}


	DxLib_End(); // DX���C�u�����g�p�̏I������
	return 0; // �\�t�g�̏I��

}