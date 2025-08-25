#pragma once
#include "ScaledSurface.h"
#include "Renderer/Surface.h"

namespace skel
{
	class TextRenderer;
}

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
	float2 m_noneTileMousePosDecimal{0};
	int m_hoveredIdx{-1};

	UpgradeTree* m_upgradeTree{nullptr};
	Surface* m_screen{nullptr};
	Surface* m_bgSurface{nullptr};
	TextRenderer* m_textRenderer{nullptr};

	ScaledSurface* m_gridSurface{nullptr};
	Surface* m_nodeSurface{nullptr};
	Surface* m_nodeHoveredSurface{nullptr};

	std::list<VNode*> m_nodeList;
};
