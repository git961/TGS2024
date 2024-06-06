#pragma once
#include <DxLib.h>

class Score
{
private:
	int score_x;
	int score_y;
	int score;
	int tmp_score;
	int num[5];				// 表示画像の要素番号（５桁分）
	int shifting_value;		// 画像表示時のx座標のずれる値
	int num_img[10];

public:
	Score();
	~Score();

	void Update();
	void Draw() const;

	void SetScore(int set_score) { score += set_score; }
};