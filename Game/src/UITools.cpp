#include "skelpch.h"
#include "UITools.h"

#include "Core/Engine.h"
#include "UI/ViewportPanel.h"

ImVec2 UITools::CalculateGameWindowSize()
{
	ImVec2 size = ImGui::GetContentRegionAvail();
	size.y += ImGui::GetCursorPosY();
	const ViewportPanel& viewport = Engine::GetInstance().GetViewport();
	const float2 offset = ToFloat2(viewport.GetOffset());
	size.x -= offset.x;
	size.y -= offset.y;
	return size;
}

float UITools::CalculateUIElementResizeFactor()
{
	const ViewportPanel& viewport = Engine::GetInstance().GetViewport();
	const float2 totalSize = ToFloat2(viewport.GetTotalViewportSize());
	const float2 usedSize = ToFloat2(viewport.GetUsedViewportSize());
	const float2 resizeRatio = {usedSize.x / totalSize.x, usedSize.y / totalSize.y};
	const float resizeFactor = std::min(resizeRatio.x, resizeRatio.y);
	return resizeFactor;
}
