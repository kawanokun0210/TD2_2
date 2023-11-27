#include "StageSelect.h"

void StageSelect::Initialize(MyEngine* engine, DirectXCommon* dxCommon) {
	engine_ = engine;
	dxCommon_ = dxCommon;
}

void StageSelect ::Update() {
	time++;
	if (time >= 60) {
		sceneNo = SELECT;
	}
}

void StageSelect::Draw() {

}

void StageSelect::Finalize() {

}