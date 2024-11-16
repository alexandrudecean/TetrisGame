#pragma once
#include "IInputManager.h"
#include "Block.h"

namespace TetrisAPI
{
	class IGame 
	{
	public:
		virtual void Update() = 0;
		virtual Block GetNextBlock() const = 0;

		virtual ~IGame() = default;
	};
}

