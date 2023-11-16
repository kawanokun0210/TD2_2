#include "GameScene.h"

GameScene::~GameScene()
{
	for (int i = 0; i < kMaxFloor; i++) {
		delete floor_[i];
	}

	for (int i = 0; i < kMaxWall; i++) {
		delete wall_[i];
	}

	//delete sphere_;
	delete sound_;
	//delete input_;
}

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

	engine_->SettingTexture("Resource/uvChecker.png", floorTexture_);

	for (int i = 0; i < kMaxFloor; i++) {
		floor_[i] = new Floor();
		floor_[i]->Inisialize(engine_, dxCommon_);
		floorTransform[i] = {{10.0f,0.5f,10.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};
	}

	for (int i = 0; i < kMaxWall; i++) {
		wall_[i] = new Wall();
		wall_[i]->Inisialize(engine_, dxCommon_);
		wallTransform[i] = { {0.2f,0.5f,10.0f},{0.0f,0.0f,0.0f},{0.0f,0.95f,0.0f} };
	}

	cameraTransform_ = { {1.0f,1.0f,1.0f},{0.5f,0.0f,0.0f},{0.0f,23.0f,-40.0f} };
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

	if (ImGui::TreeNode("Camera"))
	{
		ImGui::DragFloat3("Translate", &cameraTransform_.translate.x, 0.05f);
		ImGui::DragFloat3("Rotate", &cameraTransform_.rotate.x, 0.05f);
		ImGui::DragFloat3("Scale", &cameraTransform_.scale.x, 0.05f);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Floor1"))
	{
		ImGui::DragFloat3("Translate", &floorTransform[0].translate.x, 0.05f);
		ImGui::DragFloat3("Rotate", &floorTransform[0].rotate.x, 0.05f);
		ImGui::DragFloat3("Scale", &floorTransform[0].scale.x, 0.05f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Floor2"))
	{
		ImGui::DragFloat3("Translate", &floorTransform[1].translate.x, 0.05f);
		ImGui::DragFloat3("Rotate", &floorTransform[1].rotate.x, 0.05f);
		ImGui::DragFloat3("Scale", &floorTransform[1].scale.x, 0.05f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Floor3"))
	{
		ImGui::DragFloat3("Translate", &floorTransform[2].translate.x, 0.05f);
		ImGui::DragFloat3("Rotate", &floorTransform[2].rotate.x, 0.05f);
		ImGui::DragFloat3("Scale", &floorTransform[2].scale.x, 0.05f);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Wall1"))
	{
		ImGui::DragFloat3("Translate", &wallTransform[0].translate.x, 0.05f);
		ImGui::DragFloat3("Rotate", &wallTransform[0].rotate.x, 0.05f);
		ImGui::DragFloat3("Scale", &wallTransform[0].scale.x, 0.05f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Wall2"))
	{
		ImGui::DragFloat3("Translate", &wallTransform[1].translate.x, 0.05f);
		ImGui::DragFloat3("Rotate", &wallTransform[1].rotate.x, 0.05f);
		ImGui::DragFloat3("Scale", &wallTransform[1].scale.x, 0.05f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Wall3"))
	{
		ImGui::DragFloat3("Translate", &wallTransform[2].translate.x, 0.05f);
		ImGui::DragFloat3("Rotate", &wallTransform[2].rotate.x, 0.05f);
		ImGui::DragFloat3("Scale", &wallTransform[2].scale.x, 0.05f);
		ImGui::TreePop();
	}
	
}

void GameScene::Draw()
{
	for (int i = 0; i < kMaxFloor; i++) {
		floor_[i]->Draw(floorTransform[i], floorTexture_, cameraTransform_, directionalLight_);
	}

	for (int i = 0; i < kMaxWall; i++) {
		wall_[i]->Draw(wallTransform[i], wallTexture_, cameraTransform_, directionalLight_);
	}
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

	sound_->Finalize();
	sound_->UnLoad(&soundDataHandle_);
}