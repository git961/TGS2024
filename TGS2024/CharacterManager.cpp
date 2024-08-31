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
	//オブジェクト作成
	Objects[0] = new Player(GetGameMainScene());
	Objects[1] = new Enemy(GetGameMainScene());

	/*
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
*/

	//各オブジェクトの初期値入れ
	for (int i = 0; i < total_object_num; i++)
	{
		Objects[i]->Initialize(2000.0f,600.0f+50*i);
	}

}

void CharacterManager::Update()
{
	//オブジェクトのアップデート
	for (int i = 0; i < total_object_num; i++)
	{
		if (Objects[i]) {
			Objects[i]->Update();
		}
	}

	//キャラとキャラの当たり判定
	CollisionCheckObjects();
}

void CharacterManager::Draw() const
{
	for (int i = 0; i < total_object_num; i++) {
		Objects[i]->Draw();
	}
}

void CharacterManager::CollisionCheckObjects()
{
	for (int i = 0; i < total_object_num-1; i++)
	{
		for (int j = i+1; j < total_object_num; j++) {
			if (Objects[i]->HitCheck(Objects[j]->GetWorldLocation(), Objects[j]->GetWidth(), Objects[j]->GetHeight()) == true)
			{
				//ダメージ処理
			}
		}
	}
}

