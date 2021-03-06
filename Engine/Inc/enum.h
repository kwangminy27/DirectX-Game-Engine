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
	ANIMATION_2D,
	COLLIDER,
	UI,
	TEXT,
	STAGE,
	TILE,
	END
};

enum class USER_COMPONENT_TYPE
{
	PLAYER = static_cast<int>(COMPONENT_TYPE::END),
	MONSTER,
	MISSILE,
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

enum class ANIMATION_2D_TYPE
{
	ATLAS,
	FRAME
};

enum class ANIMATION_OPTION
{
	LOOP,
	DESTROY
};

enum class COLLISION_GROUP_TYPE
{
	_2D,
	_3D
};

enum class COLLIDER_TYPE
{
	RECT,
	POINT,
	CIRCLE,
	OOBB,
	PIXEL
};

enum class COLLISION_CALLBACK_TYPE
{
	ENTER,
	STAY,
	LEAVE,
	END
};

enum class UI_TYPE
{
	PANEL,
	BUTTON,
	BAR
};

enum class BUTTON_STATE
{
	DISABLE,
	NORMAL,
	MOUSEON,
	CLICK,
	END
};

enum class CHECKBOX_STATE
{
	NORMAL,
	CHECKED
};

enum class CUTTING_DIR
{
	BOTTOM_TO_TOP,
	LEFT_TO_RIGHT,
	RIGHT_TO_LEFT,
	TOP_TO_BOTTOM
};

enum class TRANSFORM_FLAG
{
	SCALE = 1 << 0,
	ROTATE = 1 << 1,
	TRANSLATE = 1 << 2
};

enum class STAGE_TYPE
{
	RECT,
	ISOMETRIC,
	HONEY,
	MAX
};

enum class TILE_OPTION
{
	NORMAL,
	BLOCKED,
	MAX
};

enum class VERTEX_BUFFER_TYPE
{
	VERTEX,
	INSTANCE,
	MAX
};