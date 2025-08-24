#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace skel
{
	class Camera2D
	{
	public:
		Camera2D(float left, float right, float bottom, float top);

		void SetViewport(float left, float right, float bottom, float top);
		void SetZoom(float zoom);
		void Zoom(float delta);
		void Pan(const glm::vec2& delta);

		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix() const;
		glm::mat4 GetViewProjectionMatrix() const;

		glm::vec2 GetPosition() const { return m_position; }
		float GetZoom() const { return m_zoom; }

	private:
		// settings
		static constexpr float m_minZoomLevel = 0.1f;
		static constexpr float m_maxZoomLevel = 10.0f;

		// variables
		glm::vec2 m_position = glm::vec2(0.0f);
		float m_zoom = 1.0f;

		float m_left, m_right, m_bottom, m_top;
	};
}
