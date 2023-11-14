#include "GameScene.h"

void GameScene::Initialize(MyEngine* engine, DirectXCommon* dxCommon)
{
	engine_ = engine;
	dxCommon_ = dxCommon;

	sound_ = new Sound();
	sound_->Initialize();

	input_ = Input::GetInstance();
	input_->Initialize();

	soundDataHandle_ = sound_->LoadWave("Audio/Alarm01.wav");

	directionalLight_.color = { 1.0f,1.0f,1.0f,1.0f };
	directionalLight_.direction = { 0.0f,-1.0f,0.0f };
	directionalLight_.intensity = 1.0f;

	engine_->SettingTexture("Resource/floor.png", floorTexture_);

	floor_ = new Floor();
	floor_->Inisialize(engine_, dxCommon_);

	cameraTransform_ = { {1.0f,1.0f,1.0f},{0.5f,0.0f,0.0f},{0.0f,15.0f,-30.0f} };
}

void GameScene::Update()
{
	//XINPUT_STATE joyState;
	input_->Update();

	//for (int i = 0; i < 2; i++)
	//{
	//	/*if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
	//		return;
	//	}*/
	//	//if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
	//		transform_[i].rotate.y += 0.01f;
	//	//}
	//	worldMatrix_ = MakeAffineMatrix(transform_[i].scale, transform_[i].rotate, transform_[i].translate);
	//}

	if (input_->PushKey(DIK_SPACE)) {
		sound_->PlayWave(soundDataHandle_, true);
	}

	floor_->Update();

	if (ImGui::TreeNode("Camera"))
	{
		ImGui::DragFloat3("Translate", &cameraTransform_.translate.x, 0.05f);
		ImGui::DragFloat3("Rotate", &cameraTransform_.rotate.x, 0.05f);
		ImGui::DragFloat3("Scale", &cameraTransform_.scale.x, 0.05f);
		ImGui::TreePop();
	}
	
}

void GameScene::Draw()
{
	floor_->Draw(floorTexture_, cameraTransform_, directionalLight_);
}

void GameScene::Finalize()
{
	//for (int i = 0; i < 2; i++)
	//{
	//	//triangle_[i]->Finalize();
	//	delete triangle_[i];
	//}

	//for (int i = 0; i < 2; i++)
	//{
	//	//sprite_[i]->Finalize();
	//	delete sprite_[i];
	//}

	//sphere_->Finalize();
	//for (int i = 0; i < 2; i++) {
	//	object_[i]->Finalize();
	//}
	//delete object_[0];
	//delete object_[1];

	delete floor_;

	sound_->Finalize();
	sound_->UnLoad(&soundDataHandle_);

	//delete sphere_;
	delete sound_;
	//delete input_;
}