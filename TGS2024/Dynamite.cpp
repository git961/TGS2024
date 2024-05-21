#include "Dynamite.h"

Dynamite::Dynamite(World set_xy)
{
	width = 60;
	height = 50;
	location.x = set_xy.x;
	location.y = set_xy.y;
	world.x = set_xy.x;
	world.y = set_xy.y;
	move_x = 3;
	rotation = 0;
	dynamite_img = LoadGraph("images/Player/dynamite.png");

}

Dynamite::~Dynamite()
{
}

void Dynamite::Update()
{
	world.x+=move_x;
	rotation+=0.3;
}

void Dynamite::Draw() const
{
	DrawRotaGraph(location.x, location.y, 1,rotation, dynamite_img, TRUE, 0);

}
