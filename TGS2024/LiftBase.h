#pragma once
#include "ObjectBase.h"

class LiftBase:public ObjectBase
{
protected:
	float move_y;//y座標の増加量
	float limit_y;//y座標の移動の限界座標入れるよう
public:

	void Down();

};