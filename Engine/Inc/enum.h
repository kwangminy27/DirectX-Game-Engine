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
	END
};

enum class USER_COMPONENT_TYPE
{
	PLAYER = static_cast<int>(COMPONENT_TYPE::END),
	END
};
