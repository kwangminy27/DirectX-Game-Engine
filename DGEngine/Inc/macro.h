#pragma once

#ifdef DG_ENGINE_EXPORT
#define DG_ENGINE_DLL __declspec(dllexport)
#else
#define DG_ENGINE_DLL __declspec(dllimport)
#endif