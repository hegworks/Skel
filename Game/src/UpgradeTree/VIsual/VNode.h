#pragma once
#include "Renderer/Surface.h"

class VNode
{
public:
	VNode(int idx, const int2& pixelPos, Surface* surface, Surface* surfaceHovered);
	VNode(int idx, const int2& pixelPos);
	VNode() = delete;

	int m_idx{0}; // in grid
	int2 m_pixelPos{0}; // in grid
	bool m_isHovered{false};

	Surface* m_surface{nullptr};
	Surface* m_surfaceHovered{nullptr};
};
