#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>
#include <format>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <dxgidebug.h>
#include <dxcapi.h>

struct Vector4 final {
	float x;
	float y;
	float z;
	float w;
};

class Triangle
{

public:

	void Initialize();

	void Update();

	void Release();

private:

	//クライアント領域のサイズ
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;

	ID3D12GraphicsCommandList* commandList;

	ID3D12Device* device = nullptr;

	IDxcBlob* vertexShaderBlob;
	IDxcBlob* pixelShaderBlob;

	//dxcCompilerを初期化
	IDxcUtils* dxcUtils_ = nullptr;
	IDxcCompiler3* dxcCompiler_ = nullptr;

	//RootSignature作成
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};

	//シリアライズしてバイナリにする
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	//バイナリをもとに生成
	ID3D12RootSignature* rootSignature = nullptr;

	//現時点でincludeはしないが、includeに対応するための設定を行っておく
	IDxcIncludeHandler* includeHandler = nullptr;

	//InputLayout
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[1] = {};
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};

	//BlendStateの設定
	D3D12_BLEND_DESC blendDesc{};

	//RasiterzerStateの設定
	D3D12_RASTERIZER_DESC rasterizerDesc{};

	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	//実際に生成
	ID3D12PipelineState* graphicsPipelineState = nullptr;

	//頂点リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};

	//頂点リソースの設定
	D3D12_RESOURCE_DESC vertexRespurceDesc{};

	//
	ID3D12Resource* vertexResource = nullptr;

	//
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	//
	Vector4* vertexData = nullptr;

	//
	D3D12_VIEWPORT viewport{};

	//
	D3D12_RECT scissorRect{};

};

