#include <Windows.h>
#include <cstdint>
#include <string>
#include <format>
#include "WinApp.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	WinApp* winApp = new WinApp;
	winApp->Initialize(kWindowWidth, kWindowHeight, L"LE2B_09_カワノ_ユウキ");

	MSG msg{};
	//ウィンドウのxボタンが押されるまでループ
	while (msg.message != WM_QUIT){
		//Windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			//ゲームの処理
		}

	}
	return 0;
}
