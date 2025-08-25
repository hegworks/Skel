#pragma once
#include "Grid.h"
#include "Engine/AssetManager.h"
#include "Renderer/TextRenderer.h"

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
	TextRenderer* GetTextRenderer() const { return m_textRenderer.get(); }

private:
	std::unique_ptr<AssetManager> m_assetManager{nullptr};
	std::unique_ptr<Grid> m_grid{nullptr};
	std::unique_ptr<TextRenderer> m_textRenderer{nullptr};

	SkelGameBase* m_skellGameBase{nullptr};
	Surface* m_screen{nullptr};
	Surface* m_bgSurface{nullptr};

	static constexpr int FontTextRendererCharToIndex(const char c)
	{
		if(c >= 'a' && c <= 'z') return c - 'a'; // 0-25
		if(c >= 'A' && c <= 'Z') return c - 'A'; // 0-25
		if(c >= '0' && c <= '9') return c - '0' + 26; // 26-35
		if(c == '*') return 35 + 1;
		if(c == '>') return 35 + 2;
		if(c == ',') return 35 + 3;
		if(c == '.') return 35 + 4;
		if(c == ' ') return 35 + 5;
		throw std::exception("character not supported");
	}
};
