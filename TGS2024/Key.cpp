#include "Key.h"

Key::Key(int set_type, float set_x, float set_y)
{
	if (set_type == 0)
	{
		key_img[0] = LoadGraph("images/Stage/key/Blue.png");
	}
	else {
		key_img[0] = LoadGraph("images/Stage/key/Red.png");
	}

	world.x = set_x;
	world.y = set_y;

	location.x = set_x;
	location.y = set_y;
	size = 2.0f;

	width = 64.0f;
	height = 64.0f;
}

Key::~Key()
{
}

void Key::Update()
{
}

void Key::Draw() const
{
	// 宝石画像
	DrawRotaGraph((int)location.x, (int)location.y, size, 0.0, key_img[0], TRUE, 0);

}

void Key::KeyAnim()
{
}
