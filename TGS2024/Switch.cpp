#include "Switch.h"

Switch::Switch(float set_x, float set_y)
{
	//switch_img = LoadGraph("images/Stage/Gimmick/liftswitch.png");
	//LoadDivGraph("images/Player/pickaxe.png", 8, 4, 2, 170, 170, pickaxe_img);
	LoadDivGraph("images/Stage/Gimmick/liftswitch.png", 5, 5, 1, 32, 32, switch_img);

	height = 64.0f;
	width = 64.0f;

	world.x = set_x;
	world.y = set_y;
	location.x = set_x;
	location.y = set_y;


	img_num = 0;
}

Switch::~Switch()
{
}

void Switch::Update()
{

	////押されたら上か下かに動く
	//if (canmove_flg == true)
	//{
	//	//下に居たら
	//	if (up_down_flg == false)
	//	{
	//		//上に上がる
	//	}
	//	else
	//	{
	//		//上に居たら下に下がる
	//	}
	//}
}

void Switch::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 2, 0, switch_img[img_num], TRUE);
}
