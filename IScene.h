#pragma once
#include "Engine.h"
#include "DirectX.h"

enum SCENE {
	TITLE,
	SELECT,
	PLAY,
	CLEAR
};

class IScene
{
protected:
	static int sceneNo;

public:

	virtual void Initialize(MyEngine* engine, DirectXCommon* dxCommon) = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Finalize() = 0;

	virtual ~IScene();

	int GetSceneNo() { return sceneNo; }

};

