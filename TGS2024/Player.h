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

        bool jump;//true:�W�����v�� false:�n�ʂɂ���
        float old_y;

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
