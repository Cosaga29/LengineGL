#include "PixelBuffer.hpp"
#define NUM_COLORS 5


enum COLOR {

	PIXEL_BLUE = 0x0000FFFF,
	PIXEL_WHITE = 0xFFFFFFFF,
	PIXEL_RED = 0xFF0000FF,
	PIXEL_GREEN = 0x00FF00FF,
	PIXEL_BLACK = 0x00000000

};


class PixelDrawer {

	PixelBuffer* m_buffer;

private:




public:
	PixelDrawer(PixelBuffer& buffer);

	void Clip(int& x, int& y);

	void Draw(int x, int y, COLOR c);
	void Draw(int x, int y, unsigned char* color);

	void Fill(int x1, int y1, int x2, int y2, COLOR c);

	void DrawLine(int x1, int y1, int x2, int y2, COLOR c);

	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, COLOR c);

	void FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, COLOR c);

	void DrawCircle(int xc, int yc, int r, COLOR c);

	void FillCircle(int xc, int yc, int r, COLOR c);

};

