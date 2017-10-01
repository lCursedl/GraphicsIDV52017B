#pragma once
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "MATRIX4D.h"
#include "UtilsGL.h"

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
	std::vector<unsigned short>Material_Index;
	int IndexSize = 0;
	GLuint IB;
	GLuint diffuse_textID;
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
	int itemp;
	int size;
	int diffuse_count = 0;
	int material_count = 0;
};