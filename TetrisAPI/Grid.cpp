#include "Grid.h"

using namespace TetrisAPI;

Grid::Grid(const Color& emptyCellColor) :
	m_emptyCellColor(emptyCellColor),
	m_blockCanMove(false)
{
	for (size_t i = 0; i < HEIGHT; i++)
	{
		std::vector<Color> line;
		for (size_t j = 0; j < WIDTH; j++)
		{
			line.emplace_back(m_emptyCellColor);
		}
		m_grid.emplace_back(line);
	}
}

void Grid::MoveDown()
{
	while (m_blockCanMove)
		Move(Position::Down);
}

uint16_t Grid::ClearLastLines()
{
	uint16_t linesCleared = 0;
	while (LastLineFull())
	{
		linesCleared++;
		ClearLastLine();
	}
	return linesCleared;
}

void Grid::Rotate()
{
	if (!m_blockCanMove)
		return;

	RemoveCurrentBlock();
	m_currentBlock->Rotate();
	if (TrySpawnCurrentBlock(m_currentBlockOffset) == Succes)
		SpawnCurrentBlock();
	else
		m_currentBlock->UndoRotate();
}

void Grid::Move(const Position& pos)
{
	Position newOffset = m_currentBlockOffset + pos;
	RemoveCurrentBlock();
	EResult result = TrySpawnCurrentBlock(newOffset);
	if (result == Succes)
	{
		m_currentBlockOffset = newOffset;
		SpawnCurrentBlock();
		return;
	}

	if (pos == Position::Down)
		m_blockCanMove = false;
	
	SpawnCurrentBlock();
}

bool Grid::BlockCanMove() const
{
	return m_blockCanMove;
}

std::vector<std::vector<Color>> TetrisAPI::Grid::GetGrid() const
{
	return m_grid;
}

void Grid::SpawnBlock(const Block& block)
{
	m_currentBlock = block;
	m_currentBlockOffset = Position::Origin;
	m_blockCanMove = true;

	SpawnCurrentBlock();
}

bool Grid::LastLineFull() const
{
	for (size_t i = 0; i < WIDTH; i++)
	{
		if (IsPositionEmpty( Position(HEIGHT - 1, i) ))
			return false;
	}
	return true;
}

void Grid::ClearLastLine()
{
	for (size_t i = HEIGHT - 1; i > 0; i--)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			m_grid[i][j] = m_grid[i - 1][j];
		}
	}
	for (size_t j = 0; j < WIDTH; j++)
	{
		m_grid[0][j] = m_emptyCellColor;
	}
}

EResult Grid::TrySpawnCurrentBlock(const Position& offset) const
{
	for (const auto& pos : m_currentBlock->GetCurrentRotation())
	{
		Position position = pos + offset;
		EResult result = TrySpawnAt(position);
		if (result != Succes)
			return result;
	}
	return Succes;
}

EResult Grid::TrySpawnAt(const Position& pos) const
{
	if (IsPositionInGrid(pos))
	{
		if (IsPositionEmpty(pos))
			return Succes;
		return Collision;
	}
	return OutOfBounds;
}

void Grid::SetCurrentBlockCells(const Color& color)
{
	for (const auto& pos : m_currentBlock->GetCurrentRotation())
	{
		(*this)[pos + m_currentBlockOffset] = color;
	}
}

void Grid::SpawnCurrentBlock()
{
	SetCurrentBlockCells(m_currentBlock->GetColor());
}

void Grid::RemoveCurrentBlock()
{
	SetCurrentBlockCells(m_emptyCellColor);
}

bool Grid::IsPositionEmpty(const Position& pos) const
{
	return (*this)[pos] == m_emptyCellColor;
}

bool Grid::IsPositionInGrid(const Position& pos) const
{
	return  pos.GetX() >= 0 && pos.GetX() < HEIGHT &&
		pos.GetY() >= 0 && pos.GetY() < WIDTH;
}

Color& Grid::operator[](const Position& pos)
{
	return m_grid[pos.GetY()][pos.GetX()];
}

const Color& Grid::operator[](const Position& pos) const
{
	return m_grid[pos.GetY()][pos.GetX()];
}
