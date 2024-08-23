#pragma once

#define BLOCKSIZE 64
#define BLOCK_HALFSIZE BLOCKSIZE/2

#define FIELD_WIDTH 11520 //ワールド全体の幅 1280*8
#define FIELD_HEIGHT 720 //ワールド全体の高さ

#define map_blockmax_x FIELD_WIDTH / BLOCKSIZE
#define map_blockmax_y 12

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define WINDOW_HALFX SCREEN_WIDTH/2
#define WINDOW_HALFY SCREEN_HEIGHT/2

#define DYNAMITE_MAXNUM 5

#define _USE_MATH_DEFINES       // M_PI使用用

//デグリーからラジアンに変換
#define DEGREE_RADIAN(_deg) (M_PI*(_deg)/180.0)

// 敵の最大数
#define ENEMYMAXNUM				20
#define ROLLING_ENEMY_MAXNUM	20
#define LONG_LEGS_ENEMY_MAXNUM	1
#define HARD_ENEMY_MAXNUM		1
#define REBOUND_ENEMY_MAXNUM	1

// ギミックの最大数
#define LIFT_MAXNUM				10
#define FRAGILE_WALL_MAXNUM		10
#define CAGE_DOOR_MAXNUM		10
#define MAGMA_MAXMUN			10
#define FALLING_FLOOR_MAXNUM	10
#define GEYSER_MAXNUM			10

#define ROCK_MAXNUM 100