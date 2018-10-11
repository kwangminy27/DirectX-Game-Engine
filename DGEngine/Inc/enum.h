#pragma once

enum class MESSAGE_LOOP
{
	EXIT,
	RUN
};

enum class RESOLUTION
{
	WIDTH = 800,
	HEIGHT = 600
};

enum class SHADER_TYPE
{
	VERTEX,
	PIXEL,
	END
};

enum class CONSTANT_BUFFER_SHADER_TYPE
{
	VERTEX = 0x1,
	PIXEL = 0x2
};

enum class COMPONENT_TYPE
{
	TRANSFORM,
	RENDERER,
	CAMERA,
	MATERIAL,
	END
};

enum class USER_COMPONENT_TYPE
{
	PLAYER = static_cast<int>(COMPONENT_TYPE::END),
	MONSTER,
	END
};

enum class CAMERA_TYPE
{
	PERSPECTIVE,
	ORTHOGONAL
};

enum class RENDER_STATE_TYPE
{
	RASTERIZER,
	DEPTH_STENCIL,
	BLEND,
	END
};

enum class GAME_MODE
{
	_2D,
	_3D
};
