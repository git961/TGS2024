#include "Score.h"

Score::Score()
{
	score = 0;
}

Score::~Score()
{

}

void Score::Update()
{

}

void Score::Draw() const
{
	SetFontSize(20);
	DrawFormatString(300, 20, 0xffffff, "Score %d", score);
}