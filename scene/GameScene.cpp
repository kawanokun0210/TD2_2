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

	//triangleData_[0].position[0] = { -0.5f,-0.5f,0.0f,1.0f };
	//triangleData_[0].position[1] = { 0.0f,0.5f,0.0f,1.0f };
	//triangleData_[0].position[2] = { 0.5f,-0.5f,0.0f,1.0f };
	//triangleData_[0].material = { 1.0f,1.0f,1.0f,1.0f };

	//triangleData_[1].position[0] = { -0.5f,-0.5f,0.5f,1.0f };
	//triangleData_[1].position[1] = { 0.0f,0.0f,0.0f,1.0f };
	//triangleData_[1].position[2] = { 0.5f,-0.5f,-0.5f,1.0f };
	//triangleData_[1].material = { 1.0f,1.0f,1.0f,1.0f };

	//for (int i = 0; i < 2; i++)
	//{
	//	transform_[i] = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	//}

	//triangleDrawA_ = false;
	//triangleDrawB_ = false;

	//spriteData_.LeftTop[0] = { 0.0f,0.0f,0.0f,1.0f };
	//spriteData_.RightDown[0] = { 640.0f,360.0f,0.0f,1.0f };
	//spriteData_.LeftTop[1] = { 0.0f,0.0f,0.0f,1.0f };
	//spriteData_.RightDown[1] = { 640.0f,360.0f,0.0f,1.0f };
	//spriteData_.material = { 1.0f,1.0f,1.0f,1.0f };
	//spriteTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	//spriteDraw_ = false;

	//sphereTransform_ = { {0.4f,0.4f,0.4f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	//sphereMaterial_ = { 1.0f,1.0f,1.0f,1.0f };

	//sphereDraw_ = false;

	//objectDraw_ = false;

	directionalLight_.color = { 1.0f,1.0f,1.0f,1.0f };
	directionalLight_.direction = { 0.0f,-1.0f,0.0f };
	directionalLight_.intensity = 1.0f;

	//texture_ = 0;
	//uvResourceNum_ = 0;
	//engine_->SettingTexture("Resource/uvChecker.png", uvResourceNum_);

	//monsterBallResourceNum_ = 1;
	//engine_->SettingTexture("Resource/monsterBall.png", monsterBallResourceNum_);

	//for (int i = 0; i < 2; i++)
	//{
	//	triangle_[i] = new Triangle();
	//	triangle_[i]->Initialize(dxCommon_, engine_);
	//}

	//for (int i = 0; i < 2; i++)
	//{
	//	sprite_[i] = new Sprite();
	//	sprite_[i]->Initialize(dxCommon_, engine_);
	//}

	//sphere_ = new Sphere();
	//sphere_->Initialize(dxCommon_, engine_);

	//object_[0] = new Object();

	//object_[0]->Initialize(dxCommon_, engine_, "Resource/", "axis.obj");

	//object_[1] = new Object();

	//object_[1]->Initialize(dxCommon_, engine_, "Resource/", "plane.obj");

	//for (int i = 0; i < 2; i++) {
	//	objectTransform_[i] = {{0.4f,0.4f,0.4f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};
	//	objectMaterial_[i] = {1.0f,1.0f,1.0f,1.0f};
	//}

	//objectTransform_[1] = { {0.4f,0.4f,0.4f},{0.0f,0.0f,0.0f},{1.0f,-1.0f,0.0f} };

	floor_ = new Floor();
	floor_->Inisialize(engine_, dxCommon_);

	cameraTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-5.0f} };
}

void GameScene::Update()
{
	//XINPUT_STATE joyState;
	input_->Update();

	for (int i = 0; i < 2; i++)
	{
		/*if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
			return;
		}*/
		//if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			transform_[i].rotate.y += 0.01f;
		//}
		worldMatrix_ = MakeAffineMatrix(transform_[i].scale, transform_[i].rotate, transform_[i].translate);
	}

	if (input_->PushKey(DIK_SPACE)) {
		sound_->PlayWave(soundDataHandle_, true);
	}

	
}

void GameScene::Draw()
{
	floor_->Draw(cameraTransform_, directionalLight_);
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