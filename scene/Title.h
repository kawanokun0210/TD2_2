#pragma once
#include "../IScene.h"
#include "Sprite.h"
#include "Engine.h"
#include "Input.h"


class Title : public IScene
{
public:
	Title();
	~Title();

	void Initialize(MyEngine* engine, DirectXCommon* dxCommon) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:

	MyEngine* engine_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;

	Sprite* sprite_ = nullptr;
	SpriteData spriteData_{0};
	Transform spriteTransform_{0};

	DirectionalLight directionalLight_{0};
};

