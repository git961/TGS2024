#pragma once

#define BLOCKSIZE 64
#define BLOCK_HALFSIZE BLOCKSIZE/2

#define FIELD_WIDTH 11520 //ワールド全体の幅 1280*8
#define FIELD_HEIGHT 3136 //ワールド全体の高さ (720+64)*4

#define map_blockmax_x FIELD_WIDTH / BLOCKSIZE
#define map_blockmax_y FIELD_HEIGHT / BLOCKSIZE

#define MAP_BLOCKMAX map_blockmax_x*map_blockmax_y

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define WINDOW_HALFX SCREEN_WIDTH/2
#define WINDOW_HALFY SCREEN_HEIGHT/2

#define DYNAMITE_MAXNUM 5

#define _USE_MATH_DEFINES       // M_PI使用用

//デグリーからラジアンに変換
#define DEGREE_RADIAN(_deg) (M_PI*(_deg)/180.0)

#define TOTAL_NUM 100

// 敵の最大数
#define ENEMYMAXNUM				40
#define ROLLING_ENEMY_MAXNUM	20
#define LONG_LEGS_ENEMY_MAXNUM	20
#define HARD_ENEMY_MAXNUM		3
#define REBOUND_ENEMY_MAXNUM	20

// ギミックの最大数
#define LIFT_MAXNUM				30
#define FRAGILE_WALL_MAXNUM		30
#define CAGE_DOOR_MAXNUM		20
#define MAGMA_MAXMUN			20
#define FALLING_FLOOR_MAXNUM	20
#define GEYSER_MAXNUM			20

#define KEY_MAXNUM 2

#define ROCK_MAXNUM 200

#define GREEN_GEM_MAXNUM 40