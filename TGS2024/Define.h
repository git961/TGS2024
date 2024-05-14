#pragma once

#define BLOCKSIZE 64
#define BLOCK_HALFSIZE BLOCKSIZE/2

#define map_blockmax_x 2560 / BLOCKSIZE
#define map_blockmax_y 720 / BLOCKSIZE

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define FIELD_WIDTH 2560 //ワールド全体の幅
#define FIELD_HEIGHT 720 //ワールド全体の高さ

#define WINDOW_HALFX SCREEN_WIDTH/2
#define WINDOW_HALFY SCREEN_HEIGHT/2

#define ENEMYMAXNUM 1

#define _USE_MATH_DEFINES       // M_PI使用用

//デグリーからラジアンに変換
#define DEGREE_RADIAN(_deg) (M_PI*(_deg)/180.0f)