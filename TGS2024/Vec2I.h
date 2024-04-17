#pragma once
class Vec2I {
public:
	float x;
	float y;

	Vec2I(float set_x,float set_y):x(set_x),y(set_y){}

	float edge_list[4][2] = {
		// 各エッジタイプに対する値の初期化
		// ここに初期化する値を記述する
	};

};