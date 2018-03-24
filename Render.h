#ifndef __RENDER_H_INCLUDED__
#define __RENDER_H_INCLUDED__

#include <Windows.h>
#include <dwrite.h>
#include <d2d1.h>
#include <string>
#include "Level.h"
#include "defs.h"


class Render
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	IDWriteFactory* writeFactory;
	ID2D1SolidColorBrush* currentBrush;
	ID2D1SolidColorBrush* defBrushGreen;
	ID2D1SolidColorBrush* defBrushRed;
	IDWriteTextFormat* defTextFormat;
	const WCHAR* fps;
	Block* block;

	D2D1_COLOR_F clearScreenColor;
	D2D1_RECT_F fpsRect;
	std::wstring fpsWchar;
	int vecIt;
	float timeElapsed;
	
public:
	bool showFps, drawCollisions;

	Render();
	~Render();

	bool Init(HWND* _hwnd);

	bool Redraw(Level &_level, double _timePassed);
};
#endif