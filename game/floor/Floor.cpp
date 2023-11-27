#include "Floor.h"

Floor::Floor()
{
}

Floor::~Floor()
{
	delete object_;
}

void Floor::Inisialize(MyEngine* engine, DirectXCommon* dxCommon)
{
	object_ = new Object;
	object_->Initialize(dxCommon, engine, "Resource/", "cube.obj");

	floorMaterial = { 1.0f,1.0f,1.0f,1.0f };
}

void Floor::Update()
{
}

void Floor::Draw(Transform& transform, uint32_t index, const Transform& cameraTransform, const DirectionalLight& light)
{
	object_->Draw(floorMaterial, transform, index, cameraTransform, light);
}
