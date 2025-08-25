#pragma once
namespace skel
{
	class Surface;

	// basic sprite class
	class Sprite
	{
	public:
		Sprite(Surface* surface, unsigned int frameCount);
		~Sprite();
		// methods
		void Draw(Surface* target, int x, int y);
		void DrawScaled(int x, int y, int width, int height, Surface* target);
		void SetFlags(unsigned int f) { flags = f; }
		void SetFrame(unsigned int i) { currentFrame = i; }
		unsigned int GetFlags() const { return flags; }
		int GetWidth() { return width; }
		int GetHeight() { return height; }
		uint* GetBuffer();
		unsigned int Frames() { return numFrames; }
		Surface* GetSurface() { return surface; }
		void InitializeStartData();
		unsigned int GetCurrentFrame() const { return currentFrame; }
		void PrintAsText();

	private:
		// attributes
		int width, height;
		unsigned int numFrames;
		unsigned int currentFrame;
		unsigned int flags;
		unsigned int** start;
		Surface* surface;
	};
}
