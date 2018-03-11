#ifndef __RENDERER_H_INCLUDED__
#define __RENDERER_H_INCLUDED__

#include <Windows.h>
#include <d2d1.h>

class Renderer
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;

public:
	Renderer();
	~Renderer();

	bool Init(HWND _hwnd);

	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }
};

#endif