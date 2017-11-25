#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <string>



CTexture::CTexture()
{
	size = 0;
	props = 0;
	params = 0;
	x = 0;
	y = 0;
	id = 0;
	bounded = 0;
	mipmaps = 0;
}

CTexture::~CTexture()
{
}

int CTexture::LoadTexture(char * name)
{
	std::string path;
	path = std::string(name);
	int x = 0, y = 0, channels = 0;
	unsigned char *buffer = stbi_load(path.c_str(), &x, &y, &channels, 0);

	if (!buffer)
	{
		return -1;
	}

	size = x*y*channels;
	bounded = 1;
	this->x = x;
	this->y = y;
	mipmaps = 1;
	this->params = params;

	switch (channels) {
	case 1: {
		props |= TEXT_BASIC_FORMAT::CH_ALPHA;
	}break;
	case 3: {
		props |= TEXT_BASIC_FORMAT::CH_RGB;
	}break;
	case 4: {
		props |= TEXT_BASIC_FORMAT::CH_RGBA;
	}break;
	}

	memcpy(&optname[0], name, strlen(name));
	optname[strlen(name)] = '\0';

	LoadAPITexture(buffer);
	stbi_image_free(buffer);

	return id;
}