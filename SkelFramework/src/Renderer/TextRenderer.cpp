#include "skelpch.h"
#include "Renderer/TextRenderer.h"

#include "Renderer/Sprite.h"
#include "Renderer/Surface.h"

TextRenderer::TextRenderer(const std::string& fontAddress, const int frameCount, const int charSpacing, const int lineSpacing, int (*CharToIndex)(char)) :
	m_CharToIndex(CharToIndex)
{
	if(frameCount > MAX_FRAME_COUNT)
	{
		throw std::exception("frameCount too big: MAX_FRAME_COUNT is less than frameCount");
	}

	m_frameCount = frameCount;
	m_charSpacing = charSpacing;
	m_lineSpacing = lineSpacing;

	const Surface* fontSurface = new Surface(fontAddress, false);
	m_frameHeight = fontSurface->GetHeight();
	m_frameWidth = fontSurface->GetWidth() / frameCount;
	for(int i = 0; i < m_frameCount; ++i)
	{
		m_pSurfaces[i] = new Surface(m_frameWidth, m_frameHeight, false);
		fontSurface->CopyTo(*m_pSurfaces[i], -i * m_frameWidth, 0);
		m_pSprites[i] = new Sprite(m_pSurfaces[i], 1);
	}
	delete fontSurface;
}

TextRenderer::~TextRenderer()
{
	for(int i = 0; i < m_frameCount; ++i)
	{
		delete m_pSprites[i];
	}
}

void TextRenderer::DrawOnSurface(Surface* surface, const std::string& text, const int x, const int y, const int scale) const
{
	int newLineCount = 0;
	int lastNewLineIndex = 0;
	for(int i = 0; i < text.size(); ++i)
	{
		const char c = text.at(i);
		if(c == '\n')
		{
			newLineCount++;
			lastNewLineIndex = i + 1;
		}
		else
		{
			const int charIndex = m_CharToIndex(c);
			const int xPos = x + (m_frameWidth + m_charSpacing) * scale * (i - lastNewLineIndex);
			const int yPos = y + (m_frameHeight + m_lineSpacing) * scale * newLineCount;
			m_pSprites[charIndex]->DrawScaled(xPos, yPos, m_frameWidth * scale, m_frameHeight * scale, surface);
		}
	}
}
