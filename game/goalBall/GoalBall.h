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

	void Draw(uint32_t index, const Transform& cameraTransform, const DirectionalLight& light);

	Vector3 GetGoalTranslate() { return goalTransform.translate; }
	float GetRadius() { return radius; }

private:
	Sphere* sphere_;

	Vector4 goalBollMaterial;

	Transform goalTransform;
	float radius = 0.5f;

};

