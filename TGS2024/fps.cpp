#include "fps.h"



fps::fps() {
	count = 0;
	nowTime = GetNowHiPerformanceCount();
	oldTime = nowTime;
	fpsCheckTime = GetNowHiPerformanceCount();
	deltaTime = 0;
	fpsCounter = 0;
	Fps = 0;
	Time = 0;
}
fps::~fps() {

}

void fps::fpsUpdate() {
	Keisoku_fps();
	wait_fanc();
}

void fps::wait_fanc() {
	int term;
	static int t = 0;

	//現在の時間 - 1回前に取った時間で16秒まててるか調べる 
	term = GetNowCount() - t;

	if (16 - term > 0)
		Sleep(16 - term);

	t = GetNowCount();
	return;
}

void fps::Reset_fps() {
	fpsCheckTime = GetNowHiPerformanceCount();
	Fps = 0;
	fpsCounter = 0;
}

void fps::Keisoku_fps() {
	///1ループ時点のシステム時間を取得
	oldTime = nowTime;
	nowTime = GetNowHiPerformanceCount();

	//1ループの時間経過を求める
	deltaTime = (nowTime - oldTime) / 6000000.0F;

	count += (int)deltaTime;

	//1秒間のFPSを計測する、1秒ごとに初期化する
	fpsCounter++;
	if (nowTime - fpsCheckTime > 1000000) {
		Fps = fpsCounter;
		fpsCounter = 0;
		fpsCheckTime = nowTime;
		Time += 1;
	}

}

void fps::display_fps()const {
	//FPSの表示
	SetFontSize(16);
	DrawFormatString(0, 200, 0xffffff, "FPS:%3d DELTA: %8.6fsec time:%d", Fps, deltaTime, Time);


}



