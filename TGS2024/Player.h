#pragma once
#include "CharacterBase.h"
#include "GameMainScene.h"
#include "padinput.h"

class GameMainScene;

class Player :
    public CharacterBase
{
private:
    CharacterBase charabase;
    Input input;

    float atk_cnt_timer;//�U���������Ă���Ƃ߂�܂ł̎��Ԃ��J�E���g����p

       //�v���C���[�̏��
        bool walk;//true:�����Ă� false:�~�܂��Ă�
        bool attacking;//true:�U���� false:�U�����ĂȂ� 

        float walk_velocity_x;


        bool jump_flg;//true:�W�����v���@false:�n�ʂɋ���
        bool jump_start_flg;//�{�^���������ꂽ��
        
        float jump_timer;
        float rad;
        float sita;
        float pi = 3.1415f;


        float jump_v0;//�W�����v�̏����x
        float gravity;//�W�����v�̏d��
        float velocity_y;//y�����̑��x

        float y_ground;//�n�ʂ̍����f�o�b�N�p

public:
    Player();
    ~Player();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    //�v���C���[�U���p���[�V�����@Pickaxe�F��͂�
    void AttackPickaxe();

    void PlayerJump();

    bool GetAttacking() { return attacking; };
};

//void Player::AttackPickaxe()
//{
//    if (input.CheckBtn(XINPUT_BUTTON_Y) == TRUE)
//    {
//        //Y��������U��
//    }
//}
