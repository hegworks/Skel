#include "skelpch.h"
#include "Grid.h"

#include "SkelGameBase.h"
#include "UpgradeTree.h"
#include "VIsual/VNode.h"

Grid::Grid()
{
	m_upgradeTree = UpgradeTree::GetInstance();
	m_screen = m_upgradeTree->GetScreen();
	m_bgSurface = m_upgradeTree->GetBgSurface();
	m_nodeSurface = m_upgradeTree->GetAssetManager().AutoGetSurface("Node", false, "assets/node_512.png");
	m_nodeHoveredSurface = m_upgradeTree->GetAssetManager().AutoGetSurface("NodeHovered", false, "assets/node_Hovered.png");

	m_totalLength.x = (m_tileLength.x + m_spacing.x) * m_count.x - m_spacing.x + m_gridMargin.x * 2.0f;
	m_totalLength.y = (m_tileLength.y + m_spacing.y) * m_count.y - m_spacing.y + m_gridMargin.y * 2.0f;

	m_gridSurface = new Surface(m_totalLength.x, m_totalLength.y, false);
	m_gridSurface->Clear(0xff00ff00);

	m_gridOrigin = {0, 0};

	m_nodeList.clear();

	int idx = 0;
	for(int row = 0; row < m_count.y; ++row)
	{
		for(int col = 0; col < m_count.x; ++col)
		{
			const int2 pos = int2((m_tileLength.x + m_spacing.x) * col + m_gridMargin.x,
			                      (m_tileLength.y + m_spacing.y) * row + m_gridMargin.y);
			m_nodeSurface->CopyTo(pos.x, pos.y, *m_gridSurface);
			VNode* node = new VNode(idx, pos);
			m_nodeList.push_back(node);
		}
	}
}

void Grid::Draw()
{
	// m_gridSurface->Clear(0xffcccccc);

	const InputManager& input = Engine::GetInstance().GetInput();
	const int2 mousePosI = input.GetMousePosition();
	// const float2 mousePosF = ToFloat2(mousePosI);
	// const int2 mousePosOnGridI = ToInt2(ScreenToGrid(mousePosF));
	// m_gridSurface->Rectangle(mousePosOnGridI.x - 8, mousePosOnGridI.y - 8, mousePosOnGridI.x + 8, mousePosOnGridI.y + 8, 0xff00ff00);

	// const int2 gridTopLeftOnGrid = {0, 0};
	// m_gridSurface->Rectangle(gridTopLeftOnGrid.x - 8, gridTopLeftOnGrid.y - 8, gridTopLeftOnGrid.x + 8, gridTopLeftOnGrid.y + 8, 0xff00ff00);

	// const int2 gridBottomRightOnGrid = m_gridSurface->GetSize();
	// m_gridSurface->Rectangle(gridBottomRightOnGrid.x - 8, gridBottomRightOnGrid.y - 8, gridBottomRightOnGrid.x + 8, gridBottomRightOnGrid.y + 8, 0xff00ff00);

	const int2 gridDrawPosOnScreen = GridDrawPosOnScreen();
	m_gridSurface->CopyToScaledFast(gridDrawPosOnScreen.x, gridDrawPosOnScreen.y, *m_screen, m_gridScale);

	const float2 gridCenterOnScreen = GridCenterOnScreen();
	m_screen->Rectangle(gridCenterOnScreen.x - 8, gridCenterOnScreen.y - 8, gridCenterOnScreen.x + 8, gridCenterOnScreen.y + 8, 0xffff0000);

	const int2 gridTopLeftOnScreen = ToInt2(GridToScreen(float2(0, 0)));
	m_screen->Rectangle(gridTopLeftOnScreen.x - 8, gridTopLeftOnScreen.y - 8, gridTopLeftOnScreen.x + 8, gridTopLeftOnScreen.y + 8, 0xffff0000);

	const int2 gridBottomRightOnScreen = ToInt2(GridToScreen(ToFloat2(m_gridSurface->GetSize())));
	m_screen->Rectangle(gridBottomRightOnScreen.x - 8, gridBottomRightOnScreen.y - 8, gridBottomRightOnScreen.x + 8, gridBottomRightOnScreen.y + 8, 0xffff0000);

	m_screen->Line(mousePosI.x, mousePosI.y, gridCenterOnScreen.x, gridCenterOnScreen.y, 0xffff0000);
}

float2 Grid::ScreenToGrid(const float2& coord) const
{
	const float2 screenHalfSize = ToFloat2(m_screen->GetSize()) * 0.5f;
	const float2 gridScaledHalfSize = ToFloat2(m_gridSurface->GetSize()) * m_gridScale * 0.5f;
	return (coord - screenHalfSize + gridScaledHalfSize - m_gridOrigin) / m_gridScale;
}

float2 Grid::GridToScreen(const float2& coord) const
{
	const float2 screenHalfSize = ToFloat2(m_screen->GetSize()) * 0.5f;
	const float2 gridScaledHalfSize = ToFloat2(m_gridSurface->GetSize()) * m_gridScale * 0.5f;
	return (coord * m_gridScale) + m_gridOrigin + screenHalfSize - gridScaledHalfSize;
}

int2 Grid::GridDrawPosOnScreen() const
{
	const float2 screenHalfSize = ToFloat2(m_screen->GetSize()) * 0.5f;
	const float2 gridScaledHalfSize = ToFloat2(m_gridSurface->GetSize()) * m_gridScale * 0.5f;
	return ToInt2(m_gridOrigin + screenHalfSize - gridScaledHalfSize);
}

float2 Grid::GridCenterOnScreen() const
{
	const float2 screenHalfSize = ToFloat2(m_screen->GetSize()) * 0.5f;
	return m_gridOrigin + screenHalfSize;
}

void Grid::Update(float deltaTime)
{
	const InputManager& input = Engine::GetInstance().GetInput();

	if(input.IsKeyDown(GLFW_KEY_D)) m_gridOrigin.x -= deltaTime * 2000.0f;
	if(input.IsKeyDown(GLFW_KEY_A)) m_gridOrigin.x += deltaTime * 2000.0f;
	if(input.IsKeyDown(GLFW_KEY_W)) m_gridOrigin.y += deltaTime * 2000.0f;
	if(input.IsKeyDown(GLFW_KEY_S)) m_gridOrigin.y -= deltaTime * 2000.0f;
	if(input.GetScrollDelta() > 0 || input.GetScrollDelta() < 0)
	{
		/// zoom at mouse
		{
			const float2 mousePosOnScreen = ToFloat2(input.GetMousePosition());
			const float2 mousePosOnGrid = ScreenToGrid(mousePosOnScreen);

			// apply zoom
			if(input.GetScrollDelta() > 0.0f) m_gridScale *= 1.2f;
			if(input.GetScrollDelta() < 0.0f) m_gridScale *= 0.8f;
			m_gridScale = std::clamp(m_gridScale, 0.05f, 1.8f);

			// move grid so mouse still points to same grid-local position
			m_gridOrigin += mousePosOnScreen - GridToScreen(mousePosOnGrid);
		}
	}
}
