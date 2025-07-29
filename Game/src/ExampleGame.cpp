#include "skelpch.h"
#include "ExampleGame.h"

#include "UITest.h"
#include "Math/ColorConverter.h"
#include "UI/ConsolePanel.h"

EngineInitValues ExampleGame::GetStartupSettings()
{
	return
	{
		.windowTitle = "Example Game",
		.startupWindowWidth = 1600,
		.startupWindowHeight = 900,

		.rendererWidth = 800,
		.rendererHeight = 450,

		.vsyncEnabled = false,

		.showStatsPanelOnStartup = false,

	};
}

void ExampleGame::Initialize()
{
	const Renderer& renderer = Engine::GetInstance().GetRenderer();

	// Engine::GetInstance().GetConsole().SetEnabled(false);

	m_screen = std::make_unique<Surface>(renderer.GetWidth(), renderer.GetHeight(), true);
	m_camera2D = std::make_unique<Camera2D>(0, renderer.GetWidth(), 0, renderer.GetHeight());

	m_testImage = std::make_unique<Surface>("assets/testAsset.png", false);
	ballSize = {m_testImage->GetWidth(), m_testImage->GetHeight()};
	m_circleRadius = static_cast<int>(static_cast<float>(ballSize.x) * 0.5f);

	m_hegSurface = std::make_unique<Surface>("assets/heg.png", true);
	SKEL_INFO("hegSurfaceSize:" + std::to_string(m_hegSurface->GetWidth()) + "x" + std::to_string(m_hegSurface->GetHeight()));

	m_tileSheet = std::make_unique<CPUTileSheet>("assets/tileset.png", int2(32, 32));

	m_btnTile = std::make_unique<CPUTileSheet>("assets/btn.png", int2(138, 141));
	m_btnSurface = std::make_unique<Surface>("assets/btn.png", true);

	// std::shared_ptr<UIPanel> uiTest = std::make_shared<UITest>();
	// Engine::GetInstance().GetUIManager().RegisterPanel(uiTest);
}

void ExampleGame::Update(const float deltaTime)
{
	const InputManager& input = Engine::GetInstance().GetInput();

	if(input.GetScrollDelta() > 0)
	{
		m_circleRadius++;
		m_camera2D->Zoom(+0.1f);
	}
	else if(input.GetScrollDelta() < 0)
	{
		m_circleRadius--;
		m_camera2D->Zoom(-0.1f);
	}

	m_circleRadius = std::max(0, m_circleRadius);

	if(input.IsKeyDown(GLFW_KEY_RIGHT)) ballVel.x += 200.f * deltaTime, m_camera2D->Pan({-1, 0});
	if(input.IsKeyDown(GLFW_KEY_LEFT)) ballVel.x -= 200.f * deltaTime, m_camera2D->Pan({1, 0});
	if(input.IsKeyDown(GLFW_KEY_UP)) ballVel.y -= 200.f * deltaTime, m_camera2D->Pan({0, 1});
	if(input.IsKeyDown(GLFW_KEY_DOWN)) ballVel.y += 200.f * deltaTime, m_camera2D->Pan({0, -1});

	ballPos += ballVel * deltaTime;

	if(ballPos.x < 0 || ballPos.x + static_cast<float>(ballSize.x) > static_cast<float>(m_screen->GetWidth()))
	{
		ballVel.x = -ballVel.x;
		ballPos.x = std::clamp(ballPos.x, 0.f, static_cast<float>(m_screen->GetWidth() - ballSize.x));
	}
	if(ballPos.y < 0 || ballPos.y + static_cast<float>(ballSize.y) > static_cast<float>(m_screen->GetHeight()))
	{
		ballVel.y = -ballVel.y;
		ballPos.y = std::clamp(ballPos.y, 0.f, static_cast<float>(m_screen->GetHeight() - ballSize.y));
	}

	constexpr float friction = 0.5f;
	ballVel -= ballVel * friction * deltaTime;

	// int2 mousePos = input.GetMousePosition();
	// SKEL_INFO("MousePosition: {},{}", mousePos.x, mousePos.y);

	m_totalTime += deltaTime;
}

void ExampleGame::Render(Renderer& renderer)
{
	const InputManager& input = Engine::GetInstance().GetInput();

	const float3 bg = HSVtoRGB(fmodf(m_totalTime * 0.1f, 1.f), .7f, .7f);
	m_screen->Clear(ColorToUint32(float4(bg, 1.f)));

	m_testImage->CopyTo({static_cast<int>(ballPos.x), static_cast<int>(ballPos.y)}, *m_screen);

	m_screen->Circle(static_cast<int>(ballPos.x + ballSize.x / 2), static_cast<int>(ballPos.y + ballSize.y / 2), m_circleRadius, 0xffFFCF56, 1);
	// renderer.BlitSurface(m_hegSurface.get(), 0, 0);

	int2 btnPos = input.GetMousePosition() - (m_btnTile->GetCellSize() / 2);

	// m_btnTile->DrawTile(*m_screen, btnPos, 0);

	m_btnSurface->CopyTo(btnPos, *m_screen);

	m_screen->Line(m_screen->GetWidth() / 2, m_screen->GetHeight() / 2, input.GetMousePosition().x, input.GetMousePosition().y, 0xffff0000);
	m_tileSheet->DrawTile(*m_screen, int2(100, 100), 5);
	renderer.BlitSurface(*m_screen, 0, 0, *m_camera2D);

	// renderer.BlitSurface(*m_btn, btnPos.x, btnPos.y);
}
