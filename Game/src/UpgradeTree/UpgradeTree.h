#pragma once
#include "Grid.h"
#include "Engine/AssetManager.h"

class SkelGameBase;

class UpgradeTree
{
#pragma region Scott Meyers Thread-Safe Singleton

public:
	static UpgradeTree* GetInstance()
	{
		static UpgradeTree instance;
		return &instance;
	}

	UpgradeTree(UpgradeTree const&) = delete;
	void operator=(UpgradeTree const&) = delete;

private:
	UpgradeTree() = default;
	~UpgradeTree() = default;
#pragma endregion Scott Meyers Thread-Safe Singleton

public:
	void Initialize(Surface* screen, Surface* bgSurface, SkelGameBase* skellGameBase);
	void Draw();
	void Update(float deltaTime);

	AssetManager& GetAssetManager() const { return *m_assetManager; }
	Surface* GetScreen() const { return m_screen; }
	Surface* GetBgSurface() const { return m_bgSurface; }
	SkelGameBase* GetSkellGameBase() const { return m_skellGameBase; }

private:
	std::unique_ptr<AssetManager> m_assetManager{nullptr};
	std::unique_ptr<Grid> m_grid{nullptr};

	SkelGameBase* m_skellGameBase{nullptr};
	Surface* m_screen{nullptr};
	Surface* m_bgSurface{nullptr};
};
