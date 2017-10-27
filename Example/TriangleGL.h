#ifndef UAD_TRIANGLEGL_H
#define UAD_TRIANGLEGL_H

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


//#define USE_ARRAY_OF_STRUCTS
#define USE_VBO

#ifdef USE_VBO
struct triVertex {
	float x, y, z;
	float r, g, b;
};
#else
	#ifdef USE_ARRAY_OF_STRUCTS
	struct triVertex{
		float x,y,z;
		float r,g,b;
	};
	#else
	struct triVertex {
		float x, y, z;
	};
	#endif
#endif

	class TrangleGL : public PrimitiveBase {
	public:
		TrangleGL() : shaderID(0) {}
		void Create();
		void Create(char *) {}
		void Transform(float *t);
		void Draw(float *t, float *vp);
		void Destroy();

		MATRIX4D	transform;

#ifdef USING_OPENGL_ES
		GLuint	shaderID;
		GLuint	vertexAttribLoc;
		GLuint	colorAttribLoc;

		GLuint  matUniformLoc;
#ifdef USE_VBO
		triVertex		vertices[4];
		unsigned short	indices[6];
		GLuint			VB;
		GLuint			IB;
#else
#ifdef USE_ARRAY_OF_STRUCTS
		triVertex	vertices[6];
#else
		triVertex	positions[6];
		triVertex	colors[6];
#endif
#endif
#elif defined (USING_D3D11)

#endif // USING_OPENGL_ES	
};

#endif
