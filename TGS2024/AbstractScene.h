#pragma once
#include "padinput.h"
class AbstractScene
{
public:
	Input input;
	int change;

	virtual void Update() = 0;
	virtual void Draw() const = 0;
	virtual AbstractScene* Change() = 0;
};