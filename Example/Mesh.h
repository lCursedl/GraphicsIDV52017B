#ifndef UAD_MESH_GL_H
#define UAD_MESH_GL_H

//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>
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
	//void SetScene(CScene * pScene);
	void Destroy();

	GLuint	shaderID;
	GLint	vertexAttribLoc;
	GLint	normalAttribLoc;
	GLint	uvAttribLoc;
	GLint	diffuseAttribLoc;
	GLint	lightposLoc;

	GLint  matWorldViewProjUniformLoc;
	GLint  matWorldUniformLoc;

	MATRIX4D	transform;
	CParser P;
	std::vector<Mesh*>MyMeshes;
};
#endif