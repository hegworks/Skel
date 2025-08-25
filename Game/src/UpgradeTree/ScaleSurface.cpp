#include "skelpch.h"
#include "ScaleSurface.h"

ScaleSurface::ScaleSurface(const std::string& filePath, const bool needGPUTexture, const int2 screenSize)
{
	m_surface = new Surface(filePath, needGPUTexture);
	m_screenHalfSize = ToFloat2(screenSize) * 0.5f;
	m_surfaceHalfSize = ToFloat2(m_surface->GetSize()) * 0.5f;
}

ScaleSurface::ScaleSurface(const int width, const int height, const bool needGPUTexture, const int2 screenSize)
{
	m_surface = new Surface(width, height, needGPUTexture);
	m_screenHalfSize = ToFloat2(screenSize) * 0.5f;
	m_surfaceHalfSize = ToFloat2(m_surface->GetSize()) * 0.5f;
}

float2 ScaleSurface::GetScaledHalfSize() const
{
	return m_surfaceHalfSize * m_scale;
}

float2 ScaleSurface::GetScreenToSurface(const float2& coord) const
{
	return (coord - m_screenHalfSize + GetScaledHalfSize() - m_origin) / m_scale;
}

float2 ScaleSurface::GetSurfaceToScreen(const float2& coord) const
{
	return (coord * m_scale) + m_origin + m_screenHalfSize - GetScaledHalfSize();
}

int2 ScaleSurface::GetDrawPosOnScreen() const
{
	return ToInt2(m_origin + m_screenHalfSize - GetScaledHalfSize());
}

float2 ScaleSurface::GetCenterOnScreen() const
{
	return m_origin + m_screenHalfSize;
}

void ScaleSurface::ZoomAtScreenCoord(const float2& screenCoord, const float multiplicationFactor, const float minScale, const float maxScale)
{
	const float2 p = GetScreenToSurface(screenCoord);
	m_scale *= multiplicationFactor;
	m_scale = std::clamp(m_scale, minScale, maxScale);
	m_origin += screenCoord - GetSurfaceToScreen(p);
}

void ScaleSurface::ZoomAtCenter(const float multiplicationFactor, const float minScale, const float maxScale)
{
	m_scale *= multiplicationFactor;
	m_scale = std::clamp(m_scale, minScale, maxScale);
}
