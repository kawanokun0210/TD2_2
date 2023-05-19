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

class DX
{
public:

	void Initialize();

	void Update();

	void Draw();

private:
	WinApp* newApp = nullptr;

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

};

