#pragma once
#include <memory>

#include "UI/UIPanel.h"

class UITest : public UIPanel
{
public:
	// UITest();
	void Render() override;

	// std::shared_ptr<skel::InputManager> m_inputManager;
	// skel::InputManager& m_inputManager;
};
