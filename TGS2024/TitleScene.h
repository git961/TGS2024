#pragma once
#include "AbstractScene.h"
#include "AnimScene.h"
#include "EndScene.h"

class TitleScene : public AbstractScene
{
private:
	int cursor_x;
	int cursor_y;
	int cursor_start_y;
	int cursor_move_interval;
	int cursor_num;

	enum CursorPos
	{
		Start,
		End
	};

	bool push_b_flg;				// Bボタンを押したか？

	int scene_change_cnt;
	bool scene_change_flg;			//treu: 切り替える

	int change_cnt;		// シーン切り替えできるようになるまでのカウント

	int anim_cnt;

	int back_img;			// 背景画像
	int cursor_img;			// カーソル画像
	int text_img[4];

	//int volume;
	int title_bgm;
	int move_cursor_se;			// カーソル移動se
	int decision_se;			// 決定se

public:
	TitleScene();
	~TitleScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;
};