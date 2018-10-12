#pragma once

#ifdef DG_ENGINE_EXPORT
#define DG_ENGINE_DLL __declspec(dllexport)
#else
#define DG_ENGINE_DLL __declspec(dllimport)
#endif

// ========== Path Key ==========
#define ROOT_PATH "RootPath"
#define SHADER_PATH "ShaderPath"
#define TEXTURE_PATH "TexturePath"
#define DATA_PATH "DataPath"

// ========== Shader Key ==========
#define BASIC_SHADER "BasicShader"
#define BASIC_TEX_SHADER "BasicTexShader"
#define BASIC_ANIMATION_2D_SHADER "BasicAnimation2DShader"

// ========== Sampler Key ==========
#define LINEAR_SAMPLER "LinearSampler"

// ========== State Key ==========
#define ALPHA_BLEND "AlphaBlend"
#define DEPTH_DISABLE "DepthDisable"