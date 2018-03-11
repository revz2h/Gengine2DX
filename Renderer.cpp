#include "Renderer.h"

Renderer::Renderer()
{
	factory = NULL;
	renderTarget = NULL;
}

Renderer::~Renderer()
{

}

bool Renderer::Init(HWND _hwnd)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);

	if (res != S_OK) return false;

	RECT clientRes;

	GetClientRect(_hwnd, &clientRes);

	res = factory->CreateHwndRenderTarget
	(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(_hwnd, D2D1::SizeU(clientRes.right, clientRes.bottom)),
		&renderTarget
	);

	return true;
};