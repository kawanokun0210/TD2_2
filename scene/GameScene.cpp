#include "GameScene.h"

GameScene::~GameScene()
{
	for (int i = 0; i < kMaxFloor; i++) {
		delete floor_[i];
	}

	for (int i = 0; i < kMaxWall; i++) {
		delete wall_[i];
	}

	delete goal_;
	delete player_;
	delete sound_;

	//delete sphere_;
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

	engine_->SettingTexture("Resource/floor.png", floorTexture_);
	engine_->SettingTexture("Resource/wall.png", wallTexture_);
	engine_->SettingTexture("Resource/goal.png", goalTexture);
	engine_->SettingTexture("Resource/player.png", playerTexture);
	engine_->SettingTexture("Resource/title.png", titleTexture);
	engine_->SettingTexture("Resource/setumei.png", setumeiTexture);
	engine_->SettingTexture("Resource/clear.png", clearTexture);
	engine_->SettingTexture("Resource/next.png", nextTexture);
	engine_->SettingTexture("Resource/haikei.png", haikeiTexture);


	for (int i = 0; i < kMaxFloor; i++) {
		floor_[i] = new Floor();
		floor_[i]->Inisialize(engine_, dxCommon_);
		floorTransform[i] = {{10.0f,0.1f,10.0f},{0.0f,0.0f,0.0f},{100.0f,50.0f,100.0f}};
	}

	/*floorTransform[0] = { {2.3f,0.1f,10.0f},{0.0f,0.0f,0.0f},{7.6f,0.0f,0.0f} };
	floorTransform[1] = { {3.0f,0.1f,8.3f},{0.0f,0.0f,0.0f},{-8.6f,0.0f,0.0f} };
	floorTransform[2] = { {5.53f,0.1f,2.0f},{0.0f,0.0f,0.0f},{-0.1f,0.0f,0.0f} };*/


	for (int i = 0; i < kMaxWall; i++) {
		wall_[i] = new Wall();
		wall_[i]->Inisialize(engine_, dxCommon_);
		wallTransform[i] = { {0.2f,0.3f,10.0f},{0.0f,0.0f,0.0f},{100.0f,0.4f,0.0f} };
	}

	/*wallTransform[0] = { {0.1f,0.3f,0.98f},{0.0f,1.57f,0.0f},{-3.1f,0.4f,1.9f} };
	wallTransform[1] = { {0.1f,0.3f,2.36f},{0.0f,0.0f,0.0f},{-8.5f,0.4f,0.8f} };
	wallTransform[2] = { {0.1f,0.3f,2.5f},{0.0f,1.57f,0.0f},{0.5f,0.4f,-1.9f} };
	wallTransform[3] = { {0.1f,0.3f,1.5f},{0.0f,0.0f,0.0f},{5.4f,0.4f,-2.0f} };*/

	// 重力の追加
	gravity_ = -9.8f / 50.0f;

	goal_ = new GoalBall;
	goal_->Initialize(engine_, dxCommon_);

	player_ = new Player;
	player_->Initialize(engine_, dxCommon_);
	player_->SetGravity(gravity_);
	cameraTransform_ = { {1.0f,1.0f,1.0f},{0.5f,0.0f,0.0f},{0.0f,23.0f,-40.0f} };

	title_ = new Sprite();
	title_->Initialize(dxCommon_, engine_);

	setumei_ = new Sprite();
	setumei_->Initialize(dxCommon_, engine_);

	clear_ = new Sprite();
	clear_->Initialize(dxCommon_, engine_);

	next_ = new Sprite();
	next_->Initialize(dxCommon_, engine_);

	haikei_ = new Sprite();
	haikei_->Initialize(dxCommon_, engine_);

	spriteData_.LeftTop[0] = { 0.0f,0.0f,0.0f,1.0f };
	spriteData_.RightDown[0] = { 1280.0f,720.0f,0.0f,1.0f };
	spriteData_.LeftTop[1] = { 0.0f,0.0f,0.0f,1.0f };
	spriteData_.RightDown[1] = { 1280.0f,720.0f,0.0f,1.0f };
	spriteData_.material = { 1.0f,1.0f,1.0f,1.0f };
	spriteTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	stageNum = TITLE2;
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

	player_->Update();
	goal_->Update();

	if (input_->PushKey(DIK_A)) {
		cameraTransform_.rotate.y += 0.01f;
	}

	if (input_->PushKey(DIK_D)) {
		cameraTransform_.rotate.y -= 0.01f;
	}

	Transform origin = { {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.6f,0.0f} };
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

	if (player_->GetIsShotMode()) {
		cameraTransform_.translate.x = player_->GetPlayerTranslate().x + offset.x;
		cameraTransform_.translate.y = player_->GetPlayerTranslate().y + offset.y;
		cameraTransform_.translate.z = player_->GetPlayerTranslate().z + offset.z;
	}

	// 判定対象AとBの座標
	Vector3 posA, posB;
	float radiusA, radiusB;

	posA = player_->GetPlayerTranslate();
	radiusA = player_->GetRadius();

	posB = goal_->GetGoalTranslate();
	radiusB = goal_->GetRadius();

	float e2b = (posB.x - posA.x) * (posB.x - posA.x) +
		(posB.y - posA.y) * (posB.y - posA.y) +
		(posB.z - posA.z) * (posB.z - posA.z);
	float r2r = (radiusA + radiusB) * (radiusA + radiusB);

	if (e2b <= r2r) {
		hitCount += 1;
		player_->Initialize(engine_, dxCommon_);
		cameraTransform_ = { {1.0f,1.0f,1.0f},{0.5f,0.0f,0.0f},{0.0f,23.0f,-40.0f} };
	}

	if (stageNum == TITLE2) {
		if (input_->PushKey(DIK_S)) {
			stageNum = SETUMEI;
		}
	}

	if (stageNum == SETUMEI) {
		if (input_->PushKey(DIK_W)) {
			stageNum = 0;
		}
	}

	if (stageNum == 0) {

		floorTransform[0] = { {20.0f,0.1f,20.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

		if (hitCount == 3) {
			if (input_->PushKey(DIK_SPACE)) {
				hitCount = 0;
				stageNum = 1;
				player_->Initialize(engine_, dxCommon_);
				cameraTransform_ = { {1.0f,1.0f,1.0f},{0.5f,0.0f,0.0f},{0.0f,23.0f,-40.0f} };
			}
		}

	}

	if (stageNum == 1) {

		floorTransform[0] = { {10.0f,0.1f,10.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

		wallTransform[0] = { {2.0f,0.3f,0.1f},{0.0f,0.0f,0.0f},{0.0f,0.4f,5.0f} };
		wallTransform[1] = { {0.1f,0.3f,2.0f},{0.0f,0.0f,0.0f},{5.0f,0.4f,0.0f} };
		wallTransform[2] = { {1.0f,0.3f,0.1f},{0.0f,0.0f,0.0f},{0.0f,0.4f,-5.0f} };
		wallTransform[3] = { {0.1f,0.3f,2.0f},{0.0f,0.0f,0.0f},{-5.0f,0.4f,0.0f} };

		if (hitCount == 3) {
			if (input_->PushKey(DIK_SPACE)) {
				hitCount = 0;
				stageNum = 2;
				player_->Initialize(engine_, dxCommon_);
				cameraTransform_ = { {1.0f,1.0f,1.0f},{0.5f,0.0f,0.0f},{0.0f,23.0f,-40.0f} };
				for (int i = 0; i < kMaxWall; i++) {
					wallTransform[i] = { {0.2f,0.3f,10.0f},{0.0f,0.0f,0.0f},{100.0f,0.4f,0.0f} };
				}
			}
		}

	}

	if (stageNum == 2) {

		floorTransform[0] = { {2.0f,0.1f,10.0f},{0.0f,0.0f,0.0f},{8.0f,0.0f,0.0f} };
		floorTransform[1] = { {2.0f,0.1f,10.0f},{0.0f,0.0f,0.0f},{-8.0f,0.0f,0.0f} };
		floorTransform[2] = { {10.0f,0.1f,2.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,8.0f} };
		floorTransform[3] = { {10.0f,0.1f,2.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-8.0f} };
		floorTransform[4] = { {10.0f,0.1f,2.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

		if (hitCount == 3) {
			if (input_->PushKey(DIK_SPACE)) {
				hitCount = 0;
				stageNum = 3;
				player_->Initialize(engine_, dxCommon_);
				cameraTransform_ = { {1.0f,1.0f,1.0f},{0.5f,0.0f,0.0f},{0.0f,23.0f,-40.0f} };
				for (int i = 0; i < kMaxWall; i++) {
					wallTransform[i] = { {0.2f,0.3f,10.0f},{0.0f,0.0f,0.0f},{100.0f,0.4f,0.0f} };
				}
			}
		}

	}

	if (stageNum == 3) {

		floorTransform[0] = { {2.0f,0.1f,10.0f},{0.0f,0.0f,0.0f},{8.0f,0.0f,0.0f} };
		floorTransform[1] = { {2.0f,0.1f,10.0f},{0.0f,0.0f,0.0f},{-8.0f,0.0f,0.0f} };
		floorTransform[2] = { {10.0f,0.1f,2.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,8.0f} };
		floorTransform[3] = { {10.0f,0.1f,2.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-8.0f} };
		floorTransform[4] = { {10.0f,0.1f,2.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

		wallTransform[0] = { {1.0f,0.3f,0.1f},{0.0f,0.0f,0.0f},{-2.0f,0.4f,2.0f} };
		wallTransform[1] = { {0.1f,0.3f,1.2f},{0.0f,0.0f,0.0f},{6.0f,0.4f,-0.8f} };
		wallTransform[2] = { {1.0f,0.3f,0.1f},{0.0f,0.0f,0.0f},{2.0f,0.4f,-2.0f} };
		wallTransform[3] = { {0.1f,0.3f,1.2f},{0.0f,0.0f,0.0f},{-6.0f,0.4f,0.8f} };

		if (hitCount == 3) {
			if (input_->PushKey(DIK_SPACE)) {
				hitCount = 0;
				stageNum = 4;
				player_->Initialize(engine_, dxCommon_);
				cameraTransform_ = { {1.0f,1.0f,1.0f},{0.5f,0.0f,0.0f},{0.0f,23.0f,-40.0f} };
				for (int i = 0; i < kMaxWall; i++) {
					wallTransform[i] = { {0.2f,0.3f,10.0f},{0.0f,0.0f,0.0f},{100.0f,0.4f,0.0f} };
				}
			}
		}

	}

	if (stageNum == 4) {

		floorTransform[0] = { {2.0f,0.1f,10.0f},{0.0f,0.0f,0.0f},{8.0f,0.0f,0.0f} };
		floorTransform[1] = { {2.0f,0.1f,10.0f},{0.0f,0.0f,0.0f},{-8.0f,0.0f,0.0f} };
		floorTransform[2] = { {10.0f,0.1f,2.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,8.0f} };
		floorTransform[3] = { {10.0f,0.1f,2.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-8.0f} };
		floorTransform[4] = { {1.5f,0.1f,5.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,4.0f} };

		wallTransform[0] = { {1.0f,0.5f,0.1f},{0.0f,0.0f,0.0f},{-0.9f,0.4f,-1.0f} };
		wallTransform[1] = { {0.1f,0.5f,1.2f},{0.0f,0.0f,0.0f},{1.5f,0.4f,1.0f} };
		wallTransform[2] = { {1.0f,0.5f,0.1f},{0.0f,0.0f,0.0f},{1.0f,0.4f,6.0f} };

		if (hitCount == 3) {
			if (input_->PushKey(DIK_SPACE)) {
				hitCount = 0;
				stageNum = CLEAR2;
				for (int i = 0; i < kMaxWall; i++) {
					wallTransform[i] = { {0.2f,0.3f,10.0f},{0.0f,0.0f,0.0f},{100.0f,0.4f,0.0f} };
				}
			}
		}

	}

	if (stageNum == CLEAR2) {
		if (input_->TriggerKey(DIK_SPACE)) {
			hitCount = 0;
			stageNum = CLEAR2;

			stageNum = TITLE2;
			player_->Initialize(engine_, dxCommon_);
			cameraTransform_ = { {1.0f,1.0f,1.0f},{0.5f,0.0f,0.0f},{0.0f,23.0f,-40.0f} };
		}
	}
	for (int i = 0; i < 5; i++) {
		if (IsCollisionAABB(
			{ 
			floorTransform[i].translate.x - floorTransform[i].scale.x,
			floorTransform[i].translate.y - floorTransform[i].scale.y,
			floorTransform[i].translate.z - floorTransform[i].scale.z },
			{
			floorTransform[i].translate.x + floorTransform[i].scale.x,
			floorTransform[i].translate.y + floorTransform[i].scale.y,
			floorTransform[i].translate.z + floorTransform[i].scale.z },
			player_->GetRadius(),player_->GetPlayerTranslate())) {
			player_->SetVelo({ 1.0f,1.0f,1.0f });
			player_->InitGravity();
			player_->SetGravity(0);
			player_->SetTransform({player_->GetPlayerTranslate().x,0.50f,player_->GetPlayerTranslate().z});
			flagTmp = true;
		}
		else if(!IsCollisionAABB(
			{
			floorTransform[i].translate.x - floorTransform[i].scale.x,
			floorTransform[i].translate.y - floorTransform[i].scale.y,
			floorTransform[i].translate.z - floorTransform[i].scale.z },
			{
			floorTransform[i].translate.x + floorTransform[i].scale.x,
			floorTransform[i].translate.y + floorTransform[i].scale.y,
			floorTransform[i].translate.z + floorTransform[i].scale.z },
			player_->GetRadius(), player_->GetPlayerTranslate())&&player_->GetIsAttack()){
			player_->SetVelo({0.95f,1.0f,0.95f});
			player_->SetGravity(gravity_);
			flagTmp = false;
		}
		
		if (IsCollisionAABB(
			{
			floorTransform[i].translate.x - floorTransform[i].scale.x,
			floorTransform[i].translate.y - floorTransform[i].scale.y,
			floorTransform[i].translate.z - floorTransform[i].scale.z },
			{
			floorTransform[i].translate.x + floorTransform[i].scale.x,
			floorTransform[i].translate.y + floorTransform[i].scale.y,
			floorTransform[i].translate.z + floorTransform[i].scale.z },
			player_->GetRadius(), player_->GetPlayerTranslate()) && player_->GetIsAttack()) {
			player_->SetVelo({ 1.0f,1.0f,1.0f });
			player_->InitVelo();
			
		}
	}

	if (player_->GetPlayerTranslate().y <= -40) {
		player_->Initialize(engine_, dxCommon_);
		cameraTransform_ = { {1.0f,1.0f,1.0f},{0.5f,0.0f,0.0f},{0.0f,23.0f,-40.0f} };
	}


	for (int i = 0; i < kMaxWall; ++i) {
		if (IsCollisionAABB(subtract(wallTransform[i].translate, wallTransform[i].scale), Add(wallTransform[i].translate, wallTransform[i].scale), player_->GetRadius(), player_->GetPlayerTranslate())) {

			if (wallTransform[i].translate.z - wallTransform[i].scale.z > player_->GetPlayerTranslate().z) {
				//player_->SetKvelocity({ 0.0f,0.0f,player_->GetkVelo().z * -1 });
				player_->SetChengerZ();
				player_->SetTransform({ player_->GetPlayerTranslate().x,player_->GetPlayerTranslate().y,wallTransform[i].translate.z - wallTransform[i].scale.z - player_->GetRadius() });
			}
			else if (wallTransform[i].translate.z + wallTransform[i].scale.z < player_->GetPlayerTranslate().z) {
				player_->SetChengerZ();
				//player_->SetKvelocity({ 0.0f,0.0f,player_->GetkVelo().z * -1 });
				player_->SetTransform({ player_->GetPlayerTranslate().x,player_->GetPlayerTranslate().y,wallTransform[i].translate.z + wallTransform[i].scale.z + player_->GetRadius() });
			}
			else if (wallTransform[i].translate.x - wallTransform[i].scale.x > player_->GetPlayerTranslate().x) {
				player_->SetChengerX();
				//player_->SetKvelocity({ player_->GetkVelo().x * -1,0.0f,0.0f });
				player_->SetTransform({ wallTransform[i].translate.x - wallTransform[i].scale.z - player_->GetRadius(),player_->GetPlayerTranslate().y ,player_->GetPlayerTranslate().z});
			}
			else if (wallTransform[i].translate.x + wallTransform[i].scale.x < player_->GetPlayerTranslate().x) {
				player_->SetChengerX();
				//player_->SetKvelocity({ player_->GetkVelo().x * -1,0.0f,0.0f });
				player_->SetTransform({ wallTransform[i].translate.x + wallTransform[i].scale.x + player_->GetRadius(),player_->GetPlayerTranslate().y,player_->GetPlayerTranslate().z });
			}




		}
	}
	/*if (input_->PushKey(DIK_SPACE)) {
		sound_->PlayWave(soundDataHandle_, true);
	}*/

	/*if (ImGui::TreeNode("Flag"))
	{
		ImGui::Text("Flag : %d", flagTmp);
		ImGui::TreePop();
	}*/
		
	/*
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
	}*/
}

void GameScene::Draw()
{

	if (stageNum == TITLE2) {
		title_->Draw(spriteData_.LeftTop[0], spriteData_.RightDown[0], spriteTransform_, spriteData_.material, titleTexture, directionalLight_);
	}

	if (stageNum == SETUMEI) {
		title_->Draw(spriteData_.LeftTop[0], spriteData_.RightDown[0], spriteTransform_, spriteData_.material, setumeiTexture, directionalLight_);
	}

	if (stageNum == CLEAR2) {
		title_->Draw(spriteData_.LeftTop[0], spriteData_.RightDown[0], spriteTransform_, spriteData_.material, clearTexture, directionalLight_);
	}

	if (hitCount == 3) {
		title_->Draw(spriteData_.LeftTop[0], spriteData_.RightDown[0], spriteTransform_, spriteData_.material, nextTexture, directionalLight_);
	}

	if (stageNum == 0) {

		floor_[0]->Draw(floorTransform[0], floorTexture_, cameraTransform_, directionalLight_);

	}


	if (stageNum == 1) {

		floor_[0]->Draw(floorTransform[0], floorTexture_, cameraTransform_, directionalLight_);

		for (int i = 0; i < 4; i++) {
			wall_[i]->Draw(wallTransform[i], wallTexture_, cameraTransform_, directionalLight_);
		}

	}

	if (stageNum == 2) {

		for (int i = 0; i < 5; i++) {
			floor_[i]->Draw(floorTransform[i], floorTexture_, cameraTransform_, directionalLight_);
		}

	}

	if (stageNum == 3) {

		for (int i = 0; i < 5; i++) {
			floor_[i]->Draw(floorTransform[i], floorTexture_, cameraTransform_, directionalLight_);
		}

		for (int i = 0; i < 4; i++) {
			wall_[i]->Draw(wallTransform[i], wallTexture_, cameraTransform_, directionalLight_);
		}

	}

	if (stageNum == 4) {

		for (int i = 0; i < 5; i++) {
			floor_[i]->Draw(floorTransform[i], floorTexture_, cameraTransform_, directionalLight_);
		}

		for (int i = 0; i < 3; i++) {
			wall_[i]->Draw(wallTransform[i], wallTexture_, cameraTransform_, directionalLight_);
		}

	}


	/*for (int i = 0; i < kMaxFloor; i++) {
		floor_[i]->Draw(floorTransform[i], floorTexture_, cameraTransform_, directionalLight_);
	}

	for (int i = 0; i < kMaxWall; i++) {
		wall_[i]->Draw(wallTransform[i], wallTexture_, cameraTransform_, directionalLight_);
	}*/

	goal_->Draw(goalTexture, cameraTransform_, directionalLight_);

	player_->Draw(playerTexture, cameraTransform_, directionalLight_);
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

bool IsCollision(const Vector3& min, const Vector3& max, const Vector3& sphereCenter, int sphereRadius) {
	bool g = false;

	// 最近接点を求める
	Vector3 closestPoint{
		std::clamp(sphereCenter.x,min.x,max.x),
		std::clamp(sphereCenter.y,min.y,max.y),
		std::clamp(sphereCenter.z,min.z,max.z)
	};

	// 最近接点と弾の中心との距離を求める
	float distance = Length({
		closestPoint.x - sphereCenter.x,
		closestPoint.y - sphereCenter.y,
		closestPoint.z - sphereCenter.z });
	// 距離が半径よりも小さければ衝突
	if (distance <= sphereRadius) {
		g = true;
	}
	else { g = false; }
	return g;
}