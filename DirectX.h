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
#include "WinApp.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxcompiler.lib")

class DirectX
{
public:

	void Initialize(const int32_t kClientWidth, const int32_t kClientHeight, HWND hwnd);

	void Update(ID3D12GraphicsCommandList* commandList);

	void Draw();

	void Release();

public:

	ID3D12Debug1* debugController = nullptr;
	ID3D12InfoQueue* infoQueue = nullptr;

	//DXGIファクトリーの生成
	IDXGIFactory7* dxgiFactory = nullptr;

	//使用するアダプタ用の変数
	IDXGIAdapter4* useAdapter = nullptr;

	ID3D12Device* device = nullptr;

	//コマンドキューを生成する
	ID3D12CommandQueue* commandQueue = nullptr;
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};

	//コマンドアロケータを生成する
	ID3D12CommandAllocator* commandAllocator = nullptr;

	//コマンドリストを生成する
	ID3D12GraphicsCommandList* commandList = nullptr;

	//スワップチェーンを生成する
	IDXGISwapChain4* swapChain = nullptr;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	//ディスクリプタヒープの生成
	ID3D12DescriptorHeap* rtvDescriptorHeap = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptorHeapDesc{};

	//SwapChainからResourceを引っ張ってくる
	ID3D12Resource* swapChainResources[2] = { nullptr };

	//RTVの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};

	//RTVを2つ作るのでディスクリプタを2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];

	//TransitionBarrierの設定
	D3D12_RESOURCE_BARRIER barrier{};

	//初期値0でFenceを作る
	ID3D12Fence* fence = nullptr;
	uint64_t fanceValue;
	HANDLE fenceEvent = nullptr;

	IDXGIDebug1* debug;

};

