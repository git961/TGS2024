#pragma once
#include "ObjectBase.h"

class FragileWall : public ObjectBase
{
private:
	int fragile_wall_img;				// 脆い壁の画像

	float hp;							// 体力

public:
	FragileWall();
	~FragileWall();

	void Update();						// 更新処理
	void Draw() const;					// 描画処理
};