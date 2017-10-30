#ifndef UAD_CUBE_GL_H
#define UAD_CUBE_GL_H

#include "Configuration.h"

#ifdef USING_OPENGL_ES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif defined (USING_D3D11)
#include <d3dcompiler.h>
#include "D3DXDriver.h"
#endif


#include <d3dx9math.h>
#include "MATRIX4D.h"

#include "PrimitiveBase.h"
#include "UtilsGL.h"



struct CVertex {

	float x, y, z, w;
	float nx,ny,nz,nw;
	float s,t;
};

class CubeGL : public PrimitiveBase {
public:
	CubeGL() 
#ifdef USING_OPENGL_ES
		: shaderID(0)
#endif
	{}

#ifdef USING_D3D11
	struct CBuffer
	{
		MATRIX4D WVP;
		MATRIX4D World;
	};
#endif
	void Create();
	void Create(char *){}
	void Transform(float *t);
	void Draw(float *t,float *vp);
	void Destroy();

#ifdef USING_OPENGL_ES
	GLuint	shaderID;
	GLint	vertexAttribLoc;
	GLint	normalAttribLoc;
	GLint	uvAttribLoc;

	GLint  matWorldViewProjUniformLoc;
	GLint  matWorldUniformLoc;

	GLuint			VB;
	GLuint			IB;
#elif defined (USING_D3D11)

	ComPtr<ID3D11Buffer>		IB;
	ComPtr<ID3D11Buffer>		VB;
	ComPtr<ID3D11VertexShader>  pVS;
	ComPtr<ID3D11PixelShader>   pFS;
	ComPtr<ID3DBlob>            VS_blob;
	ComPtr<ID3DBlob>            FS_blob;
	ComPtr<ID3D11InputLayout>   Layout;
	ComPtr<ID3D11Buffer>        pd3dConstantBuffer;

	CubeGL::CBuffer	CnstBuffer;
#endif	

	CVertex			vertices[24];
	unsigned short	indices[36];	

	MATRIX4D	transform;
};
#endif