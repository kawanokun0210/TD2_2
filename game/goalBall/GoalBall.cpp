#include "GoalBall.h"

GoalBall::GoalBall()
{
}

GoalBall::~GoalBall()
{
	delete sphere_;
}

void GoalBall::Initialize(MyEngine* engine, DirectXCommon* dxCommon)
{
	sphere_ = new Sphere;
	sphere_->Initialize(dxCommon, engine);
	goalBollMaterial = { 1.0f,1.0f,1.0f,1.0f };
}

void GoalBall::Update()
{
}

void GoalBall::Draw(Transform& transform, uint32_t index, const Transform& cameraTransform, const DirectionalLight& light)
{
	sphere_->Draw(goalBollMaterial, transform, index, cameraTransform, light);
}
