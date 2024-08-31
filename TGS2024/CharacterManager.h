#pragma once
#include "GameObjectBase.h"
class CharacterManager :
    public GameObjectBase
{
private:
    int total_object_num;//生成するオブジェクトの数を入れる用

    class ObjectBase** Objects=nullptr;
    class Player* player = nullptr;

public:
    CharacterManager(class GameMainScene* set_gamemain);
    ~CharacterManager();
    void Initialize();
    void Update();
    void Draw() const;
    void CollisionCheckObjects();
    void CollisionCheckMapChip();
};

