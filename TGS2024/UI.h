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
	int score_img;//スコアアイコン画像
	int dyna_img;//ダイナマイト残弾
	int btnB_img[2];
	int btnY_img[2];
	int tuto_backimg[4];
	float alpha;
	float alpha_flg;

	float x, y;
	int player_hp;
	int heart_num;//表示するhpの数
	int dyna_num;//表示するダイナマイトの数
	int btn_num;
	int btn_cnt;

public:
	UI(int set_hp,int set_dyna_num);
	~UI();

	void Update(int set_hp,int set_dyna_num);
	void Draw() const;
	void UpdateTutorial(Player* player);
	void DrawTutorial(Player* player) const;

};