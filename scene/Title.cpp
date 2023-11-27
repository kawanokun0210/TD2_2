#include "Title.h"

void Title::Initialize(MyEngine* engine, DirectXCommon* dxCommon) {
	engine_ = engine;
	dxCommon_ = dxCommon;


	sprite_ = new Sprite();
	sprite_->Initialize(dxCommon_, engine_);


	spriteData_.LeftTop[0] = { 0.0f,0.0f,0.0f,1.0f };
	spriteData_.RightDown[0] = { 640.0f,360.0f,0.0f,1.0f };
	spriteData_.LeftTop[1] = { 0.0f,0.0f,0.0f,1.0f };
	spriteData_.RightDown[1] = { 640.0f,360.0f,0.0f,1.0f };
	spriteData_.material = {1.0f,1.0f,1.0f,1.0f };
	spriteTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	directionalLight_.color = { 1.0f,1.0f,1.0f,1.0f };
	directionalLight_.direction = { 0.0f,-1.0f,0.0f };
	directionalLight_.intensity = 1.0f;

	engine_->SettingTexture("Resource/uvChecker.png", 0);

}

void Title::Update() {
	directionalLight_.direction = Normalise(directionalLight_.direction);

	time++;
	if (time >= 60) {
		sceneNo = PLAY;
	}
}

void Title::Draw() {

	sprite_->Draw(spriteData_.LeftTop[0], spriteData_.RightDown[0], spriteTransform_, spriteData_.material, 0, directionalLight_);

}

void Title::Finalize() {

	delete sprite_;

}