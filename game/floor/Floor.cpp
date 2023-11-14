#include "Floor.h"

void Floor::Inisialize(MyEngine* engine, DirectXCommon* dxCommon)
{
	object_ = new Object;
	object_->Initialize(dxCommon, engine, "Resource/", "plane.obj");
}

void Floor::Update()
{
}

void Floor::Draw(const Transform& cameraTransform, const DirectionalLight& light)
{
	object_->Draw(floorMaterial, floorTransform, 0, cameraTransform, light);
}
