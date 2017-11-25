#pragma once
#include "Texture.h"

#include <d3d11.h>
#include <wrl.h>
#include <wrl\client.h>

using namespace Microsoft::WRL;

class CTextureD3D :
	public CTexture
{
public:
	CTextureD3D();
	~CTextureD3D();
};

