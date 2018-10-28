#pragma once

#ifdef DG_NETWORK_EXPORT
#define DG_NETWORK_DLL __declspec(dllexport)
#else
#define DG_NETWORK_DLL __declspec(dllimport)
#endif
#pragma once
