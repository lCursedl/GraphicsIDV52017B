#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "MATRIX4D.h"

struct CVertex4 {
	float x, y, z, w;
	float nx, ny, nz, nw;
	float s, t;
};

class CParser
{
public:
	CParser();
	~CParser();


	bool OpenFile(const char * Filename);
	void Parse(const char * Filename, std::vector<unsigned short>&Index, std::vector<CVertex4>&Vertex, MATRIX4D &M);

	//MATRIX4D M;
	std::string Xline;
	std::fstream Xfile;
	/*std::vector<float>Vertices;
	std::vector<unsigned int>Indices;*/
	char ctemp;
	float ftemp;
	unsigned short stemp;
	int size;
};