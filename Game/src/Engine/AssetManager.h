#pragma once
#include "skelpch.h"

#include "glm/glm.hpp"
#include <string>
#include <unordered_map>

#include "Renderer/Surface.h"

class Model;
class ShaderProgram;

class AssetManager
{
public:
	~AssetManager();

	Surface* AutoGetSurface(const std::string& key, bool needsGPUTexture, const std::string& filePath = "");

private:
	std::unordered_map<std::string, Surface*> m_surfaces;
};
