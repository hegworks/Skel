#include "skelpch.h"
#include "UITest.h"

#include "imgui.h"
#include "Core/Engine.h"

// UITest::UITest(): m_inputManager(skel::Engine::GetInstance().GetInput())
// {
// }

void UITest::Render()
{
	if(ImGui::Button("BTN"))
	{
		SKEL_INFO("Button Pressed!");
	}

	ImDrawList* draw_list = ImGui::GetForegroundDrawList();
	float2 mousePos = ToFloat2(Engine::GetInstance().GetInput().GetMousePosition());
	const int2 viewportSize = {Engine::GetInstance().GetRenderer().GetWidth(), Engine::GetInstance().GetRenderer().GetHeight()};

	float2 viewportHalfSize = ToFloat2(viewportSize) * 0.5f;
	// float2 viewportCenter = ToFloat2(Engine::GetInstance().GetViewport().PanelToRenderTargetCoords(viewportHalfSize));
	draw_list->AddLine({viewportHalfSize.x, viewportHalfSize.y}, {mousePos.x, mousePos.y}, ImColor(1.0f, 0.0f, 0.0f));
}
