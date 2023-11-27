#include "Player.h"

PlayerBall::PlayerBall() {};
PlayerBall::~PlayerBall() {

}

void PlayerBall::Initialize2() {
	directionalLight_.color = { 1.0f,1.0f,1.0f,1.0f };
	directionalLight_.direction = { 0.0f,-1.0f,0.0f };
	directionalLight_.intensity = 1.0f;
};

void PlayerBall::Update() {

};

void PlayerBall::Draw(Transform transform, uint32_t index, Transform viewProjection) {
	player_->Draw({ 1.0f,1.0f,1.0f,1.0f }, transform, index, viewProjection, directionalLight_);
};

void PlayerBall::Release() {

}
