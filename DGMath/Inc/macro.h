#pragma once

#ifdef DG_MATH_EXPORT
#define DG_MATH_DLL __declspec(dllexport)
#else
#define DG_MATH_DLL __declspec(dllimport)
#endif
