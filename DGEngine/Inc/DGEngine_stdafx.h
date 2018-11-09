#pragma once

#pragma warning(disable:4251)

// Windows API
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <conio.h>

// C++ Standard Library
#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// DirectX
#include <wrl/client.h>
#include <dxgidebug.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d2d1.h>
#include <dwrite.h>

#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

// DirectXMath
#include <DirectXColors.h>

// DirectXTK
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
#include <ScreenGrab.h>
#include <Audio.h>

// DGEngine
#include "macro.h"
#include "enum.h"
#include "type.h"

namespace DG
{
	static void ThrowIfFailed(HRESULT _hr)
	{
		if (FAILED(_hr))
			throw std::exception{};
	}
}