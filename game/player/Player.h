#pragma once
#include "Engine.h"
#include "Sphere.h"
#include "Input.h"

class Player
{
public:
	Player();
	~Player();

	void Initialize(MyEngine* engine, DirectXCommon* dxCommon);

	void Update();

	void Draw(uint32_t index, const Transform& cameraTransform, const DirectionalLight& light);

	Vector3 GetPlayerTranslate() { return playerTransform.translate; }
	bool GetIsShotMode() { return isShotMode; }

private:
	Sphere* sphere_;
	Input* input_ = nullptr;

	Vector4 playerMaterial;
	Transform playerTransform;

	// 追従対象からplayerまでのオフセット
	Vector3 offset;

	bool isShotMode;

};

