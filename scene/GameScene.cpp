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
	engine_->SettingTexture("Resource/floor.png", wallTexture_);

	for (int i = 0; i < kMaxFloor; i++) {
		floor_[i] = new Floor();
		floor_[i]->Inisialize(engine_, dxCommon_);
		//floorTransform[i] = {{10.0f,0.5f,10.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};
	}

	floorTransform[0] = { {10.0f,0.5f,10.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	floorTransform[1] = { {2.2f,0.1f,8.3f},{0.0f,0.0f,0.0f},{-4.35f,3.150f,0.0f} };
	floorTransform[2] = { {1.9f,0.1f,2.65f},{0.15f,-1.57f,-0.8f},{-0.1f,1.55f,1.95f} };


	for (int i = 0; i < kMaxWall; i++) {
		wall_[i] = new Wall();
		wall_[i]->Inisialize(engine_, dxCommon_);
		//wallTransform[i] = { {0.2f,0.5f,10.0f},{0.0f,0.0f,0.0f},{0.0f,1.0f,0.0f} };
	}

	wallTransform[0] = { {0.1f,0.35f,0.98f},{0.0f,1.57f,0.0f},{-3.1f,3.6f,-0.3f} };
	wallTransform[1] = { {0.1f,0.35f,2.36f},{0.0f,0.0f,0.0f},{-6.45f,3.6f,0.36f} };
	wallTransform[2] = { {0.1f,0.5f,4.53f},{0.0f,1.57f,0.0f},{0.59f,1.0f,-3.6f} };
	wallTransform[3] = { {0.1f,0.5f,5.31f},{0.0f,0.0f,0.0f},{5.03f,1.0f,0.0f} };

	cameraTransform_ = { {1.0f,1.0f,1.0f},{0.5f,0.0f,0.0f},{0.0f,23.0f,-40.0f} };
}

void GameScene::Update()
{
	//XINPUT_STATE joyState;
	input_->Update();

	/*if (input_->PushKey(DIK_A)) {
		for (int i = 0; i < kMaxFloor; i++) {
			floorTransform[i].rotate.y -= 0.01f;
		}

		for (int i = 0; i < kMaxFloor; i++) {
			wallTransform[i].rotate.y -= 0.01f;
		}
	}

	if (input_->PushKey(DIK_D)) {
		for (int i = 0; i < kMaxFloor; i++) {
			floorTransform[i].rotate.y += 0.01f;
		}

		for (int i = 0; i < kMaxFloor; i++) {
			wallTransform[i].rotate.y += 0.01f;
		}
	}*/

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

	if (input_->PushKey(DIK_A)) {
		cameraTransform_.rotate.y -= 0.01f;
	}

	if (input_->PushKey(DIK_D)) {
		cameraTransform_.rotate.y += 0.01f;
	}

	Transform origin = { {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	// 追従対象からカメラまでのオフセット
	Vector3 offset = { 0.0f, 23.0f, -40.0f };
	// カメラの角度から回転行列を計算する
	Matrix4x4 worldTransform = MakeRotateYmatrix(cameraTransform_.rotate.y);
	// オフセットをカメラの回転に合わせて回転させる
	offset = TransformNormal(offset, worldTransform);
	// 座標をコピーしてオフセット分ずらす
	cameraTransform_.translate.x = origin.translate.x + offset.x;
	cameraTransform_.translate.y = origin.translate.y + offset.y;
	cameraTransform_.translate.z = origin.translate.z + offset.z;


	if (input_->PushKey(DIK_SPACE)) {
		sound_->PlayWave(soundDataHandle_, true);
	}

	if (ImGui::TreeNode("Camera"))
	{
		ImGui::DragFloat3("Translate", &cameraTransform_.translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &cameraTransform_.rotate.x, 0.01f);
		ImGui::DragFloat3("Scale", &cameraTransform_.scale.x, 0.01f);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Floor1"))
	{
		ImGui::DragFloat3("Translate", &floorTransform[0].translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &floorTransform[0].rotate.x, 0.01f);
		ImGui::DragFloat3("Scale", &floorTransform[0].scale.x, 0.01f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Floor2"))
	{
		ImGui::DragFloat3("Translate", &floorTransform[1].translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &floorTransform[1].rotate.x, 0.01f);
		ImGui::DragFloat3("Scale", &floorTransform[1].scale.x, 0.01f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Floor3"))
	{
		ImGui::DragFloat3("Translate", &floorTransform[2].translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &floorTransform[2].rotate.x, 0.01f);
		ImGui::DragFloat3("Scale", &floorTransform[2].scale.x, 0.01f);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Wall1"))
	{
		ImGui::DragFloat3("Translate", &wallTransform[0].translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &wallTransform[0].rotate.x, 0.01f);
		ImGui::DragFloat3("Scale", &wallTransform[0].scale.x, 0.01f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Wall2"))
	{
		ImGui::DragFloat3("Translate", &wallTransform[1].translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &wallTransform[1].rotate.x, 0.01f);
		ImGui::DragFloat3("Scale", &wallTransform[1].scale.x, 0.01f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Wall3"))
	{
		ImGui::DragFloat3("Translate", &wallTransform[2].translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &wallTransform[2].rotate.x, 0.01f);
		ImGui::DragFloat3("Scale", &wallTransform[2].scale.x, 0.01f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Wall4"))
	{
		ImGui::DragFloat3("Translate", &wallTransform[3].translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &wallTransform[3].rotate.x, 0.01f);
		ImGui::DragFloat3("Scale", &wallTransform[3].scale.x, 0.01f);
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