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
	ID2D1SolidColorBrush* defBrush;
	IDWriteTextFormat* defTextFormat;
	D2D1_COLOR_F clearScreenColor;
	D2D1_RECT_F fpsRect;
	const WCHAR* fps;
	std::wstring fpsWchar;
	int vecIt;
	Block* block;
	
public:
	Render();
	~Render();

	bool Init(HWND* _hwnd);

	bool Redraw(Level &_level, double _timePassed);
};
#endif