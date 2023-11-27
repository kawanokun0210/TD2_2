#include "Clear.h"

void Clear::Initialize(MyEngine* engine, DirectXCommon* dxCommon) {
	engine_ = engine;
	dxCommon_ = dxCommon;
}

void Clear::Update() {
	time++;
	if (time >= 60) {
		sceneNo = SELECT;
	}
}

void Clear::Draw() {

}

void Clear::Finalize() {

}