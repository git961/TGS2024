#pragma once
#include <DxLib.h>

class Score
{
private:
	int score;

public:
	Score();
	~Score();

	void Update();
	void Draw() const;

	void SetScore(int set_score)
	{
		score += set_score;
	}
};