#include "AssetManager.h"

#include <stdexcept>
#include <string>
#include <unordered_map>

AssetManager::~AssetManager()
{
	for(auto& [key, surface] : m_surfaces)
	{
		delete surface;
	}
	m_surfaces.clear();
}

Surface* AssetManager::AutoGetSurface(const std::string& key, const bool needsGPUTexture, const std::string& filePath)
{
	if(m_surfaces.contains(key))
	{
		return m_surfaces[key];
	}
	if(filePath.empty())
	{
		throw std::runtime_error("Surface with key does not exist and filePath is empty");
	}
	m_surfaces[key] = new Surface(filePath, needsGPUTexture);
	return m_surfaces[key];
}
