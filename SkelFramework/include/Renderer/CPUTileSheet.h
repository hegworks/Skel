#pragma once
#include <string>

#include "Math/SkelMath.h"

namespace skel
{
	class Surface;

	class CPUTileSheet
	{
	public:
		CPUTileSheet() = default;
		CPUTileSheet(const std::string& file, skel::int2 cellSize);
		~CPUTileSheet();

		CPUTileSheet(const CPUTileSheet& other);
		CPUTileSheet& operator=(const CPUTileSheet& rhs);

		void DrawTile(skel::Surface& target, skel::int2 targetPosition, int cellPosition) const;
		void DrawTile(skel::Surface& target, skel::int2 targetPosition, skel::int2 cellPosition) const;

		const skel::int2& GetCellSize() const { return cellSize; }

		const skel::Surface* GetSurface() const { return surface; }

		void SetTransparency(const bool enable) { useTransparency = enable; }
		bool GetTransparency() const { return useTransparency; }

		skel::uint GetPixel(int tileIndex, skel::int2 position) const;

		skel::int2 GetTileSize() const { return cellSize; }

	private:
		skel::Surface* surface{nullptr};

		bool useTransparency{true};

		skel::uint* cellPositionStart{nullptr};

		skel::int2 cellSize{0};
		skel::int2 cellGrid{0};
	};
}
