#include "Enemy.h"

Enemy::Enemy(int set_type)
{
	// ���S���W
	x = 50;
	y = 600;

	width = 30;
	height = 30;

	move_x = 1;			// �ړ���
	move_y = 0;			// ���g�p
	hp = 10;
	attack = 10;
	speed = 3;			// �Ȃ��Ă��ǂ�

	type = set_type;

	srand(time(NULL));
	num = rand() % 10 + 1;
	if (num >= 5)
	{
		direction = true;
	}
	else
	{
		direction = false;
	}

	// �i�s���@�����Ȃ�x���W�ƈړ��������ς��
	if (direction == false)
	{
		x = 1260;
		move_x *= -1;
	}
}

Enemy::~Enemy()
{

}

void Enemy::Update(GameMainScene* gamemain)
{
	// �ړ�����
	x += speed * move_x;

	// �[�ɗ����璵�˕Ԃ�A�G���m�̓����蔻��Ŏg�p���邩��
	if (x + width / 2 > 1280 || x - width / 2 < 0)
	{
		move_x *= -1;
	}
}

void Enemy::Draw() const
{
#ifdef DEBUG
	DrawFormatString(0, 50, 0xffffff, "hp : %f", hp);

#endif // DEBUG

	// �����蔻��̃{�b�N�X
	DrawBoxAA(x - width / 2, y - width / 2, x + width / 2, y + height / 2, 0xffffff, true);
	// ���S���W
	DrawCircleAA(x, y, 1, 0xff00ff, true);

}

// ��_���[�W����
void Enemy::Damege(int damege)
{
	hp -= (float)damege;
}
