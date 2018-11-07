#pragma once

#ifdef DG_NETWORK_EXPORT
#define DG_NETWORK_DLL __declspec(dllexport)
#else
#define DG_NETWORK_DLL __declspec(dllimport)
#endif
#pragma once

#define STREAM_BUFFER_DEFAULT_SIZE 1024
#define BIT_STREAM_BUFFER_DEFAULT_SIZE 256
