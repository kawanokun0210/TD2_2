#pragma once
#include "Sphere.h"
#include "MatrixCalculation.h"
#include "../Vertex.h"

class PlayerBall
{
public:
	PlayerBall();
	~PlayerBall();
	void Initialize2();
	void Update();
	void Draw(Transform transfrom, uint32_t index, Transform viewProjection);
	void Release();
	Sphere* player_ = nullptr;
	DirectionalLight directionalLight_;
};

