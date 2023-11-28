#include "Player.h"
#include "Engine.h"

PlayerBall::PlayerBall() {};
PlayerBall::~PlayerBall() {

}

void PlayerBall::Initialize2(MyEngine* engine, DirectXCommon* dxCommon) {
	player_ = new Sphere;
	player_->Initialize(dxCommon, engine);
	transform_.scale = { 0.5f,0.5f,0.5f };
	transform_.rotate = { 0.0f,0.0f,0.0f };
	transform_.translate = { 0.0f,1.0f,0.0f };

	

};

void PlayerBall::Update() {

};

void PlayerBall::Draw( Transform viewProjection, uint32_t index, const DirectionalLight& light) {
	player_->Draw({ 1.0f,1.0f,1.0f,1.0f }, transform_, index, viewProjection, light);
};

void PlayerBall::Release() {

}