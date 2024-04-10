#pragma once
#include "CharacterBase.h"
#include "GameMainScene.h"
class GameMainScene;

class Enemy :
    public CharacterBase
{
private:
public:

    Enemy();
    ~Enemy();

    void Update(GameMainScene* gamemain);
    void Draw() const;


};

