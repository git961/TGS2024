#include "CharacterManager.h"
#include "Player.h"

CharacterManager::CharacterManager(GameMainScene* set_gamemain):
GameObjectBase(set_gamemain) {
}

CharacterManager::~CharacterManager()
{
}

void CharacterManager::Initialize()
{
	total_object_num = 0;
	//生成するオブジェクトがいくつあるか数える
	GetGameMainScene();
	//mapiogetしてケース文で生成するやつtotal_object_numでカウントする
	//
}

void CharacterManager::Update()
{
}

void CharacterManager::Draw() const
{
}

