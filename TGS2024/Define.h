#pragma once

#define BLOCKSIZE 64
#define BLOCK_HALFSIZE BLOCKSIZE/2

#define FIELD_WIDTH 10240 //ワールド全体の幅 1280*8
#define FIELD_HEIGHT 720 //ワールド全体の高さ

#define map_blockmax_x FIELD_WIDTH / BLOCKSIZE
#define map_blockmax_y 12

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720



#define WINDOW_HALFX SCREEN_WIDTH/2
#define WINDOW_HALFY SCREEN_HEIGHT/2

#define ENEMYMAXNUM 20
#define ROLLING_ENEMY_MAXNUM 20

#define DYNAMITE_MAXNUM 5

#define _USE_MATH_DEFINES       // M_PI使用用

//デグリーからラジアンに変換
#define DEGREE_RADIAN(_deg) (M_PI*(_deg)/180.0)