#ifndef UAD_CUBE_GL_H
#define UAD_CUBE_GL_H

#include "Configuration.h"

#ifdef USING_OPENGL_ES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif defined (USING_D3D11)
#include <d3dcompiler.h>
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
	CubeGL() : shaderID(0) {}
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

#endif	

	CVertex			vertices[24];
	unsigned short	indices[36];
	

	MATRIX4D	transform;
};


#endif