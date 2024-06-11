#pragma once
#include "AbstractScene.h"
#include "AnimScene.h"
#include "EndScene.h"

class TitleScene : public AbstractScene
{
private:
	double pickaxe_x;			// アニメーション時のつるはしx座標
	double pickaxe_y;			// アニメーション時のつるはしy座標
	int cursor_x;
	int cursor_y;
	double degree;				// 画像の角度（デグリー）
	double radian;				// 画像の角度（ラジアン）
	int cursor_start_y;
	int cursor_move_interval;
	int cursor_num;
	int crack_x;				// 岩のヒビx座標
	int crack_y;				// 岩のヒビy座標
	double distance_x;			// つるはしとヒビのx座標距離
	double distance_y;			// つるはしとヒビのy座標距離
	double distance;			// つるはしとヒビの距離
	int count;
	bool text_up_flg;			// テキストを上に動かすか？
	bool anim_stop_flg;			// アニメーションが終了したか？

	float start_x;
	float start_y;
	float tmp_sin;
	double speed;					// つるはし落下速度

	float start_text_y;
	float end_text_y;
	float tmp_start_text_y;
	float tmp_end_text_y;

	enum CursorPos
	{
		Start,
		End
	};

	bool push_b_flg;			// Bボタンを押したか？
	int scene_change_cnt;
	bool scene_change_flg;		//treu: 切り替える

	int change_cnt;				// シーン切り替えできるようになるまでのカウント

	int anim_cnt;
	int pickaxe_anim_cnt;		// つるはしを振るアニメーションカウント
	int rock_break_num;			// 岩の画像番号

	int back_img;				// 背景画像
	int cursor_img;				// カーソル画像
	int pickaxe_img[3];			// つるはし画像
	int text_img[4];
	int rock_break_img[7];		// タイトル名に重なっている岩

	int pickaxe_img_num;		// つるはし画像番号

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

private:
	void PickaxeRotation();			// つるはし回転アニメーション
	void CrumblingRock();			// 岩が崩れるアニメーション
	void PadOperation();			// パッド操作
	void ValueAssignment();			// テキストが動く際の値の割り当て
	void MoveText();				// テキストを下から上に出す処理
	void TextPositioning();			// テキスト位置決定処理
	void PickaxeAnimation();		// つるはしアニメーション
};