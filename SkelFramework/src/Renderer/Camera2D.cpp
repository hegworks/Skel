#include "skelpch.h"
#include "Renderer/Camera2D.h"

namespace skel
{
	Camera2D::Camera2D(float left, float right, float bottom, float top)
		: m_left(left), m_right(right), m_bottom(bottom), m_top(top)
	{
	}

	void Camera2D::SetViewport(float left, float right, float bottom, float top)
	{
		m_left = left;
		m_right = right;
		m_bottom = bottom;
		m_top = top;
	}

	void Camera2D::SetZoom(float zoom)
	{
		m_zoom = glm::clamp(zoom, 0.1f, 10.0f);
	}

	void Camera2D::Zoom(float delta)
	{
		SetZoom(m_zoom + delta);
	}

	void Camera2D::Pan(const glm::vec2& delta)
	{
		m_position += delta / m_zoom;
	}

	glm::mat4 Camera2D::GetViewMatrix() const
	{
		return glm::translate(glm::mat4(1.0f), glm::vec3(-m_position, 0.0f));
	}

	glm::mat4 Camera2D::GetProjectionMatrix() const
	{
		float width = (m_right - m_left) / m_zoom;
		float height = (m_top - m_bottom) / m_zoom;
		float cx = (m_right + m_left) / 2.0f;
		float cy = (m_top + m_bottom) / 2.0f;
		return glm::ortho(cx - width / 2.0f, cx + width / 2.0f,
		                  cy + height / 2.0f, cy - height / 2.0f, -1.0f, 1.0f);
	}

	glm::mat4 Camera2D::GetViewProjectionMatrix() const
	{
		return GetProjectionMatrix() * GetViewMatrix();
	}
}
