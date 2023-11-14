#include "Title.h"

void Title::Initialize(MyEngine* engine, DirectXCommon* dxCommon) {
	engine_ = engine;
	dxCommon_ = dxCommon;

	/*for (int i = 0; i < 1; i++) {
		sprite_[i] = new Sprite();
		sprite_[i]->Initialize(dxCommon_, engine_);
	}

	spriteData_.LeftTop[0] = { 0.0f,0.0f,0.0f,1.0f };
	spriteData_.RightDown[0] = { 1280.0f,720.0f,0.0f,1.0f };
	spriteData_.LeftTop[1] = { 0.0f,0.0f,0.0f,1.0f };
	spriteData_.RightDown[1] = { 1280.0f,720.0f,0.0f,1.0f };
	spriteData_.material = { 0.0f,0.0f,0.0f,0.0f };
	spriteTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	directionalLight_.color = { 1.0f,1.0f,1.0f,1.0f };
	directionalLight_.direction = { 0.0f,-1.0f,0.0f };
	directionalLight_.intensity = 1.0f;*/

	//engine_->SettingTexture("Resource/uvChecker.png", 0);

}

void Title::Update() {
	/*directionalLight_.direction = Normalise(directionalLight_.direction);*/

	time++;
	if (time >= 60) {
		sceneNo = PLAY;
	}
}

void Title::Draw() {
	/*for (int i = 0; i < 1; i++) {
		sprite_[i]->Draw(spriteData_.LeftTop[i], spriteData_.RightDown[i], spriteTransform_, spriteData_.material, 0, directionalLight_);
	}*/
}

void Title::Finalize() {
	/*for (int i = 0; i < 1; i++) {
		delete sprite_[i];
	}*/
}