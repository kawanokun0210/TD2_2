#pragma once
#include "Object.h"
#include "Engine.h"


class Floor
{
public:
	void Inisialize(MyEngine* engine, DirectXCommon* dxCommon);

	void Update();

	void Draw(const Transform& cameraTransform, const DirectionalLight& light);
private:
	Object* object_;
	Transform floorTransform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	Vector4 floorMaterial = { 1.0f,1.0f,1.0f,1.0f };
};

