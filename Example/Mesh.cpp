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


	diffuseAttribLoc = glGetUniformLocation(shaderID, "Diffuse");
	lightposLoc = glGetUniformLocation(shaderID, "LightPos");
	matWorldViewProjUniformLoc = glGetUniformLocation(shaderID, "WVP");
	matWorldUniformLoc = glGetUniformLocation(shaderID, "World");


	P.Parse(filename, MyMeshes);

	for (int i = 0; i < MyMeshes.size(); i++)
	{
		glGenBuffers(1, &MyMeshes[i]->VB);
		glBindBuffer(GL_ARRAY_BUFFER, MyMeshes[i]->VB);
		glBufferData(GL_ARRAY_BUFFER, MyMeshes[i]->VertexSize * sizeof(CVertex4), MyMeshes[i]->Vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		for (int j = 0; j < MyMeshes[i]->nMaterials; j++)
		{
			glGenBuffers(1, &MyMeshes[i]->MaterialList[j]->IB);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MyMeshes[i]->MaterialList[j]->IB);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, MyMeshes[i]->MaterialList[j]->IndexSize * sizeof(unsigned short), &MyMeshes[i]->MaterialList[j]->Material_Index[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}		
	}
	transform = Identity();
}

void MeshGL::Transform(float *t)
{
	transform = t;
}

void MeshGL::Draw(float *t, float *vp)
{
	glUseProgram(shaderID);

	if (t)
	{
		transform = t;
	}
	MATRIX4D VP = MATRIX4D(vp);
	MATRIX4D WVP = transform*VP;

	glUniformMatrix4fv(matWorldUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(matWorldViewProjUniformLoc, 1, GL_FALSE, &WVP.m[0][0]);

	VECTOR4D PosLight(-15.0f, 0.0f, 0.0f);

	glUniform4fv(lightposLoc, 1, &pScProp->LightContainer[0].Position.x);

	for (int i = 0; i < MyMeshes.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, MyMeshes[i]->VB);

		glEnableVertexAttribArray(vertexAttribLoc);
		if (normalAttribLoc != -1)
		{
			glEnableVertexAttribArray(normalAttribLoc);
		}

		if (uvAttribLoc != -1)
		{
			glEnableVertexAttribArray(uvAttribLoc);
		}

		glVertexAttribPointer(vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex4), BUFFER_OFFSET(0));


		if (normalAttribLoc != -1)
		{
			glVertexAttribPointer(normalAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex4), BUFFER_OFFSET(16));
		}
		
		if (uvAttribLoc != -1)
			glVertexAttribPointer(uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(CVertex4), BUFFER_OFFSET(32));

		for (int j = 0; j < MyMeshes[i]->MaterialList.size(); j++)
		{
			if (diffuseAttribLoc != -1)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, MyMeshes[i]->MaterialList[j]->diffuse_textID);
				glUniform1i(diffuseAttribLoc, 0);
			}			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MyMeshes[i]->MaterialList[j]->IB);
			glDrawElements(GL_TRIANGLES, MyMeshes[i]->MaterialList[j]->IndexSize, GL_UNSIGNED_SHORT, 0);
		}		

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(vertexAttribLoc);

		if (normalAttribLoc != -1)
		{
			glDisableVertexAttribArray(normalAttribLoc);
		}
		
		if (uvAttribLoc != -1)
		{
			glDisableVertexAttribArray(uvAttribLoc);
		}
					
	}
	glUseProgram(0);
}

//void MeshGL::SetScene(CScene * pScene)
//{
//	this->MyScene = pScene;
//}

void MeshGL::Destroy() {
	glDeleteProgram(shaderID);
}