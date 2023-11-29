#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "../Vertex.h"
#include "Engine.h"
#include "Triangle.h"
#include "Sprite.h"
#include "Sphere.h"
#include "Object.h"
#include "Input.h"
#include "Sound.h"
#include "../IScene.h"

#include "Floor.h"
#include "Wall.h"
#include "GoalBall.h"
#include "Player.h"

enum STAGE {
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4,
	STAGE5
};

class GameScene : public IScene
{
public:
	~GameScene();

	void Initialize(MyEngine* engine, DirectXCommon* dxCommon) override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:
	MyEngine* engine_;
	DirectXCommon* dxCommon_;

	Transform transform_[2];
	Matrix4x4 worldMatrix_;

	Transform cameraTransform_;

	DirectionalLight directionalLight_;

	Sound* sound_;
	SoundData soundDataHandle_;

	Input* input_ = nullptr;

private:

	// 床
	static const uint32_t kMaxFloor = 50;

	Floor* floor_[kMaxFloor];
	Transform floorTransform[kMaxFloor];
	uint32_t floorTexture_ = 0;

	// 壁
	static const uint32_t kMaxWall = 50;

	Wall* wall_[kMaxWall];
	Transform wallTransform[kMaxWall];
	uint32_t wallTexture_ = 1;

	// go-ru
	GoalBall* goal_;
	uint32_t goalTexture = 2;

	// player
	Player* player_;
	uint32_t playerTexture = 3;

	bool isAttack = false;

	uint32_t stageNum;
	uint32_t hitCount;
};