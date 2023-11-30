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
	goalTransform = { {0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f},{0.0f,0.6f,0.0f} };
}

void GoalBall::Update()
{
	/*if (ImGui::TreeNode("GoalBoll"))
	{
		ImGui::DragFloat3("Translate", &goalTransform.translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &goalTransform.rotate.x, 0.01f);
		ImGui::DragFloat3("Scale", &goalTransform.scale.x, 0.01f);
		ImGui::TreePop();
	}*/
}

void GoalBall::Draw(uint32_t index, const Transform& cameraTransform, const DirectionalLight& light)
{
	sphere_->Draw(goalBollMaterial, goalTransform, index, cameraTransform, light);
}
