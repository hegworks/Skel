#include "skelpch.h"
#include "UpgradeTree.h"

void UpgradeTree::Initialize(Surface* screen, SkelGameBase* skellGameBase)
{
	m_screen = screen;
	m_skellGameBase = skellGameBase;

	m_assetManager = std::make_unique<AssetManager>();
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
