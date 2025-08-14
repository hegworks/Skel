#pragma once
#include "Core/GameBase.h"
#include "Renderer/CPUTileSheet.h"
#include "Renderer/Surface.h"
#include "Renderer/Camera2D.h"

class ExampleGame : public GameBase
{
public:
	ExampleGame() = default;

	EngineInitValues GetStartupSettings() override;

	void Initialize() override;
	void Update(float deltaTime) override;
	void Render(Renderer& renderer) override;

private:
	std::unique_ptr<Camera2D> m_camera2D{nullptr};
	std::unique_ptr<Camera2D> m_bgCamera2D{nullptr};
	std::unique_ptr<Surface> m_screen{nullptr};
	std::unique_ptr<Surface> m_bgSurface{nullptr};
	std::unique_ptr<Surface> m_testImage{nullptr};
	std::unique_ptr<Surface> m_hegSurface{nullptr};
	std::unique_ptr<Surface> m_btnSurface{nullptr};
	std::unique_ptr<CPUTileSheet> m_btnTile{nullptr};
	std::unique_ptr<CPUTileSheet> m_tileSheet{nullptr};

	float m_totalTime = 0;

	int m_circleRadius = 0;

	float2 ballPos{100, 100};
	float2 ballVel{60, 45};
	int2 ballSize;
};
