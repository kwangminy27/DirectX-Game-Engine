#include "DGEngine_stdafx.h"
#include "core.h"

#include "device.h"
#include "timer.h"
#include "path_manager.h"
#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/rendering_manager.h"
#include "Rendering/shader_manager.h"
#include "Rendering/shader.h"

using namespace std;
using namespace DG;

MESSAGE_LOOP Core::state_ = MESSAGE_LOOP::RUN;

void Core::Initialize(wstring const& _class_name, wstring const& _window_name, HINSTANCE _instance, int _icon)
{
	try
	{
		instance_ = _instance;

		_RegisterClass(_class_name, _icon);
		_CreateWindow(_class_name, _window_name);

		_CreateTimer();

		Device::singleton()->Initialize(window_);
		PathManager::singleton()->Initialize();
		ResourceManager::singleton()->Initialize();
		RenderingManager::singleton()->Initialize();

		timer_->Initialize();
	}
	catch (exception const& _e)
	{
		cerr << _e.what() << endl;
	}
	catch (...)
	{
		cerr << "Core::Initialize" << endl;
	}
}

void Core::Run()
{
	MSG message{};
	while (Core::state_ == MESSAGE_LOOP::RUN)
	{
		if (PeekMessage(&message, nullptr, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			timer_->Update();

			_Logic();
		}
	}
}

void Core::_Release()
{
	RenderingManager::singleton().reset();
	ResourceManager::singleton().reset();
	PathManager::singleton().reset();

#ifdef _DEBUG
	Device::singleton()->ReportLiveObjects();
#endif
	Device::singleton().reset();
}

LRESULT Core::_WindowProc(HWND _window, UINT _message, WPARAM _w_param, LPARAM _l_param)
{
	switch (_message)
	{
	case WM_DESTROY:
		Core::state_ = MESSAGE_LOOP::EXIT;
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(_window, _message, _w_param, _l_param);
}

void Core::_RegisterClass(wstring const& _class_name, int _icon)
{
	WNDCLASSEX wcex{};
	wcex.cbSize = sizeof(wcex);
	wcex.lpfnWndProc = Core::_WindowProc;
	wcex.hInstance = instance_;
	wcex.hIcon = LoadIcon(instance_, MAKEINTRESOURCE(_icon));
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
	wcex.lpszClassName = _class_name.c_str();
	wcex.hIconSm = LoadIcon(instance_, MAKEINTRESOURCE(_icon));
	if (!RegisterClassEx(&wcex))
		throw exception{ "RegisterClassEx" };
}

void Core::_CreateWindow(wstring const& _class_name, wstring const& _window_name)
{
	window_ = CreateWindowEx(
		NULL,
		_class_name.c_str(),
		_window_name.c_str(),
		WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr,
		nullptr,
		instance_,
		nullptr
	);

	if (!window_)
		throw exception{ "CreateWindowEx" };

	RECT rc{ 0, 0, static_cast<int>(RESOLUTION::WIDTH), static_cast<int>(RESOLUTION::HEIGHT) };
	AdjustWindowRectEx(&rc, WS_CAPTION | WS_SYSMENU, false, NULL);
	MoveWindow(window_, 160, 90, rc.right - rc.left, rc.bottom - rc.top, true);

	ShowWindow(window_, SW_SHOW);
}

void Core::_CreateTimer()
{
	timer_ = unique_ptr<Timer, function<void(Timer*)>>{ new Timer, [](Timer* _p) {
		delete _p;
	} };
	time_scale_ = 1.f;
}

void Core::_Logic()
{
	float delta_time = timer_->delta_time() * time_scale_;

	_Input(delta_time);
	_Update(delta_time);
	_LateUpdate(delta_time);
	_Collision(delta_time);
	_Render(delta_time);
}

void Core::_Input(float _time)
{
}

void Core::_Update(float _time)
{
}

void Core::_LateUpdate(float _time)
{
}

void Core::_Collision(float _time)
{
}

void Core::_Render(float _time)
{
	auto const& device = Device::singleton();

	device->Clear();

	ShaderManager::singleton()->FindShader("BasicShader")->SetShader();
	ResourceManager::singleton()->FindMesh("ColorTri")->Render();

	device->Present();
}
