#include "Render.h"
#include <vector>

Render::Render()
{
	factory = NULL;
	renderTarget = NULL;
	writeFactory = NULL;

	defBrushGreen = NULL;
	defBrushRed = NULL;
	currentBrush = NULL;

	defTextFormat = NULL;

	block = NULL;
	fps = NULL;

	timeElapsed = 0;
}

Render::~Render()
{
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
	if (writeFactory) writeFactory->Release();

	if (defBrushGreen) defBrushGreen->Release();
	if (defBrushRed) defBrushRed->Release();
	if (currentBrush) currentBrush->Release();

	if (defTextFormat) defTextFormat->Release();

	block = NULL;
	fps = NULL;
}

bool Render::Init(HWND* _hwnd)
{
	//TODO: Better error handling
	static const WCHAR defFontName[] = CONSOLE_TEXT_FONT;

	if (D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory) != S_OK) return false;

	if (DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&writeFactory)) != S_OK) return false;

	RECT clientRes;

	GetClientRect(*_hwnd, &clientRes);

	if (factory->CreateHwndRenderTarget
	(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(*_hwnd, D2D1::SizeU(clientRes.right, clientRes.bottom)),
		&renderTarget
	) != S_OK) return false;

	//Create default brushes
	if (renderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 100.0f, 0.0f, 100.0f), &defBrushGreen) != S_OK) return false;
	if (renderTarget->CreateSolidColorBrush(D2D1::ColorF(100.0f, 0.0f, 0.0f, 100.0f), &defBrushRed) != S_OK) return false;

	if (writeFactory->CreateTextFormat(defFontName, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, CONSOLE_TEXT_SIZE, L"", &defTextFormat) != S_OK) return false;

	clearScreenColor = D2D1::ColorF(D2D1::ColorF::Blue);
	fpsRect = D2D1::RectF(10.0f, 10.0f, 10.0f + 50, 10.0f + 10);

	return true;
};

bool Render::Redraw(Level &_level, double _timePassed)
{
	renderTarget->BeginDraw();

	renderTarget->Clear(&clearScreenColor);

	//Player
	if (_level.player->drawHitbox)
	{		
		
		if (_level.player->colliding) currentBrush = defBrushRed;
		else currentBrush = defBrushGreen;
		
		renderTarget->DrawRectangle(
			D2D1::RectF(
				_level.player->scrX, 
				_level.player->scrY, 
				_level.player->scrX + _level.player->width,
				_level.player->scrY + _level.player->height),
			currentBrush
		);
	}

	//Blocks
	for(vecIt = 0; vecIt != _level.blocks.size(); vecIt++)
	{
		block = _level.blocks.at(vecIt);

		if (block->colliding) currentBrush = defBrushRed;
		else currentBrush = defBrushGreen;

		if (block->drawHitbox)
		{
			renderTarget->DrawRectangle(
				D2D1::RectF(
					block->scrX,
					block->scrY,
					block->scrX + block->width,
					block->scrY + block->height
				),
				currentBrush
			);
		}
	}

	//FPS
	if (_level.showFps)
	{
		timeElapsed += _timePassed;

		if (timeElapsed > 1)
		{
			fpsWchar = std::to_wstring(60 / _timePassed); // fps = std::to_wstring(60 / _timePassed).c_str(); doesn't work
			fps = fpsWchar.c_str();

			timeElapsed = 0;
		}

		renderTarget->DrawTextA(fps, 5, defTextFormat, fpsRect, defBrushGreen);		
	}

	renderTarget->EndDraw();

	return true;
}