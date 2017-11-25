#pragma once
#include "Configuration.h"

enum TEXT_BASIC_FORMAT
{
	CH_ALPHA = 1,
	CH_RGB = 2,
	CH_RGBA = 4
};

enum TEXT_BASIC_PARAMS
{
	TILED = 1,
	CLAMP_TO_EDGE = 2,
	MIPMAPS = 4
};

class CTexture
{
public:
	CTexture();
	~CTexture();

	char			optname[128];
	unsigned int	size;
	unsigned int	props;
	unsigned int	params;
	unsigned short	x, y;
	unsigned short	id;
	unsigned char	bounded;
	unsigned char	mipmaps;

	int LoadTexture(char * name);

	virtual void LoadAPITexture(unsigned char * buffer) = 0;
	virtual void SetTextureParams(unsigned int &target) = 0;
};