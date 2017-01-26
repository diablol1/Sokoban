#pragma once

namespace gs
{
	enum class GameStates
	{
		PLAY,
		EXIT
	};
}

namespace tt
{
	enum class TileTypes
	{
		NONE,
		WALL,
		BOX,
		FINISH,
		BOX_ON_FINISH
	};
}

namespace dt
{
	enum class Directions
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
}