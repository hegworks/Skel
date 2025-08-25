#include "skelpch.h"
#include "Grid.h"

#include "SkelGameBase.h"
#include "UpgradeTree.h"
#include "Renderer/TextRenderer.h"
#include "VIsual/VNode.h"

Grid::Grid()
{
	m_upgradeTree = UpgradeTree::GetInstance();
	m_textRenderer = m_upgradeTree->GetTextRenderer();
	m_screen = m_upgradeTree->GetScreen();
	m_bgSurface = m_upgradeTree->GetBgSurface();
	m_nodeSurface = m_upgradeTree->GetAssetManager().AutoGetSurface("Node", false, "assets/node_512.png");
	m_nodeHoveredSurface = m_upgradeTree->GetAssetManager().AutoGetSurface("NodeHovered", false, "assets/node_Hovered.png");

	m_totalLength.x = (m_tileLength.x + m_spacing.x) * m_count.x - m_spacing.x + m_gridMargin.x * 2.0f;
	m_totalLength.y = (m_tileLength.y + m_spacing.y) * m_count.y - m_spacing.y + m_gridMargin.y * 2.0f;

	m_gridSurface = new ScaledSurface(m_totalLength.x, m_totalLength.y, false, m_screen->GetSize());
	m_gridSurface->GetSurface()->Clear(0xff00ff00);

	m_nodeList.clear();

	Surface* numberedSurface = new Surface(m_nodeSurface->GetSize().x, m_nodeSurface->GetSize().y, false);
	int idx = 0;
	for(int row = 0; row < m_count.y; ++row)
	{
		for(int col = 0; col < m_count.x; ++col)
		{
			numberedSurface->Clear(0);
			m_nodeSurface->CopyTo(*numberedSurface, 0, 0);
			m_textRenderer->DrawOnSurface(numberedSurface, std::to_string(idx), 85, 135, 10);
			const int2 pos = int2((m_tileLength.x + m_spacing.x) * col + m_gridMargin.x,
			                      (m_tileLength.y + m_spacing.y) * row + m_gridMargin.y);
			numberedSurface->CopyTo(*m_gridSurface->GetSurface(), pos.x, pos.y);
			VNode* node = new VNode(idx, pos);
			m_nodeList.push_back(node);
			idx++;
		}
	}
	delete numberedSurface;
}

void Grid::Draw()
{
	// m_gridSurface->GetSurface()->Clear(0xffcccccc);

	const InputManager& input = Engine::GetInstance().GetInput();
	const int2 mousePosI = input.GetMousePosition();
	// const float2 mousePosF = ToFloat2(mousePosI);
	// const int2 mousePosOnGridI = ToInt2(m_gridSurface->GetScreenToSurface(mousePosF));
	// m_gridSurface->GetSurface()->Rectangle(mousePosOnGridI.x - 8, mousePosOnGridI.y - 8, mousePosOnGridI.x + 8, mousePosOnGridI.y + 8, 0xff00ff00);

	// const int2 gridTopLeftOnGrid = {0, 0};
	// m_gridSurface->Rectangle(gridTopLeftOnGrid.x - 8, gridTopLeftOnGrid.y - 8, gridTopLeftOnGrid.x + 8, gridTopLeftOnGrid.y + 8, 0xff00ff00);

	// const int2 gridBottomRightOnGrid = m_gridSurface->GetSize();
	// m_gridSurface->Rectangle(gridBottomRightOnGrid.x - 8, gridBottomRightOnGrid.y - 8, gridBottomRightOnGrid.x + 8, gridBottomRightOnGrid.y + 8, 0xff00ff00);

	const int2 gridDrawPosOnScreen = m_gridSurface->GetDrawPosOnScreen();
	m_gridSurface->GetSurface()->CopyToScaledFast(*m_screen, gridDrawPosOnScreen.x, gridDrawPosOnScreen.y, m_gridSurface->GetScale());

	const float2 gridCenterOnScreen = m_gridSurface->GetCenterOnScreen();
	m_screen->Rectangle(gridCenterOnScreen.x - 8, gridCenterOnScreen.y - 8, gridCenterOnScreen.x + 8, gridCenterOnScreen.y + 8, 0xffff0000);

	const int2 gridTopLeftOnScreen = ToInt2(m_gridSurface->GetSurfaceToScreen(float2(0, 0)));
	m_screen->Rectangle(gridTopLeftOnScreen.x - 8, gridTopLeftOnScreen.y - 8, gridTopLeftOnScreen.x + 8, gridTopLeftOnScreen.y + 8, 0xffff0000);

	const int2 gridBottomRightOnScreen = ToInt2(
		m_gridSurface->GetSurfaceToScreen(ToFloat2(m_gridSurface->GetSize())));
	m_screen->Rectangle(gridBottomRightOnScreen.x - 8, gridBottomRightOnScreen.y - 8, gridBottomRightOnScreen.x + 8, gridBottomRightOnScreen.y + 8, 0xffff0000);

	m_screen->Line(mousePosI.x, mousePosI.y, gridCenterOnScreen.x, gridCenterOnScreen.y, 0xffff0000);
}

void Grid::Update(float deltaTime)
{
	const InputManager& input = Engine::GetInstance().GetInput();

	if(input.IsKeyDown(GLFW_KEY_D)) m_gridSurface->m_origin.x -= deltaTime * 2000.0f;
	if(input.IsKeyDown(GLFW_KEY_A)) m_gridSurface->m_origin.x += deltaTime * 2000.0f;
	if(input.IsKeyDown(GLFW_KEY_W)) m_gridSurface->m_origin.y += deltaTime * 2000.0f;
	if(input.IsKeyDown(GLFW_KEY_S)) m_gridSurface->m_origin.y -= deltaTime * 2000.0f;

	float zoomFactor;
	if(input.GetScrollDelta() > 0.0f) zoomFactor = 1.2f;
	else if(input.GetScrollDelta() < 0.0f) zoomFactor = 0.8f;
	else return;
	const float2 mousePosOnScreen = ToFloat2(input.GetMousePosition());
	m_gridSurface->ZoomAtScreenCoord(mousePosOnScreen, zoomFactor, 0.05f, 1.8f);
}
