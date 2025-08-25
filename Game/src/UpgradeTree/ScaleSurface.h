#pragma once
#include "Renderer/Surface.h"

class ScaleSurface
{
public:
	ScaleSurface(const std::string& filePath, bool needGPUTexture, int2 screenSize);
	ScaleSurface(int width, int height, bool needGPUTexture, int2 screenSize);

	float2 m_origin{0.0f};

	Surface* GetSurface() const { return m_surface; }
	float GetScale() const { return m_scale; }
	int2 GetSize() const { return m_surface->GetSize(); }

	float2 GetScaledHalfSize() const;
	float2 GetScreenToSurface(const float2& coord) const;
	float2 GetSurfaceToScreen(const float2& coord) const;
	int2 GetDrawPosOnScreen() const;
	float2 GetCenterOnScreen() const;
	void ZoomAtScreenCoord(const float2& screenCoord, float multiplicationFactor, float minScale = 0.01f, float maxScale = 1000.0f);
	void ZoomAtCenter(float multiplicationFactor, float minScale = 0.01f, float maxScale = 1000.0f);

private:
	Surface* m_surface;
	float m_scale{1.0f};
	float2 m_screenHalfSize{0.0f};
	float2 m_surfaceHalfSize{0.0f};
};
