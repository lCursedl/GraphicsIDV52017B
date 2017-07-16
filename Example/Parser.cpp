#include "Parser.h"



CParser::CParser()
{
}


CParser::~CParser()
{
}

bool CParser::OpenFile(const char * Filename)
{
	Xfile.open(Filename, std::fstream::in);
	if (!Xfile.is_open())
	{
		return false;
	}
	return true;
}

void CParser::Parse(const char * Filename, std::vector<unsigned short>&Index, std::vector<CVertex4>&Vertex, MATRIX4D &M)
{
	if (OpenFile(Filename))
	{
		std::getline(Xfile, Xline);
		if (!Xline.compare("xof 0303txt 0032"))
		{
			while (!Xfile.eof())
			{
				std::getline(Xfile, Xline);
				if (!Xline.compare(" FrameTransformMatrix relative {"))
				{
					for (int i = 0; i < 16; i++)
					{
						Xfile >> M.v[i] >> ctemp;
					}
					Xfile >> ctemp;
				}
				if (!Xline.compare(" Mesh mesh_pinata_cerdo_ {"))
				{
					Xfile >> size >> ctemp;
					for (int i = 0; i < size; i++)
					{
						CVertex4 V;
						Xfile >> ftemp >> ctemp;
						V.x = ftemp;
						//Vertices.push_back(ftemp);
						Xfile >> ftemp >> ctemp;
						V.y = ftemp;
						//Vertices.push_back(ftemp);
						Xfile >> ftemp >> ctemp;
						V.z = ftemp;
						Xfile >> ctemp;
						Vertex.push_back(V);
						//Vertices.push_back(ftemp);
					}
					Xfile >> size >> ctemp;
					for (int i = 0; i < size; i++)
					{
						Xfile >> ctemp >> ctemp >> stemp;
						Index.push_back(stemp);
						//Indices.push_back(stemp);
						Xfile >> ctemp >> stemp;
						Index.push_back(stemp);
						//Indices.push_back(stemp);
						Xfile >> ctemp >> stemp >> ctemp >> ctemp;
						Index.push_back(stemp);
						//Indices.push_back(stemp);
					}
				}
			}
		}
		Xfile.close();
	}
}