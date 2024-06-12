#pragma once
#include "GameMainScene.h"
#include "Player.h"
#include "DxLib.h"
#include "Define.h"


class UI
{
private:
	
	int heart_img;//Hp画像
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

	int player_hp;
	int heart_num;//表示するhpの数
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

};