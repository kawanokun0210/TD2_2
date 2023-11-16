#include "Wall.h"

Wall::Wall()
{
}

Wall::~Wall()
{
	delete object_;
}

void Wall::Inisialize(MyEngine* engine, DirectXCommon* dxCommon)
{
	object_ = new Object;
	object_->Initialize(dxCommon, engine, "Resource/", "cube.obj");

	wallMaterial = { 1.0f,1.0f,1.0f,1.0f };
}

void Wall::Update()
{
}

void Wall::Draw(Transform& transform, uint32_t index, const Transform& cameraTransform, const DirectionalLight& light)
{
	object_->Draw(wallMaterial, transform, index, cameraTransform, light);
}
