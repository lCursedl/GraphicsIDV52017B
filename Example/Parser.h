#pragma once
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "MATRIX4D.h"
#include "UtilsGL.h"

struct CVertex4 {
	CVertex4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f), nx(0.0f), ny(0.0f), nz(0.0f), nw(1.0f){

	}
	float x, y, z, w;
	float nx, ny, nz, nw;
	float u, v;
};

struct Mesh
{
	CVertex4 * Vertices;
	unsigned short * Indices;

	int			VertexSize;
	int			IndexSize;

	GLuint		VB;
	GLuint		IB;
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
	int size;
};