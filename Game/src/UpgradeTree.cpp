#include "skelpch.h"
#include "UpgradeTree.h"

#include "UITest.h"

EngineInitValues UpgradeTree::GetStartupSettings()
{
	return
	{
		.windowTitle = "Upgrade Tree",
		.startupWindowWidth = 1600,
		.startupWindowHeight = 900,
		.startupWindowPosX = 50,
		.startupWindowPosY = 75,
		.startFullscreen = true,

		.rendererWidth = 800,
		.rendererHeight = 450,

		.vsyncEnabled = false,

		.showStatsPanelOnStartup = false,
		.detailedConsoleLogs = false,

		.consoleToggleKey = GLFW_KEY_GRAVE_ACCENT, // set to GLFW_KEY_UNKNOWN to disable
		.consoleDetailToggleKey = GLFW_KEY_F1, // set to GLFW_KEY_UNKNOWN to disable
		.fullscreenToggleKey = GLFW_KEY_F11, // set to GLFW_KEY_UNKNOWN to disable
		.closeAppKey = GLFW_KEY_ESCAPE, // set to GLFW_KEY_UNKNOWN to disable

	};
}

void UpgradeTree::Initialize()
{
	// Engine::GetInstance().GetConsole().SetEnabled(false);

	const Renderer& renderer = Engine::GetInstance().GetRenderer();
	m_screen = std::make_unique<Surface>(renderer.GetWidth(), renderer.GetHeight(), true);
	m_bgSurface = std::make_unique<Surface>(renderer.GetWidth(), renderer.GetHeight(), true);
	m_camera2D = std::make_unique<Camera2D>(0, renderer.GetWidth(), 0, renderer.GetHeight());
	m_staticCamera2D = std::make_unique<Camera2D>(0, renderer.GetWidth(), 0, renderer.GetHeight());

	const std::shared_ptr<UIPanel> uiTest = std::make_shared<UITest>();
	Engine::GetInstance().GetUIManager().RegisterPanel(uiTest);
}

void UpgradeTree::Update(const float deltaTime)
{
	CameraControls();
}

void UpgradeTree::Render(Renderer& renderer)
{
	m_bgSurface->Clear(0);
	m_screen->Clear(0xff555555);

	renderer.BlitSurface(*m_bgSurface, 0, 0, *m_staticCamera2D);
	renderer.BlitSurface(*m_screen, 0, 0, *m_camera2D);
}

float2 UpgradeTree::WindowCoordToScreenSurface(const float2& windowCoord) const
{
	const float2 camPos = ToFloat2(m_camera2D->GetPosition());
	const float2 screenHalfSizeF = ToFloat2(m_screen->GetSize() / 2.0f);
	const float2 dstF =
		(windowCoord - screenHalfSizeF) / m_camera2D->GetZoom() +
		screenHalfSizeF + camPos;
	return dstF;
}

void UpgradeTree::CameraControls()
{
	const InputManager& input = Engine::GetInstance().GetInput();
	if(input.GetScrollDelta() > 0) m_camera2D->Zoom(+0.1f);
	if(input.GetScrollDelta() < 0) m_camera2D->Zoom(-0.1f);
	if(input.IsKeyDown(GLFW_KEY_RIGHT)) m_camera2D->Pan({-1, 0});
	if(input.IsKeyDown(GLFW_KEY_LEFT)) m_camera2D->Pan({1, 0});
	if(input.IsKeyDown(GLFW_KEY_UP)) m_camera2D->Pan({0, 1});
	if(input.IsKeyDown(GLFW_KEY_DOWN)) m_camera2D->Pan({0, -1});
}
