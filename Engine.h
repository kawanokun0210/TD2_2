#pragma once
#include "DirectX.h"
#include <dxcapi.h>
#include "Vector3.h"
#include "Vector4.h"
#include "Triangle.h"
#include "MatrixCalculation.h"

#include "externals/imgui/imgui.h"
#include "externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"
#include "externals/DirectXTex/DirectXTex.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#pragma comment(lib,"dxcompiler.lib")

class CreateEngine
{
public:
	void Initialize();

	void Initialization(WinApp* win, const wchar_t* title, int32_t width, int32_t height);

	void BeginFrame();

	void EndFrame();

	void Finalize();

	void Update();

	void Draw();

	void VariableInialize();

	void DrawTriangle(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& material);

	static DirectX::ScratchImage LoadTexture(const std::string& filePath);

	static ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metaData);

	static void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);
 
private:
	static WinApp* win_;
	static	DirectXCommon* dxCommon_;

	CreateTriangle* triangle_[3];

	int triangleCount_;

	IDxcUtils* dxcUtils_;
	IDxcCompiler3* dxcCompiler_;

	IDxcIncludeHandler* includeHandler_;

	ID3DBlob* signatureBlob_;
	ID3DBlob* errorBlob_;
	ID3D12RootSignature* rootSignature_;

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc_{};

	D3D12_BLEND_DESC blendDesc_{};

	IDxcBlob* vertexShaderBlob_;

	IDxcBlob* pixelShaderBlob_;

	D3D12_RASTERIZER_DESC rasterizerDesc_{};

	ID3D12PipelineState* graphicsPipelineState_;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;

	D3D12_VIEWPORT viewport_{};
	D3D12_RECT scissorRect_{};

	D3D12_INPUT_ELEMENT_DESC inputElementDescs_[1];

	Transform transform_;
	Matrix4x4 worldMatrix_;

	//頂点リソースにデータを書き込む
	/*Vector4 vertexData_;*/

	IDxcBlob* CompileShader(
		//CompileShaderするShaderファイルへのパス
		const std::wstring& filePath,
		//Compielerに使用するProfile
		const wchar_t* profile,
		//初期化で生成したものを3つ
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler
	);

	void InitializeDxcCompiler();
	void CreateRootSignature();
	void CreateInputlayOut();
	void BlendState();
	void RasterizerState();
	void InitializePSO();
	void ViewPort();
	void ScissorRect();
};