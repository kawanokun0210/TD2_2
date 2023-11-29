#pragma once
#include "Object.h"
#include "Engine.h"

class Floor
{
public:
	Floor();
	~Floor();

	void Inisialize(MyEngine* engine, DirectXCommon* dxCommon);

	void Update();

	void Draw(Transform& transform, uint32_t index, const Transform& cameraTransform, const DirectionalLight& light);
private:
	Object* object_;

	Vector4 floorMaterial;
};

