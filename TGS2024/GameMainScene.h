#pragma once
#include "AbstractScene.h"
class GameMainScene :
    public AbstractScene
{
private:

public:
    GameMainScene();
    ~GameMainScene();

    void Update() override;
    void Draw() const override;
    AbstractScene* Change() override;
};

