#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "MATRIX4D.h"

struct CVertex4 {
	float x, y, z;
};

class CParser
{
public:
	CParser();
	~CParser();


	bool OpenFile(const char * Filename);
	void Parse(const char * Filename, std::vector<unsigned short>&Index, std::vector<CVertex4>&Vertex, MATRIX4D &M);

	std::string Xline;
	std::fstream Xfile;
	char ctemp;
	float ftemp;
	unsigned short stemp;
	int size;
};