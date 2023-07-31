#include "Engine.h"
#include "Triangle.h"
#include "DirectX.h"
#include "externals/imgui/imgui.h"
#include "externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"

const wchar_t kWindowTitle[] = { L"CG2_WinMain" };

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	CoInitializeEx(0, COINIT_MULTITHREADED);

	//初期化
	WinApp* win_ = nullptr;
	CreateEngine* Engine = new CreateEngine;
	DirectXCommon* dxCommon = new DirectXCommon;
	Engine->Initialization(win_, kWindowTitle, 1280, 720);

	Engine->VariableInialize();

	DirectX::ScratchImage mipImages = Engine->LoadTexture("Resource/uvChecker.png");
	const DirectX::TexMetadata& metaData = mipImages.GetMetadata();
	ID3D12Resource* textureResource = Engine->CreateTextureResource(dxCommon->GetDevice(), metaData);
	Engine->UploadTextureData(textureResource, mipImages);

#pragma region ゲームループ

	MSG msg{};

	while (msg.message != WM_QUIT) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else {

			//ゲームの処理
			Engine->BeginFrame();

			ImGui_ImplDX12_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			ImGui::ShowDemoWindow();
			Engine->Update();

			Engine->Draw();

			ImGui::Render();

			Engine->EndFrame();

		}
	}

#pragma endregion

	OutputDebugStringA("Hello,DirectX!\n");

	CoUninitialize();

	Engine->Finalize();
	return 0;
}