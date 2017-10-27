#ifndef UAD_MESH_GL_H
#define UAD_MESH_GL_H

#include <d3dx9math.h>
#include "Parser.h"

#include "PrimitiveBase.h"
#include "Scene.h"
#include "UtilsGL.h"

class MeshGL : public PrimitiveBase {
public:
	MeshGL() : shaderID(0) {}
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

#endif // USING_OPGENL_ES
	

	MATRIX4D	transform;
	CParser P;
	std::vector<Mesh*>MyMeshes;
};
#endif