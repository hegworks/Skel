#include "skelpch.h"
#include "Renderer/CPUTileSheet.h"
#include "Renderer/Surface.h"

#include <cassert>

namespace skel
{
	class TileSheet;

	CPUTileSheet::CPUTileSheet(const std::string& file, const skel::int2 cellSize)
		: surface{new skel::Surface(file, false)}
		  , cellSize(cellSize)
	{
		cellGrid.x = surface->GetWidth() / cellSize.x;
		cellGrid.y = surface->GetHeight() / cellSize.y;

		cellPositionStart = new skel::uint[cellGrid.x * cellGrid.y];

		for(int y = 0; y < cellGrid.y; y++)
		{
			for(int x = 0; x < cellGrid.x; x++)
			{
				cellPositionStart[y * cellGrid.x + x] =
					x * cellSize.x + y * cellSize.y * surface->GetWidth();
			}
		}
	}

	CPUTileSheet::CPUTileSheet(const CPUTileSheet& other)
	{
		cellSize = other.cellSize;
		cellGrid = other.cellGrid;
		useTransparency = other.useTransparency;

		surface = new skel::Surface(other.surface->GetWidth(), other.surface->GetHeight(), false);
		other.surface->CopyTo(0, 0, *surface);

		cellPositionStart = new skel::uint[cellGrid.x * cellGrid.y];
		for(int i = 0; i < cellGrid.x * cellGrid.y; i++)
		{
			cellPositionStart[i] = other.cellPositionStart[i];
		}
	}

	CPUTileSheet::~CPUTileSheet()
	{
		delete surface;
		delete[] cellPositionStart;
	}

	CPUTileSheet& CPUTileSheet::operator=(const CPUTileSheet& rhs)
	{
		if(this != &rhs)
		{
			cellSize = rhs.cellSize;
			cellGrid = rhs.cellGrid;
			useTransparency = rhs.useTransparency;

			delete surface;
			delete[] cellPositionStart;

			surface = new skel::Surface(rhs.surface->GetWidth(), rhs.surface->GetHeight(), false);
			rhs.surface->CopyTo(0, 0, *surface);

			cellPositionStart = new skel::uint[cellGrid.x * cellGrid.y];
			for(int i = 0; i < cellGrid.x * cellGrid.y; i++)
			{
				cellPositionStart[i] = rhs.cellPositionStart[i];
			}
		}
		return *this;
	}

	void CPUTileSheet::DrawTile(skel::Surface& target, skel::int2 targetPosition, int cellPosition) const
	{
		if(cellPosition > cellGrid.x * cellGrid.y || cellPosition < 0)
			assert(0); // CellPosition is not valid!

		skel::uint startBufferPosition = cellPositionStart[cellPosition];

		int clipXLeftOffset = std::max(0, targetPosition.x) - targetPosition.x;
		int clipXRightOffset = std::min(targetPosition.x + static_cast<int>(cellSize.x), static_cast<int>(target.GetWidth())) - targetPosition.x - static_cast<int>(cellSize.x);

		int clipYTopOffset = std::max(0, targetPosition.y) - targetPosition.y;
		int clipYBottomOffset = std::min(targetPosition.y + static_cast<int>(cellSize.y),
		                                 static_cast<int>(target.GetHeight())) - targetPosition.y - static_cast<int>(cellSize.y);

		int drawWidth = -clipXLeftOffset + cellSize.x + clipXRightOffset;
		int drawHeight = -clipYTopOffset + cellSize.y + clipYBottomOffset;

		for(int y = 0; y < drawHeight; y++) // If we don't need transparency we could use memcpy i
		{
			for(int x = 0; x < drawWidth; x++)
			{
				int targetSurfaceOffset = (targetPosition.y + y + clipYTopOffset) * target.GetWidth() + targetPosition.x + x + clipXLeftOffset;
				int ownSurfaceOffset = (y + clipYTopOffset) * surface->GetWidth() + x + clipXLeftOffset;

				skel::uint color = surface->GetBuffer()[startBufferPosition + ownSurfaceOffset];

				if(!useTransparency || (color >> 24) != 0)
					target.GetBuffer()[targetSurfaceOffset] = color | 0xff000000;
			}
		}

		target.MarkAsDirty();
	}

	void CPUTileSheet::DrawTile(skel::Surface& target, skel::int2 targetPosition, skel::int2 cellPosition) const
	{
		DrawTile(target, targetPosition, cellPosition.y * cellGrid.x + cellPosition.x);
	}

	skel::uint CPUTileSheet::GetPixel(int tileIndex, skel::int2 position) const
	{
		if(position.x < 0 || position.x >= static_cast<int>(cellSize.x) ||
			position.y < 0 || position.y >= static_cast<int>(cellSize.y) || tileIndex < 0 || tileIndex >= cellGrid.y * cellGrid.x)
		{
			return 0;
		}

		return surface->GetBuffer()[cellPositionStart[tileIndex] + position.y * surface->GetWidth() + position.x];
	}
}
