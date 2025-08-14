#include "skelpch.h"
#include "UITest.h"

#include "imgui.h"
#include "Core/Engine.h"

// UITest::UITest(): m_inputManager(skel::Engine::GetInstance().GetInput())
// {
// }

void UITest::Render()
{
	ImGui::Begin("Viewport"); // Name must match the docked panel name if using docking

	ImVec2 panelSize = ImGui::GetContentRegionAvail();
	panelSize.y += ImGui::GetCursorPosY(); // Add the height already "used" above
	const ViewportPanel& viewport = Engine::GetInstance().GetViewport();
	float2 offset = ToFloat2(viewport.GetOffset());
	panelSize.x -= offset.x;
	panelSize.y -= offset.y;

	float2 totalSize = ToFloat2(viewport.GetTotalViewportSize());
	float2 usedSize = ToFloat2(viewport.GetUsedViewportSize());
	float2 resizeRatio = {usedSize.x / totalSize.x, usedSize.y / totalSize.y};
	float resizeValue = std::min(resizeRatio.x, resizeRatio.y);

	ImVec2 buttonSize = {200.0f * resizeValue, 100.0f * resizeValue};

	// Calculate centered position
	ImVec2 pos;
	// pos.x = (panelSize.x - buttonSize.x) * 0.5f;
	// pos.y = (panelSize.y - buttonSize.y) * 0.5f;
	pos.x = panelSize.x - buttonSize.x;
	pos.y = panelSize.y - buttonSize.y;

	ImGui::SetCursorPos(pos);

	if(ImGui::Button("BTN", buttonSize))
	{
		SKEL_INFO("Button Pressed!");
	}

	ImGui::End();

	///////////////////////////

	// static bool use_work_area = false;
	// static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

	// const ImGuiViewport* viewport = ImGui::GetWindowViewport();
	// ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
	// ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
	// ImGui::SetNextWindowPos(ImVec2(0, 0));
	// ImGui::SetNextWindowSize(ImVec2(0, 0));
	// ImGui::SetNextWindowBgAlpha(0);
	// ImVec2 buttonSize = {200, 100};

	// ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.3f));
	// if(ImGui::Begin("Main Menu", nullptr, flags))
	// {
	// ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 2 - buttonSize.x / 2, ImGui::GetWindowHeight() / 2 - buttonSize.y / 2));
	// ImGui::SetCursorPos(ImVec2(0,0));
	// if(ImGui::Button("BTN", buttonSize))
	// {
	// SKEL_INFO("Button Pressed!");
	// }
	// ImGui::End();
	// }

	// ImDrawList* draw_list = ImGui::GetForegroundDrawList();
	// float2 mousePos = ToFloat2(Engine::GetInstance().GetInput().GetMousePosition());
	// const int2 viewportSize = {Engine::GetInstance().GetRenderer().GetWidth(), Engine::GetInstance().GetRenderer().GetHeight()};

	// float2 viewportHalfSize = ToFloat2(viewportSize) * 0.5f;
	// float2 viewportCenter = ToFloat2(Engine::GetInstance().GetViewport().PanelToRenderTargetCoords(viewportHalfSize));
	// draw_list->AddLine({viewportHalfSize.x, viewportHalfSize.y}, {mousePos.x, mousePos.y}, ImColor(1.0f, 0.0f, 0.0f));
}
