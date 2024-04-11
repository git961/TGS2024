#include "GameMainScene.h"


GameMainScene::GameMainScene() {
	player=new Player;
	enemy=new Enemy;
	ac = new AttackCheck;
	checkhit = false;
}


GameMainScene::~GameMainScene() {

}

void GameMainScene::Update() {
	input.InputUpdate();
	fp.fpsUpdate();

	//�v���C���[�������Ɠ������Ă邩�̃`�F�b�N
	if (player->HitCheck(enemy->GetX(), enemy->GetY(), enemy->GetWidth(), enemy->GetHeight())==true) {
		checkhit = true;
	}
	else {
		checkhit = false;
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

		//�G�`��
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