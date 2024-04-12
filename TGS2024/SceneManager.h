#pragma once
#include "AbstractScene.h"
class SceneManager : public AbstractScene
{
private:
	AbstractScene* now_scene;
	AbstractScene* next_scene;

public:
	SceneManager();
	SceneManager(AbstractScene* scene);
	~SceneManager();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;

};

