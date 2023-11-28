#include "Play.h"

void Play::Initialize(MyEngine* engine, DirectXCommon* dxCommon) {
	engine_ = engine;
	dxCommon_ = dxCommon;
	//player_->Initialize2();
	Transform origin = { {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	// 追従対象からカメラまでのオフセット
	Vector3 offset = { 0.0f, 23.0f, -40.0f };
	// カメラの角度から回転行列を計算する
	Matrix4x4 worldTransform = MakeRotateYmatrix(camera_.rotate.y);
	// オフセットをカメラの回転に合わせて回転させる
	offset = TransformNormal(offset, worldTransform);
	// 座標をコピーしてオフセット分ずらす
	camera_.translate.x = origin.translate.x + offset.x;
	camera_.translate.y = origin.translate.y + offset.y;
	camera_.translate.z = origin.translate.z + offset.z;
	
	
}

void Play::Update() {
	time++;
	if (time >= 60) {
		sceneNo = SELECT;
	}
}

void Play::Draw() {
	//player_->Draw(camera_directionalLight_);
}

void Play::Finalize() {

}

void Play::SetCamera(Transform camera) {
	camera_ = camera;
}