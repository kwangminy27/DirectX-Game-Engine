#pragma once

#ifdef DG_EXPORT
#define DG_DLL __declspec(dllexport)
#else
#define DG_DLL __declspec(dllimport)
#endif
