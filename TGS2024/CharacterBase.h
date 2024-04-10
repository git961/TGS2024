#pragma once
#include <math.h>
#include "DxLib.h"

//#define CHARAIMAGENUM 10;//�L�����N�^�摜�����z��̑傫��

class CharacterBase
{
protected:

	float x;
	float y;
	
	float move_x;
	float move_y;

	float hp;//�̗�
	float attack;//�U����

	float speed;

	int chara_image[10];//�L�����N�^�摜�����p

	float width;
	float height;

	float distance_x;
	float distance_y;

	float two_widths;
	float two_heights;

	//opponent:�Ӗ�������

public:
	//�R���X�g���N�^�ƃf�X�g���N�^
	CharacterBase(){};
	~CharacterBase(){};

	//�����蔻��:�����ɓ����������ǂ��������Ԃ�
	bool HitCheck(float opponent_x,float opponent_y,float opponent_center_x, float opponent_center_y)
	{
		float my_center_x = width / 2;
		float my_center_y = height / 2;

		//x���W�̑���Ǝ����̋������Βl�ő���
		distance_x = fabs(x - opponent_x);
		//2�̕�/2�𑫂�
		two_widths = my_center_x + opponent_center_x/2;

		//y���W�̑���Ǝ����̋������Βl�ő���
		distance_y = fabs(y - opponent_y);
		//2�̍���/2�𑫂�
		two_heights = my_center_y + opponent_center_y / 2;

		//���������̐�Βl��蕝���傫��������q�b�g
		if (distance_x < two_widths && distance_y<two_heights)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

};

