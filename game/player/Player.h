#pragma once
#pragma once
#include "Sphere.h"
#include "MatrixCalculation.h"
#include "../Vertex.h"
#include "Engine.h"
class PlayerBall
{
public:
	PlayerBall();
	~PlayerBall();
	void Initialize2(MyEngine* engine, DirectXCommon* dxCommon);
	void Update();
	void Draw(Transform viewProjection, uint32_t index, const DirectionalLight& light);
	void Release();


	Sphere* player_ = nullptr;
	Transform transform_;
};
