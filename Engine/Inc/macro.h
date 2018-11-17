#pragma once

#ifdef DG_ENGINE_EXPORT
#define DG_ENGINE_DLL __declspec(dllexport)
#else
#define DG_ENGINE_DLL __declspec(dllimport)
#endif

#define MAX_TEXTURE_COUNT 4
#define MAX_SAMPLER_COUNT 2

// ========== Path Key ==========
#define ROOT_PATH "RootPath"
#define SHADER_PATH "ShaderPath"
#define TEXTURE_PATH "TexturePath"
#define DATA_PATH "DataPath"
#define SOUND_PATH "SoundPath"

// ========== Shader Key ==========
#define BASIC_SHADER "BasicShader"
#define BASIC_TEX_SHADER "BasicTexShader"
#define INSTANCE_TEX_SHADER "InstanceTexShader"
#define BASIC_ANIMATION_2D_SHADER "BasicAnimation2DShader"
#define COLLIDER_SHADER "ColliderShader"
#define COLLIDER_CIRCLE_SHADER "ColliderCircleShader"
#define BUTTON_SHADER "ButtonShader"
#define CHECKBOX_SHADER "CheckboxShader"
#define RADIO_BUTTON_SHADER "RadioButtonShader"

// ========== Sampler Key ==========
#define LINEAR_SAMPLER "LinearSampler"

// ========== State Key ==========
#define ALPHA_BLEND "AlphaBlend"
#define DEPTH_DISABLE "DepthDisable"