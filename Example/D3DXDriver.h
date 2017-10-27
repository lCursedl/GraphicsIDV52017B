#pragma once
#include "BaseDriver.h"
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>

#include <wrl.h>
#include <wrl\client.h>

using namespace Microsoft::WRL;

class D3DXDriver :	public BaseDriver
{
public:
	D3DXDriver() {  }
	void	InitDriver();
	void	CreateSurfaces();
	void	DestroySurfaces();
	void	Update();
	void	DestroyDriver();
	void	SetWindow(void *window);
	void	SetDimensions(int, int);

	void	Clear();
	void	SwapBuffers();

	int		Width;
	int		Height;
	HWND	hwnd;
};