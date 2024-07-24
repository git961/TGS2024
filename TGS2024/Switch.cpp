#include "Switch.h"

Switch::Switch()
{
	switch_img = LoadGraph("images/Stage/Gimmick/liftswitch.png");
	canmove_flg = false;
	up_down_flg = false;
}

Switch::~Switch()
{
}

void Switch::Update()
{
	//押されたら上か下かに動く
	if (canmove_flg == true)
	{
		//下に居たら
		if (up_down_flg == false)
		{
			//上に上がる

		}
		else
		{
			//上に居たら下に下がる

		}
	}
}