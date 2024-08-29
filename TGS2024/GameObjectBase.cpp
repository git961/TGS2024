#include "GameObjectBase.h"
#include "GameMainScene.h"

GameObjectBase::GameObjectBase(class GameMainScene* set_game_main)
{
	game_main = set_game_main;
}

GameObjectBase::~GameObjectBase()
{
	game_main = nullptr;
}