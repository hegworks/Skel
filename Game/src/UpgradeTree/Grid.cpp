#include "skelpch.h"
#include "Grid.h"

#include "SkelGameBase.h"
#include "UpgradeTree.h"

Grid::Grid()
{
	m_upgradeTree = UpgradeTree::GetInstance();
	m_screen = m_upgradeTree->GetScreen();
	m_outerSurface = m_upgradeTree->GetAssetManager().AutoGetSurface("NodeOuter", false, "assets/Node_128.png");

	m_totalLength.x = (m_tileLength.x + m_spacing.x) * m_count.x - m_spacing.x + m_gridMargin.x * 2.0f;
	m_totalLength.y = (m_tileLength.y + m_spacing.y) * m_count.y - m_spacing.y + m_gridMargin.y * 2.0f;

	m_gridSurface = new Surface(m_totalLength.x, m_totalLength.y, false);
	m_gridSurface->Clear(0xff00ff00);

	m_gridPos = ToFloat2((m_screen->GetSize() / 2) - (m_gridSurface->GetSize() / 2));

	for(int row = 0; row < m_count.y; ++row)
	{
		for(int col = 0; col < m_count.x; ++col)
		{
			m_outerSurface->CopyTo((m_tileLength.x + m_spacing.x) * col + m_gridMargin.x,
			                       (m_tileLength.y + m_spacing.y) * row + m_gridMargin.y, *m_gridSurface);
		}
	}
}

void Grid::Draw()
{
	// float2 posF = m_upgradeTree->GetInstance()->GetSkellGameBase()->WindowCoordToScreenSurface(m_gridPos);
	m_gridSurface->CopyTo(ToInt2(m_gridPos), *m_screen);
}

void Grid::Update(float deltaTime)
{
	// return;
	if(Engine::GetInstance().GetInput().IsKeyDown(GLFW_KEY_D)) m_gridPos.x += deltaTime * 500.0f;
	if(Engine::GetInstance().GetInput().IsKeyDown(GLFW_KEY_A)) m_gridPos.x -= deltaTime * 500.0f;
	if(Engine::GetInstance().GetInput().IsKeyDown(GLFW_KEY_W)) m_gridPos.y -= deltaTime * 500.0f;
	if(Engine::GetInstance().GetInput().IsKeyDown(GLFW_KEY_S)) m_gridPos.y += deltaTime * 500.0f;
}
