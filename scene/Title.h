#pragma once
#include "../IScene.h"
#include "Sprite.h"

class Title : public IScene
{
public:

	void Initialize(MyEngine* engine, DirectXCommon* dxCommon) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:

	MyEngine* engine_;
	DirectXCommon* dxCommon_;

	Sprite* sprite_;
	SpriteData spriteData_;
	Transform spriteTransform_;

	DirectionalLight directionalLight_;

	int time;

};

