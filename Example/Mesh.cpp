#include "Mesh.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void MeshGL::Create(char * filename) {
	shaderID = glCreateProgram();

	char *vsSourceP = file2string("VS_Mesh.glsl");
	char *fsSourceP = file2string("FS_Mesh.glsl");

	GLuint vshader_id = createShader(GL_VERTEX_SHADER, vsSourceP);
	GLuint fshader_id = createShader(GL_FRAGMENT_SHADER, fsSourceP);

	glAttachShader(shaderID, vshader_id);
	glAttachShader(shaderID, fshader_id);

	glLinkProgram(shaderID);
	glUseProgram(shaderID);

	vertexAttribLoc = glGetAttribLocation(shaderID, "Vertex");
	normalAttribLoc = glGetAttribLocation(shaderID, "Normal");
	uvAttribLoc = glGetAttribLocation(shaderID, "UV");

	matWorldViewProjUniformLoc = glGetUniformLocation(shaderID, "WVP");
	matWorldUniformLoc = glGetUniformLocation(shaderID, "World");


	P.Parse(filename, Indices, Vertices, transform);

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(CVertex4), &Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned short), &Indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//transform =  Identity();
}

void MeshGL::Transform(float *t) {
	transform = t;
}

void MeshGL::Draw(float *t, float *vp) {
	glUseProgram(shaderID);

	if (t)
	{
		transform = t;
	}
	MATRIX4D VP = MATRIX4D(vp);
	MATRIX4D WVP = transform*VP;

	glUniformMatrix4fv(matWorldUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(matWorldViewProjUniformLoc, 1, GL_FALSE, &WVP.m[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	glEnableVertexAttribArray(vertexAttribLoc);
	//glEnableVertexAttribArray(normalAttribLoc);

	//Eliminar al pasar a MeshGL
	/*if (uvAttribLoc != -1)
		glEnableVertexAttribArray(uvAttribLoc);*/
	//

	glVertexAttribPointer(vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex4), BUFFER_OFFSET(0));
	//glVertexAttribPointer(normalAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex), BUFFER_OFFSET(16));

	/*if (uvAttribLoc != -1)
		glVertexAttribPointer(uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(CVertex), BUFFER_OFFSET(32));*/

	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(vertexAttribLoc);

	//Eliminar al pasar a MeshGDL
	//glDisableVertexAttribArray(normalAttribLoc);

	/*if (uvAttribLoc != -1) {
		glDisableVertexAttribArray(uvAttribLoc);
	}*/

	glUseProgram(0);
}

void MeshGL::Destroy() {
	glDeleteProgram(shaderID);
}