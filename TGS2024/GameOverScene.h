#pragma once
#include "AbstractScene.h"
#include "TitleScene.h"
#include "BlackOut.h"

class GameOverScene : public AbstractScene
{
private:
	BlackOut *black_out;

	int score;
	int change_cnt;		// シーン切り替えできるようになるまでのカウント
	int volume;
	bool play_sound_flg;		// 一度だけ再生
	int gameover_se;
	int rock_effect_img[10];
	int retry_img[10];
	int font_img[10];
	int ring_img;

	int rip_img[6];//お墓画像読込
	int rip_num;
	int rip_cnt;
	int rock_num;
	bool rock_flg;
	float alpha;
	float size;
	float x, y;
	float effect_y;

	bool select_flg;//選択できるか？

	//カーソル
	int cursor_x;
	int cursor_y;
	int cursor_move_interval;
	int cursor_num;
	int cursor_img;			// カーソル画像
	int move_cursor_se;			// カーソル移動se
	bool push_b_flg;				// Bボタンを押したか？

	bool change_flg;

	enum gameoverCursorPos
	{
		Retry,
		End
	};

public:
	GameOverScene(int set_score);
	~GameOverScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};

