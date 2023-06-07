#pragma once
#include"DirectX.h"
#include"Vector4.h"

class CreateEngine;

class Triangle {
public:
	void Initialize(DirectX* dxCommon);

	void Draw(const Vector4& a, const Vector4& b, const Vector4& c);

	void Finalize();

private:
	void SettingVertex();

private:
	CreateEngine* Engine;

	DirectX* dxCommon_;

	Vector4* vertexData_;

	ID3D12Resource* vertexResource_;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;

};

