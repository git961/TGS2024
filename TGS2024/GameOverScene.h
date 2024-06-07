#pragma once
#include "AbstractScene.h"
#include "TitleScene.h"

class GameOverScene : public AbstractScene
{
private:
	int score;
	int change_cnt;		// シーン切り替えできるようになるまでのカウント
	int volume;
	bool play_sound_flg;		// 一度だけ再生
	int gameover_se;
public:
	GameOverScene(int set_score);
	~GameOverScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

