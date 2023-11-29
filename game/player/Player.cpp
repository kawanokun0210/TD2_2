#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	delete sphere_;
}

void Player::Initialize(MyEngine* engine, DirectXCommon* dxCommon)
{
	input_ = Input::GetInstance();
	input_->Initialize();

	sphere_ = new Sphere;
	sphere_->Initialize(dxCommon, engine);

	isAttack = false;
	isShotMode = false;

	playerMaterial = { 1.0f,1.0f,1.0f,1.0f };
	playerTransform = { {0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f},{0.0f,0.6f,-9.0f} };
}

void Player::Update()
{


	if (input_->PushKey(DIK_A)) {
		playerTransform.rotate.y += 0.01f;
	}

	if (input_->PushKey(DIK_D)) {
		playerTransform.rotate.y -= 0.01f;
	}

	if (input_->PushKey(DIK_RETURN)) {
		isShotMode = true;
	}

	if (isShotMode == 0) {

		Transform origin = { {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.6f,0.0f} };
		offset = { 0.0f, 0.0f, -9.0f };

		// カメラの角度から回転行列を計算する
		Matrix4x4 worldTransform = MakeRotateYmatrix(playerTransform.rotate.y);
		// オフセットをカメラの回転に合わせて回転させる
		offset = TransformNormal(offset, worldTransform);
		// 座標をコピーしてオフセット分ずらす
		playerTransform.translate.x = origin.translate.x + offset.x;
		playerTransform.translate.y = origin.translate.y + offset.y;
		playerTransform.translate.z = origin.translate.z + offset.z;
	}

	if (isShotMode) {
		if (input_->PushKey(DIK_SPACE)) {
			isAttack = true;
		}
	}

	if (isAttack) {
		// キャラクターの移動速さ
		const float kCharacterSpeed = 1.0f;

		// キャラの移動
		Vector3 kVelocity(0, 0, kCharacterSpeed);

		kVelocity = Normalise(kVelocity);
		kVelocity.x *= kCharacterSpeed;
		kVelocity.y *= kCharacterSpeed;
		kVelocity.z *= kCharacterSpeed;

		kVelocity = TransformNormal(kVelocity, MakeAffineMatrix(playerTransform.scale, playerTransform.rotate, playerTransform.translate));

		playerTransform.translate.x += kVelocity.x;
		playerTransform.translate.y += kVelocity.y;
		playerTransform.translate.z += kVelocity.z;
	}

	/*if (input_->PushKey(DIK_W)) {
		playerTransform.translate.y += 0.01f;
	}

	if (input_->PushKey(DIK_S)) {
		playerTransform.translate.y -= 0.01f;
	}*/

	if (ImGui::TreeNode("Player"))
	{
		ImGui::DragFloat3("Translate", &playerTransform.translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &playerTransform.rotate.x, 0.01f);
		ImGui::DragFloat3("Scale", &playerTransform.scale.x, 0.01f);
		ImGui::TreePop();
	}
}

void Player::Draw(uint32_t index, const Transform& cameraTransform, const DirectionalLight& light)
{
	sphere_->Draw(playerMaterial, playerTransform, index, cameraTransform, light);
}

void Player::Move()
{
	offset.z += 0.01f;
}
