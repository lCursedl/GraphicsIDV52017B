#pragma once
#include "Configuration.h"

#ifdef USING_OPENGL_ES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif defined(USING_D3D11)
#include "D3DXDriver.h"
#include <d3dcompiler.h>
#include "TextureD3D.h"
#endif


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "MATRIX4D.h"
#include "UtilsGL.h"

#ifdef USING_D3D11
extern ComPtr<ID3D11Device>            D3D11Device;
extern ComPtr<ID3D11DeviceContext>     D3D11DeviceContext;
#endif

struct CVertex4
{
	CVertex4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f), nx(0.0f), ny(0.0f), nz(0.0f), nw(1.0f){

	}
	float x, y, z, w;
	float nx, ny, nz, nw;
	float u, v;
};

struct M_Material
{
	unsigned short Material_ID;
	unsigned short * MIndex;
	std::vector<unsigned short>Material_Index;
	int IndexSize = 0;
#ifdef USING_OPENGL_ES
	GLuint IB;
	GLuint diffuse_textID;
#elif defined (USING_D3D11)
	ComPtr<ID3D11Texture2D>				Tex;
	ComPtr<ID3D11Buffer>				IB;
	ComPtr<ID3D11ShaderResourceView>    pSRVTex;
	ComPtr<ID3D11SamplerState>          pSampler;
	CTexture *							Diffuse;
#endif // USING_OPENGL_ES
	
	std::string DiffusePath;
};

struct Mesh
{
	CVertex4 * Vertices;
	float * Vertex;
	unsigned short * Indices;
	std::vector<M_Material*>MaterialList;

	int			VertexSize;
	int			IndexSize;
	unsigned short nMaterials = 0;
	unsigned int Stride = 16;

	bool HasNormal;
	bool HasTexcoords;

#ifdef USING_OPENGL_ES
	GLuint		VB;
	GLuint		IB;
#elif defined (USING_D3D11)

	struct CBuffer
	{
		MATRIX4D WVP;
		MATRIX4D World;
	};

	ComPtr<ID3D11Buffer>		IB;
	ComPtr<ID3D11Buffer>		VB;

	std::vector<D3D11_INPUT_ELEMENT_DESC>	VertexDecl;

	Mesh::CBuffer				CnstBuffer;
#endif
	
};

class CParser
{
public:
	CParser();
	~CParser();


	bool OpenFile(const char * Filename);
	void Parse(const char * Filename, std::vector<Mesh*>&MeshList);

	std::string Xline;
	std::fstream Xfile;
	char ctemp;
	float ftemp;
	unsigned short stemp;
	int itemp;
	int size;
	int diffuse_count = 0;
	int material_count = -1;
};