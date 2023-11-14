#include "Engine.h"
#include "GameScene.h"


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

	GameScene* gameScene = new GameScene();
	gameScene->Initialize(engine, engine->GetDirectXCommon());

	while (true)
	{
		//windowのメッセージを最優先で処理させる
		if (WinApp::GetInstance()->Procesmessage())
		{
			break;
		}

		//ゲームの処理
		engine->BeginFrame();

		gameScene->Update();

		gameScene->Draw();

		engine->EndFrame();
	}

	//解放処理
	gameScene->Finalize();

	engine->Finalize();

	delete engine;
	delete gameScene;

	CoUninitialize();

	return 0;
}