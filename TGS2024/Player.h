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

public:
    Player();
    ~Player();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    //�v���C���[�U���p���[�V�����@Pickaxe�F��͂�
    void AttackPickaxe();
};

//void Player::AttackPickaxe()
//{
//    if (input.CheckBtn(XINPUT_BUTTON_Y) == TRUE)
//    {
//        //Y��������U��
//    }
//}
