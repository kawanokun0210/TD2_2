#pragma once
#include <memory>
#include "../IScene.h"
#include "Title.h"
#include "GameScene.h"
#include "StageSelect.h"
#include "Play.h"
#include "Clear.h"

class GameManager
{
private:

	std::unique_ptr<IScene> sceneArr[4];

	int currentSceneNo;
	int prevSceneNo;

	MyEngine* engine_;
	DirectXCommon* dxCommon_;
	IScene* iscene;

public:
	GameManager(MyEngine* engine, DirectXCommon* dxCommon);
	~GameManager();

	int Run();

};

