#include "GameMainScene.h"


GameMainScene::GameMainScene() {
	player=new Player;

	enemy = new Enemy(walk);

	ac = new AttackCheck;
	checkhit = false;
}


GameMainScene::~GameMainScene() {
	delete enemy;
}

void GameMainScene::Update() {
	input.InputUpdate();
	fp.fpsUpdate();

	if (enemy != nullptr)
	{
		if (player->HitCheck(enemy->GetX(), enemy->GetY(), enemy->GetWidth(), enemy->GetHeight()) == true) {
			checkhit = true;
		}
		else {
			checkhit = false;
		}
	}

	//��͂��������Ɠ������Ă邩�̃`�F�b�N

	//�v���C���[
	if (player != nullptr)
	{
		player->Update(this);
	}

	//�v���C���[�̍U��
	if (ac != nullptr) {
			ac->Update(this,player);
	}

	// �G�l�~�[�X�V����
	if (enemy != nullptr)
	{
		enemy->Update(this);
	}

#ifdef DEBUG
	if (input.CheckBtn(XINPUT_BUTTON_A) == TRUE)
	{
		enemy->Damege(2);
	}
	if (enemy == nullptr)
	{
		enemy = new Enemy(walk);
	}
#endif // DEBUG

	if (enemy != nullptr)
	{
		// �G�l�~�[�폜����
		if (enemy->GetHp() <= 0)
		{
			delete enemy;
			enemy = nullptr;
		}

	}

}

void GameMainScene::Draw() const {
		DrawFormatString(0, 0, 0xffffff, "GameMain");
		fp.display_fps();

		if (checkhit == true)
		{
			DrawFormatString(0, 10, 0xffffff, "hit");
		}

		//�v���C���[�`��
		if (player != nullptr)
		{
			player->Draw();
		}

		// �G�l�~�[�`�揈��
		if (enemy != nullptr)
		{
			enemy->Draw();
		}

		//�v���C���[�U���`��
		if (ac != nullptr) {
			if (ac->GetAttackFlg() == true)
			{
				ac->Draw();
			}
		}
}

AbstractScene* GameMainScene::Change() {
	//if (change == TRUE) {
	//	return new GameOverScene;
	//}
	return this;
}