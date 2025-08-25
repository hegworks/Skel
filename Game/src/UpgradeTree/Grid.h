#pragma once
#include "Renderer/Surface.h"

class VNode;
class UpgradeTree;

class Grid
{
public:
	Grid();
	void Draw();
	void Update(float deltaTime);

private:
	// settings
	static constexpr int2 m_count{33, 33};
	static constexpr int2 m_spacing{200, 200};
	static constexpr int2 m_tileLength{512, 512};
	static constexpr int2 m_gridMargin{128, 128};

	// variables
	int2 m_totalLength{0};

	UpgradeTree* m_upgradeTree{nullptr};
	Surface* m_screen{nullptr};
	Surface* m_bgSurface{nullptr};

	Surface* m_gridSurface{nullptr};
	Surface* m_nodeSurface{nullptr};
	Surface* m_nodeHoveredSurface{nullptr};

	float2 m_gridOrigin{0, 0};
	float m_gridScale{1};

	std::list<VNode*> m_nodeList;

	float2 ScreenToGrid(const float2& coord) const;
	float2 GridToScreen(const float2& coord) const;
	int2 GridDrawPosOnScreen() const;
	float2 GridCenterOnScreen() const;
};
