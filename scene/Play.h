#pragma once
#include "../IScene.h"
#include "Player.h"

class Play : public IScene
{
public:

	void Initialize(MyEngine* engine, DirectXCommon* dxCommon) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void SetCamera(Transform camera);

private:

	MyEngine* engine_;
	DirectXCommon* dxCommon_;

	// 発射するボール
	PlayerBall* player_;

	Transform camera_;
	int time;

};

