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

	void Move();

	void SetTransform(Vector3 pos);
	void SetGravity(float velo);
	void SetVelo(Vector3 velo);

	Vector3 GetPlayerTranslate() { return playerTransform.translate; }
	float GetRadius() { return radius; }
	bool GetIsShotMode() { return isShotMode; }

private:
	Sphere* sphere_;
	Input* input_ = nullptr;

	Vector4 playerMaterial;
	Transform playerTransform;
	float radius = 0.5f;

	// 追従対象からplayerまでのオフセット
	Vector3 offset;
	Vector3 velo_;

	bool isShotMode;
	bool isAttack;
	float gravity_;

};

