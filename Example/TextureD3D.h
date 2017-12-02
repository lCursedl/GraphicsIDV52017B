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

	void	SetTextureParams(unsigned int &target);
	void	LoadAPITexture(unsigned char * buffer);

	ComPtr<ID3D11Texture2D>				Tex;
	ComPtr<ID3D11ShaderResourceView>    pSRVTex;
	ComPtr<ID3D11SamplerState>          pSampler;
};