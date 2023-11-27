#include "GameManager.h"

GameManager::GameManager(MyEngine* engine, DirectXCommon* dxCommon) {
	engine_ = engine;
	dxCommon_ = dxCommon;

	sceneArr[TITLE] = std::make_unique<Title>();
	sceneArr[SELECT] = std::make_unique<StageSelect>();
	sceneArr[PLAY] = std::make_unique<GameScene>();
	sceneArr[CLEAR] = std::make_unique<Clear>();

	currentSceneNo = iscene->GetSceneNo();

	sceneArr[currentSceneNo]->Initialize(engine_, dxCommon_);
}

GameManager::~GameManager() {};

int GameManager::Run() {
	while (true)
	{
		//windowのメッセージを最優先で処理させる
		if (WinApp::GetInstance()->Procesmessage())
		{
			break;
		}

		//ゲームの処理
		engine_->BeginFrame();

		prevSceneNo = currentSceneNo;
		currentSceneNo = sceneArr[currentSceneNo]->GetSceneNo();

		if (prevSceneNo != currentSceneNo) {
			sceneArr[currentSceneNo]->Initialize(engine_, dxCommon_);
			sceneArr[prevSceneNo]->Finalize();
		}

		sceneArr[currentSceneNo]->Update();

		sceneArr[currentSceneNo]->Draw();

		engine_->EndFrame();
	}

	sceneArr[currentSceneNo]->Finalize();
	engine_->Finalize();

	CoUninitialize();

	return 0;
}