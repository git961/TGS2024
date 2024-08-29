#pragma once

class GameObjectBase
{
private:
	class GameMainScene* game_main = nullptr;
public:
	GameObjectBase(class GameMainScene* set_game_main);
	virtual ~GameObjectBase();
	class GameMainScene* GetGameMainScene() { return game_main; }
};