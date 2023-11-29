#pragma once
#include "Object.h"
#include "Engine.h"

class Wall
{
public:
	Wall();
	~Wall();

	void Inisialize(MyEngine* engine, DirectXCommon* dxCommon);

	void Update();

	void Draw(Transform& transform, uint32_t index, const Transform& cameraTransform, const DirectionalLight& light);
private:
	Object* object_;

	Vector4 wallMaterial;
};

