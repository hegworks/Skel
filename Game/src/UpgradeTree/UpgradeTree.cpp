#include "skelpch.h"
#include "UpgradeTree.h"

void UpgradeTree::Initialize(Surface* screen, Surface* bgSurface, SkelGameBase* skellGameBase)
{
	m_screen = screen;
	m_bgSurface = bgSurface;
	m_skellGameBase = skellGameBase;

	m_assetManager = std::make_unique<AssetManager>();
	m_textRenderer = std::make_unique<TextRenderer>("assets/Font.png", 41, 1, 4, FontTextRendererCharToIndex);
	m_grid = std::make_unique<Grid>();
}

void UpgradeTree::Draw()
{
	m_grid->Draw();
}

void UpgradeTree::Update(float deltaTime)
{
	m_grid->Update(deltaTime);
}
