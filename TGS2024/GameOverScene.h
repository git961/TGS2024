#pragma once
#include "AbstractScene.h"
#include "TitleScene.h"
#include "BlackOut.h"

class GameOverScene : public AbstractScene
{
private:
	BlackOut *black_out;

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
	int alpha;
	float size;
	float x, y;
	float effect_y;

	bool select_flg;//選択できるか？

	//カーソル
	int cursor_x;
	int cursor_y;
	int cursor_move_interval;
	int cursor_num;
	int cursor_img[3];			// カーソル画像
	int cursor_img_num;			// カーソルの画像番号
	int move_cursor_se;			// カーソル移動se
	bool push_b_flg;				// Bボタンを押したか？

	bool change_flg;

	enum gameoverCursorPos
	{
		Retry,
		End
	};

	float ring_x;
	float ring_y;
	int count;
	float ring_start_x;
	bool anim_finish_flg;			// 墓アニメーションが終わったか？
	int ring_alpha;					// リングの画像不透明度
	bool lower_ring_alpha;			// リング画像の不透明度を下げるか？

	int grave_se;					// 墓の着地音
	int fallen_leaves_se;			// リスタート選択時にプレイヤーが出てくる音
	int decision_se;				// 決定se
	int cursor_anim_cnt;			// カーソルのアニメーション用カウント
	int push_b_img;

	int gameover_bgm;				// ゲームオーバーbgm

public:
	GameOverScene();
	~GameOverScene();

	void Update() override;
	void Draw() const override;
	AbstractScene* Change() override;

private:
	void RingAnimation();			// リングアニメーション
};

