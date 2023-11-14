#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "../Vertex.h"
#include "Engine.h"
#include "Triangle.h"
#include "Sprite.h"
#include "Sphere.h"
#include "Object.h"
#include "Input.h"
#include "Sound.h"
#include "Floor.h"

class GameScene
{
public:
	void Initialize(MyEngine* engine, DirectXCommon* dxCommon);

	void Update();

	void Draw();

	void Finalize();

private:
	MyEngine* engine_;
	DirectXCommon* dxCommon_;

	Transform transform_[2];
	Matrix4x4 worldMatrix_;

	Transform cameraTransform_;

	uint32_t floorTexture_;

	DirectionalLight directionalLight_;

	Floor* floor_;

	Sound* sound_;
	SoundData soundDataHandle_;

	Input* input_ = nullptr;
};