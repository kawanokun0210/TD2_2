#include "Engine.h"
#include "GameManager.h"

const wchar_t kWindowTitle[] = { L"CG2_WinMain" };

//Windowsアプリでのエントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	D3DResourceLeakChecker leakCheck;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	Microsoft::WRL::ComPtr<ID3D12Device> device;

	//COM初期化
	CoInitializeEx(0, COINIT_MULTITHREADED);

	//初期化
	MyEngine* engine = new MyEngine;
	engine->Initialize(kWindowTitle, 1280, 720);

	GameManager* gameManager = new GameManager(engine, engine->GetDirectXCommon());

	gameManager->Run();

	delete engine;
	delete gameManager;

	return 0;
}