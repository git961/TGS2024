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
};

