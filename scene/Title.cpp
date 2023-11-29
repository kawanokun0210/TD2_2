#include "Title.h"

Title::Title()
{
}

Title::~Title()
{
	delete engine_;
	delete sprite_;
}

void Title::Initialize(MyEngine* engine, DirectXCommon* dxCommon) {

	input_->Input::GetInstance();
	/*input_->Initialize();*/

	engine_ = engine;
	dxCommon_ = dxCommon;

	sprite_ = new Sprite();
	sprite_->Initialize(dxCommon_, engine_);

	spriteData_.LeftTop[0] = { 0.0f,0.0f,0.0f,1.0f };
	spriteData_.RightDown[0] = { 1280.0f,720.0f,0.0f,1.0f };
	spriteData_.LeftTop[1] = { 0.0f,0.0f,0.0f,1.0f };
	spriteData_.RightDown[1] = { 1280.0f,720.0f,0.0f,1.0f };
	spriteData_.material = {1.0f,1.0f,1.0f,1.0f };
	spriteTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	directionalLight_.color = { 1.0f,1.0f,1.0f,1.0f };
	directionalLight_.direction = { 0.0f,-1.0f,0.0f };
	directionalLight_.intensity = 1.0f;

	engine_->SettingTexture("Resource/title.png", 0);

}

void Title::Update() {
	input_->Update();

	directionalLight_.direction = Normalise(directionalLight_.direction);

	if (input_->TriggerKey(DIK_SPACE)) {
		sceneNo = PLAY;
	}
}

void Title::Draw() {

	sprite_->Draw(spriteData_.LeftTop[0], spriteData_.RightDown[0], spriteTransform_, spriteData_.material, 0, directionalLight_);

}

void Title::Finalize() {

}