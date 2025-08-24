#pragma once
#include "Renderer/Surface.h"

class UpgradeTree;

class Grid
{
public:
	Grid();
	void Draw();
	void Update(float deltaTime);

private:
	// settings
	static constexpr int2 m_count{16, 16};
	static constexpr int2 m_spacing{70, 62};
	static constexpr int2 m_tileLength{128, 128};
	static constexpr int2 m_gridMargin{64, 64};

	// variables
	int2 m_totalLength{0};

	UpgradeTree* m_upgradeTree{nullptr};
	Surface* m_screen{nullptr};

	Surface* m_gridSurface{nullptr};
	Surface* m_outerSurface{nullptr};

	float2 m_gridPos{0, 0};
};
