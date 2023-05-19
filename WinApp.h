#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>
#include <format>


class WinApp
{

public:

	void Initialize(const int32_t kClientWidth, const int32_t kClientHeight, const wchar_t* title);

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	//クライアント領域のサイズ
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;

	WNDCLASS wc{};

	HWND hwnd = nullptr;
};

