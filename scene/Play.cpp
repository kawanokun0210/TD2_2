#include "Play.h"

void Play::Initialize(MyEngine* engine, DirectXCommon* dxCommon) {
	engine_ = engine;
	dxCommon_ = dxCommon;
}

void Play::Update() {
	time++;
	if (time >= 60) {
		sceneNo = SELECT;
	}
}

void Play::Draw() {

}

void Play::Finalize() {

}