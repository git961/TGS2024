#pragma once
#ifndef FPS_H_
#define FPS_H_
#include"DxLib.h"
#include<math.h>

class fps
{
private:
	int count;
	//FPSの計測と表示を行うローカル変数の宣言
	LONGLONG nowTime;
	LONGLONG oldTime;
	LONGLONG fpsCheckTime;
	double deltaTime;
	int fpsCounter;
	int Fps;
public:

	int Time;


	fps();
	~fps();

	//関数のプロトタイプ宣言
	void wait_fanc();//FPS固定処理の関数
	void Reset_fps();//ループ前にFPS計測を初期化する関数
	void Keisoku_fps();//FPSの計測する関数
	void display_fps()const;//計測したFPSを表示する関数

	void fpsUpdate();
};

#endif

