#pragma once
#include "../IScene.h"

class Clear : public IScene
{
public:

	void Initialize(MyEngine* engine, DirectXCommon* dxCommon) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:

	MyEngine* engine_;
	DirectXCommon* dxCommon_;

	int time;

};

