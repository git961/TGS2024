#include "CharacterManager.h"
#include "Player.h"
#include "Enemy.h"

CharacterManager::CharacterManager(GameMainScene* set_gamemain):
GameObjectBase(set_gamemain) {
}

CharacterManager::~CharacterManager()
{
}

void CharacterManager::Initialize()
{
	total_object_num = 2;
	Objects = new ObjectBase * [total_object_num];
	//生成するオブジェクトがいくつあるか数える
	GetGameMainScene();
	//mapiogetしてケース文で生成するやつtotal_object_numでカウントする
	//

	Objects[0] = new Player(GetGameMainScene());

		//マップチップに反映する
	for (int i = 0; i < map_blockmax_y; i++)
	{
		for (int j = 0; j < map_blockmax_x; j++)
		{
			switch (GetGameMainScene()->GetMapio()->GetMapData(i, j))
			{
			case 2:
			
				//enemy[total_object_num] = new Enemy((float)j * BLOCKSIZE + BLOCKSIZE / 2, (float)i * BLOCKSIZE + BLOCKSIZE / 2, false);
				break;

			}



		}
	}


}

void CharacterManager::Update()
{
}

void CharacterManager::Draw() const
{
}

