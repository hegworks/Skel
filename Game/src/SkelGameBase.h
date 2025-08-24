#pragma once
#include "Core/GameBase.h"
#include "Engine/AssetManager.h"
#include "Renderer/CPUTileSheet.h"
#include "Renderer/Surface.h"
#include "Renderer/Camera2D.h"
#include "UpgradeTree/UpgradeTree.h"

class SkelGameBase : public GameBase
{
public:
	// transform mousePos in window space to screenSurface space based on camera
	float2 WindowCoordToScreenSurface(const float2& windowCoord) const;

private:
	EngineInitValues GetStartupSettings() override;

	void Initialize() override;
	void Update(float deltaTime) override;
	void Render(Renderer& renderer) override;

	std::unique_ptr<Camera2D> m_camera2D{nullptr};
	std::unique_ptr<Camera2D> m_staticCamera2D{nullptr};
	std::unique_ptr<Surface> m_screen{nullptr};
	std::unique_ptr<Surface> m_bgSurface{nullptr};
	UpgradeTree* m_upgradeTree{nullptr};

	void CameraControls() const;
};
