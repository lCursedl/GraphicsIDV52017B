#ifndef UAD_MESH_GL_H
#define UAD_MESH_GL_H

#include <d3dx9math.h>
#include "Parser.h"

#include "PrimitiveBase.h"
#include "Scene.h"
#include "UtilsGL.h"

class MeshGL : public PrimitiveBase {
public:

#ifdef USING_D3D11
	struct CBuffer
	{
		MATRIX4D WVP;
		MATRIX4D World;
	};
#endif

	MeshGL()
#ifdef USING_OPENGL_ES
		: shaderID(0)
#endif
	{}
	void Create(){}
	void Create(char * filename);
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();

#ifdef USING_OPENGL_ES
	GLuint	shaderID;
	GLint	vertexAttribLoc;
	GLint	normalAttribLoc;
	GLint	uvAttribLoc;
	GLint	diffuseAttribLoc;
	GLint	lightposLoc;

	GLint  matWorldViewProjUniformLoc;
	GLint  matWorldUniformLoc;
#elif defined (USING_D3D11)
	ComPtr<ID3D11VertexShader>  pVS;
	ComPtr<ID3D11PixelShader>   pFS;
	ComPtr<ID3DBlob>            VS_blob;
	ComPtr<ID3DBlob>            FS_blob;
	ComPtr<ID3D11InputLayout>   Layout;
	ComPtr<ID3D11Buffer>        pd3dConstantBuffer;
#endif // USING_OPGENL_ES
	

	MATRIX4D	transform;
	CParser P;
	std::vector<Mesh*>MyMeshes;
};
#endif