#pragma once

// Windows API
#include <Windows.h>

// C++ Standard Library
#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>

// DirectX
#include <wrl/client.h>
#include <dxgidebug.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// DirectXMath
#include <DirectXColors.h>

// DGEngine
#include "macro.h"
#include "enum.h"

namespace DG
{
	static void ThrowIfFailed(HRESULT _hr)
	{
		if (FAILED(_hr))
			throw std::exception{};
	}
}