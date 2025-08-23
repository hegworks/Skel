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

	// transform mousePos in window space to screenSurface space based on camera
	float2 WindowCoordToScreenSurface(const float2& windowCoord) const;

private:
	std::unique_ptr<Camera2D> m_camera2D{nullptr};
	std::unique_ptr<Camera2D> m_staticCamera2D{nullptr};
	std::unique_ptr<Surface> m_screen{nullptr};
	std::unique_ptr<Surface> m_bgSurface{nullptr};

	void CameraControls();
};
