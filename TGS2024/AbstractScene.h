#pragma once
#include "padinput.h"
class AbstractScene
{
public:
	virtual ~AbstractScene(){};
	Input input;
	int change;
	virtual void Finalize(){}

	virtual void Update() = 0;
	virtual void Draw() const = 0;
	virtual AbstractScene* Change() = 0;
};