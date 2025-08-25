#include "skelpch.h"
#include "VNode.h"

VNode::VNode(const int idx, const int2& pixelPos, Surface* surface, Surface* surfaceHovered)
{
	m_idx = idx;
	m_pixelPos = pixelPos;
	m_surface = surface;
	m_surfaceHovered = surfaceHovered;
}

VNode::VNode(int idx, const int2& pixelPos)
{
	m_idx = idx;
	m_pixelPos = pixelPos;
}
