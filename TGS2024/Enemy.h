#pragma once
#define DEBUG		// �f�o�b�O�p�A������#ifdef DEBUG�̏���������Ȃ��Ȃ�

#include <stdlib.h>
#include <time.h>
#include "CharacterBase.h"
#include "GameMainScene.h"

class GameMainScene;

// �G�̎��
enum EnemyType
{
    walk,       // ���s
    roll        // �]����
};

class Enemy : public CharacterBase
{
private:
    int type;       // 0:���s�@1:�]����
    int num;        // �X�|�[���ʒu�ݒ�p

public:
    Enemy(int set_type);
    ~Enemy();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    void Damege(int damege);                // ��_���[�W����

    float GetHp() { return hp; }            // hp�擾
};

