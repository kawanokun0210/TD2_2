#pragma once
#include "Engine.h"
#include "Sphere.h"

class GoalBall
{
public:
	GoalBall();
	~GoalBall();

	void Initialize(MyEngine* engine, DirectXCommon* dxCommon);

	void Update();

	void Draw(Transform& transform, uint32_t index, const Transform& cameraTransform, const DirectionalLight& light);

private:
	Sphere* sphere_;

	Vector4 goalBollMaterial;
};

