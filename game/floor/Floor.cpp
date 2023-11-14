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

	floorTransform = { {10.0f,0.5f,10.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	floorMaterial = { 1.0f,1.0f,1.0f,1.0f };
}

void Floor::Update()
{
	if (ImGui::TreeNode("Floor"))
	{
		ImGui::DragFloat3("Translate", &floorTransform.translate.x, 0.05f);
		ImGui::DragFloat3("Rotate", &floorTransform.rotate.x, 0.05f);
		ImGui::DragFloat3("Scale", &floorTransform.scale.x, 0.05f);
		ImGui::TreePop();
	}
}

void Floor::Draw(uint32_t index, const Transform& cameraTransform, const DirectionalLight& light)
{
	object_->Draw(floorMaterial, floorTransform, index, cameraTransform, light);
}
