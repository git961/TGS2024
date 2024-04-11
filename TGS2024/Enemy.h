#pragma once
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

public:
    Enemy(float set_direction, int set_type);
    ~Enemy();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    void Damege(int damege);                // ��_���[�W����
};

