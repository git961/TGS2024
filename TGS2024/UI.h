#pragma once
#include "GameMainScene.h"
#include "Player.h"
#include "DxLib.h"
#include "Define.h"


class UI
{
private:
	
	int heart_img[6];//Hp画像
	int heart_break_img[3];
	int p_img;
	int dyna_img;//ダイナマイト残弾
	int btnB_img[2];
	int btnY_img[2];
	int btnmove_img[4];
	int tuto_backimg[10];
	float alpha;
	float alpha2;
	bool alpha_flg;
	int kanban_anim_num;
	int i;

	float x, y;

	//int hp_x, hp_y;
	int hp_x[6];
	int hp_x_num;

	bool break_flg;
	int old_hp;
	int break_num;
	int break_cnt;
	int heart_num;//表示するhpの数
	int heart_anim_num;//HP画像切り替え用
	int anim_cnt;
	int dyna_num;//表示するダイナマイトの数
	int btn_num;
	int btn_cnt;
	bool btn_flg;

public:
	UI(int set_hp,int set_dyna_num);
	~UI();

	void Update(int set_hp,int set_dyna_num);
	void Draw() const;
	void UpdateTutorial(Player* player);
	void DrawTutorial(Player* player) const;
	void HeartAnim();
	void BreakHpAnim();
	void SetBreakHpFlg(bool set_flg) { break_flg = set_flg; }
};