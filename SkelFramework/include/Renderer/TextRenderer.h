#pragma once

namespace skel
{
	class Sprite;
	class Surface;

	class TextRenderer
	{
	public:
		TextRenderer(const std::string& fontAddress, int frameCount, int charSpacing, int lineSpacing, int (*CharToIndex)(char));
		~TextRenderer();
		void DrawOnSurface(Surface* surface, const std::string& text, int x, int y, int scale) const;

	private:
		int m_frameCount = 0;
		int m_charSpacing = 0;
		int m_lineSpacing = 0;

		static constexpr int MAX_FRAME_COUNT = 64;
		Surface* m_pSurfaces[64];
		Sprite* m_pSprites[64];

		int (*m_CharToIndex)(char c) = nullptr;

		int m_frameHeight = 0;
		int m_frameWidth = 0;
	};
}
