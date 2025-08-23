#include "skelpch.h"
#include "UITest.h"

#include "imgui.h"
#include "UITools.h"
#include "Core/Engine.h"

void UITest::Render()
{
	ImGui::Begin("Viewport");
	const ImVec2 panelSize = UITools::CalculateGameWindowSize();
	const float resizeValue = UITools::CalculateUIElementResizeFactor();

	const ImVec2 buttonSize = {200.0f * resizeValue, 100.0f * resizeValue};
	ImVec2 buttonPos;
	buttonPos.x = panelSize.x - buttonSize.x;
	buttonPos.y = panelSize.y - buttonSize.y;

	ImGui::SetCursorPos(buttonPos);
	if(ImGui::Button("BTN", buttonSize))
	{
		SKEL_INFO("Button Pressed!");
	}

	ImGui::End();
}
