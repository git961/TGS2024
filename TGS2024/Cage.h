#pragma once
#include "ObjectBase.h"

class Cage : public ObjectBase
{
private:
	int cage_img;						// 檻の画像
	int cage_grate_img;					// 檻の格子の画像

public:
	Cage();
	~Cage();

	void Update();						// 更新処理
	void Draw() const;					// 描画処理
};

